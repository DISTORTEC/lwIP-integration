/**
 * \file
 * \brief lwIP's cc.h header for distortos
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_ARCH_CC_H_
#define LWIP_INTEGRATION_INCLUDE_ARCH_CC_H_

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global defines
+---------------------------------------------------------------------------------------------------------------------*/

/** lwIP should use standard `<errno.h>` */
#define LWIP_ERRNO_STDINCLUDE					1

#ifdef NDEBUG

/** disable lwIP assertions if they are disabled globally */
#define LWIP_NOASSERT							1

#endif	/* def NDEBUG */

/** lwIP should use standard `struct timeval` */
#define LWIP_TIMEVAL_PRIVATE					0

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* LWIP_INTEGRATION_INCLUDE_ARCH_CC_H_ */
