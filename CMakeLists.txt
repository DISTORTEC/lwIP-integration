#
# file: CMakeLists.txt
#
# This is the main CMakeLists.txt for lwIP integration with distortos
#
# author: Copyright (C) 2019-2022 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.8)
project(lwIP-integration)

if(NOT DEFINED LWIP_DIRECTORY)
	message(SEND_ERROR "Variable with path to lwIP directory - LWIP_DIRECTORY - is not defined")
endif()
if(NOT IS_DIRECTORY "${LWIP_DIRECTORY}")
	message(SEND_ERROR "Path to lwIP directory - LWIP_DIRECTORY = ${LWIP_DIRECTORY} - is not valid")
endif()
if(NOT EXISTS "${LWIP_DIRECTORY}/src/Filelists.cmake")
	message(SEND_ERROR "Path to lwIP directory - LWIP_DIRECTORY = ${LWIP_DIRECTORY} - does not contain "
			"src/Filelists.cmake")
endif()

if(NOT DEFINED LWIP_CONFIGURATION_H_DIRECTORY)
	message(SEND_ERROR "Variable with path to lwIP-configuration.h - LWIP_CONFIGURATION_H_DIRECTORY - is not defined")
endif()
if(NOT IS_DIRECTORY "${LWIP_CONFIGURATION_H_DIRECTORY}")
	message(SEND_ERROR "Path to lwIP-configuration.h - "
			"LWIP_CONFIGURATION_H_DIRECTORY = ${LWIP_CONFIGURATION_H_DIRECTORY} - is not valid")
endif()
if(NOT EXISTS "${LWIP_CONFIGURATION_H_DIRECTORY}/lwIP-configuration.h")
	message(SEND_ERROR "Path to lwIP-configuration.h - "
			"LWIP_CONFIGURATION_H_DIRECTORY = ${LWIP_CONFIGURATION_H_DIRECTORY} - does not contain "
			"lwIP-configuration.h")
endif()

set(LWIP_DIR ${LWIP_DIRECTORY})
include(${LWIP_DIR}/src/Filelists.cmake)

add_library(lwIP-interface-library INTERFACE)
target_include_directories(lwIP-interface-library INTERFACE
		${CMAKE_CURRENT_LIST_DIR}/include
		${LWIP_DIR}/src/include
		${LWIP_DIR}/src/include/compat/posix
		${LWIP_CONFIGURATION_H_DIRECTORY})
target_link_libraries(lwIP-interface-library INTERFACE
		distortos::distortos)

add_library(lwIP-object-library OBJECT
		${CMAKE_CURRENT_LIST_DIR}/lwipCriticalSection.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipErrorToErrorCode.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipHttpServerFsIntegration.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMailbox.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMiscellaneous.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMutex.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipSemaphore.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipTcpipCoreLocking.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipTime.cpp)
target_link_libraries(lwIP-object-library PRIVATE
		lwIP-interface-library)

target_link_libraries(lwipallapps PUBLIC
		lwIP-interface-library)
target_sources(lwipallapps INTERFACE
		$<TARGET_OBJECTS:lwIP-object-library>)

target_link_libraries(lwipcore PUBLIC
		lwIP-interface-library)
target_sources(lwipcore INTERFACE
		$<TARGET_OBJECTS:lwIP-object-library>)

if(TARGET mbedtls)
	target_compile_options(lwipmbedtls PRIVATE
			-Wno-sign-compare
			-Wno-unused-result)
	target_link_libraries(lwipmbedtls PUBLIC
			lwIP-interface-library
			mbedtls)

	target_link_libraries(lwipallapps PUBLIC
			lwipmbedtls)
	target_link_libraries(lwipcore PUBLIC
			lwipmbedtls)
endif()
