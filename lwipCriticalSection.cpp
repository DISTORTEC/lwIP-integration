/**
 * \file
 * \brief Definitions of mutex-related functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/architecture/enableInterruptMasking.hpp"
#include "distortos/architecture/restoreInterruptMasking.hpp"

#include <cstring>

static_assert(sizeof(sys_prot_t) == sizeof(distortos::architecture::InterruptMask) &&
		alignof(sys_prot_t) == alignof(distortos::architecture::InterruptMask),
		"sys_prot_t doesn't match distortos::architecture::InterruptMask!");

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

sys_prot_t sys_arch_protect()
{
	const auto interruptMask = distortos::architecture::enableInterruptMasking();
	sys_prot_t protectionLevel;
	memcpy(&protectionLevel, &interruptMask, sizeof(protectionLevel));
	return protectionLevel;
}

void sys_arch_unprotect(const sys_prot_t protectionLevel)
{
	distortos::architecture::InterruptMask interruptMask;
	memcpy(&interruptMask, &protectionLevel, sizeof(interruptMask));
	distortos::architecture::restoreInterruptMasking(interruptMask);
}
