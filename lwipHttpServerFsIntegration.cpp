/**
 * \file
 * \brief Definitions of lwIP functions related to file system integration for http server
 *
 * \author Copyright (C) 2019 Aleksander Szczygiel
 * \author Copyright (C) 2020 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwipHttpServerFsConfigure.hpp"

#include "lwip/apps/fs.h"

#include "distortos/assert.h"

#include "estd/ScopeGuard.hpp"

#include <cstring>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// path to root directory of http server
const char* httpServerRootDirectory {};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lwipHttpServerFsConfigure(const char* rootDirectory)
{
	httpServerRootDirectory = rootDirectory != nullptr ? rootDirectory : "";
}

extern "C" int fs_open_custom(fs_file* const fileStruct, const char* const name)
{
	assert(fileStruct != nullptr);
	assert(httpServerRootDirectory != nullptr);

	FILE* file;
	{
		char fullPath[256];
		const auto ret = sniprintf(fullPath, sizeof(fullPath), "%s%s", httpServerRootDirectory, name);
		if (ret < 0)
			return {};
		if (static_cast<unsigned int>(ret) >= sizeof(fullPath))
			return {};

		file = fopen(fullPath, "r");
		if (file == nullptr)
			return {};
	}

	auto closeScopeGuard = estd::makeScopeGuard(
			[file]()
			{
				fclose(file);
			});

	memset(fileStruct, 0, sizeof(*fileStruct));

	{
		const auto ret = fseek(file, 0, SEEK_END);
		if (ret != 0)
			return {};
	}
	{
		const auto ret = ftell(file);
		if (ret == -1)
			return {};

		fileStruct->len = ret;
	}
	{
		const auto ret = fseek(file, 0, SEEK_SET);
		if (ret != 0)
			return {};
	}

	fileStruct->flags = FS_FILE_FLAGS_HEADER_PERSISTENT | FS_FILE_FLAGS_HEADER_HTTPVER_1_1;
	fileStruct->pextension = file;
	closeScopeGuard.release();
	return 1;
}

extern "C" void fs_close_custom(fs_file* const fileStruct)
{
	if (fileStruct == nullptr || fileStruct->pextension == nullptr)
		return;

	fclose(static_cast<FILE*>(fileStruct->pextension));
	fileStruct->pextension = {};
}

extern "C" int fs_read_custom(fs_file* const fileStruct, char* const buffer, const int count)
{
	assert(fileStruct != nullptr);
	assert(fileStruct->pextension != nullptr);
	assert(buffer != nullptr);

	const auto bytesRead = fread(buffer, 1, count, static_cast<FILE*>(fileStruct->pextension));
	fileStruct->index += bytesRead;
	return bytesRead;
}
