/**
 * \file
 * \brief Definitions of lwIP functions related to file system integration for http server
 *
 * \author Copyright (C) 2019 Aleksander Szczygiel
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwipHttpServerFsConfigure.hpp"

#include "lwip/apps/fs.h"

#include "distortos/FileSystem/FileSystem.hpp"
#include "distortos/FileSystem/openFile.hpp"

#include "distortos/assert.h"

#include <tuple>

#include <cstring>
#include <fcntl.h>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// pointer to file system object
distortos::FileSystem* httpServerFileSystem {};

/// path to root directory of http server
const char* httpServerRootDirectory {};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lwipHttpServerFsConfigure(distortos::FileSystem& fileSystem, const char* rootDirectory)
{
	LOCK_TCPIP_CORE();

	httpServerFileSystem = &fileSystem;
	httpServerRootDirectory = rootDirectory != nullptr ? rootDirectory : "";

	UNLOCK_TCPIP_CORE();
}

extern "C" int fs_open_custom(fs_file* const fileStruct, const char* const name)
{
	assert(httpServerFileSystem != nullptr);
	assert(httpServerRootDirectory != nullptr);

	char fullPath[NAME_MAX + 1];
	{
		const auto ret = sniprintf(fullPath, sizeof(fullPath), "%s%s", httpServerRootDirectory, name);
		if (ret < 0)
			return 0;
		if (static_cast<unsigned int>(ret) >= sizeof(fullPath))
			return 0;
	}

	int ret;
	std::unique_ptr<distortos::File> file;
	std::tie(ret, file) = httpServerFileSystem->openFile(fullPath, O_RDONLY);
	if (ret != 0)
		return 0;

	const auto result = file->getSize();
	if (result.first != 0)
	{
		file->close();
		return 0;
	}

	memset(fileStruct, 0, sizeof(*fileStruct));

	fileStruct->len = result.second;
	fileStruct->flags = FS_FILE_FLAGS_HEADER_INCLUDED | FS_FILE_FLAGS_HEADER_PERSISTENT |
			FS_FILE_FLAGS_HEADER_HTTPVER_1_1;
	fileStruct->pextension = file.release();

	return 1;
}

extern "C" void fs_close_custom(fs_file* const fileStruct)
{
	if (fileStruct == nullptr || fileStruct->pextension == nullptr)
		return;

	const auto file = static_cast<distortos::File*>(fileStruct->pextension);
	file->close();
	delete file;
	fileStruct->pextension = nullptr;
}

extern "C" int fs_read_custom(fs_file* const fileStruct, char* const buffer, const int count)
{
	assert(fileStruct != nullptr);
	assert(fileStruct->pextension != nullptr);
	assert(buffer != nullptr);

	const auto ret = static_cast<distortos::File*>(fileStruct->pextension)->read(buffer, count);
	fileStruct->index += ret.second;

	return ret.second;
}
