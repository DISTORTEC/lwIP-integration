/**
 * \file
 * \brief lwIP configuration
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_
#define LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_

#include "lwIP-configuration.h"

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global defines
+---------------------------------------------------------------------------------------------------------------------*/

/** MEM_ALIGNMENT: should be set to the alignment of the CPU */
#define MEM_ALIGNMENT							4

/*---------------------------------------------------------------------------------------------------------------------+
| lwIP TCP/IP core locking
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Asserts that this function is not called from interrupt context and that lwIP's TCP/IP core is locked by
 * current thread.
 *
 * \sa LWIP_ASSERT_CORE_LOCKED()
 */

void lwipAssertCoreLocked(void);

/**
 * \brief Locks lwIP's TCP/IP core.
 *
 * \sa LOCK_TCPIP_CORE()
 */

void lwipLockTcpipCore(void);

/**
 * \brief Marks that lwIP's TCP/IP core is started.
 *
 * \sa LWIP_MARK_TCPIP_THREAD()
 */

void lwipMarkTcpipThread(void);

/**
 * \brief Unlocks lwIP's TCP/IP core.
 *
 * \sa UNLOCK_TCPIP_CORE()
 */

void lwipUnlockTcpipCore(void);

/** wrapper for lwipLockTcpipCore() */
#define LOCK_TCPIP_CORE()						lwipLockTcpipCore()

/** wrapper for lwipAssertCoreLocked() */
#define LWIP_ASSERT_CORE_LOCKED()				lwipAssertCoreLocked()

/** wrapper for lwipMarkTcpipThread() */
#define LWIP_MARK_TCPIP_THREAD()				lwipMarkTcpipThread()

/** wrapper for lwipUnlockTcpipCore() */
#define UNLOCK_TCPIP_CORE()						lwipUnlockTcpipCore()

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_ */
