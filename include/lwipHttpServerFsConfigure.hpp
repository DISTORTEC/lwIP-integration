/**
 * \file
 * \brief lwipHttpServerFsConfigure() declaration
 *
 * \author Copyright (C) 2019 Aleksander Szczygiel
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_
#define LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_

namespace distortos
{

class FileSystem;

}	// namespace distortos

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Configures HTTP server by providing reference to file system and path to root directory
 *
 * Must be called before httpd_init()
 *
 * \param [in] fileSystem is a reference to the file system object
 * \param [in] rootDirectory is the path to root directory of HTTP server
 */

void lwipHttpServerFsConfigure(distortos::FileSystem& fileSystem, const char* rootDirectory);

#endif	// LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_
