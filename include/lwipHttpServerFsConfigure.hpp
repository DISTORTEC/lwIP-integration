/**
 * \file
 * \brief lwipHttpServerFsConfigure() declaration
 *
 * \author Copyright (C) 2019 Aleksander Szczygiel
 * \author Copyright (C) 2020 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_
#define LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Configures HTTP server by providing path to root directory.
 *
 * Must be called before httpd_init()
 *
 * \note This functionality requires integration of file systems with standard library to be enabled in distortos
 * configuration.
 *
 * \warning Path is stored directly, no copy is made - the string referenced by \a rootDirectory must be valid at all
 * times.
 *
 * \param [in] rootDirectory is the path to root directory of HTTP server
 */

void lwipHttpServerFsConfigure(const char* rootDirectory);

#endif	// LWIP_INTEGRATION_INCLUDE_LWIPHTTPSERVERFSCONFIGURE_HPP_
