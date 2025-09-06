# Copyright (C) 2020-2025  The Mustard development team
#
# This file is part of Mustard, an offline software framework for HEP experiments.
#
# Mustard is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# Mustard is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# Mustard. If not, see <https://www.gnu.org/licenses/>.

message(STATUS "Looking for argparse")

set(MUSTARD_ARGPARSE_MINIMUM_REQUIRED 3.2)

if(NOT MUSTARD_BUILTIN_ARGPARSE)
    find_package(argparse ${MUSTARD_ARGPARSE_MINIMUM_REQUIRED}.0)
    if(NOT argparse_FOUND)
        set(MUSTARD_BUILTIN_ARGPARSE ON)
        message(NOTICE "***Notice: argparse not found (minimum required is ${MUSTARD_ARGPARSE_MINIMUM_REQUIRED}). For the time turning on MUSTARD_BUILTIN_ARGPARSE")
    endif()
endif()

if(MUSTARD_BUILTIN_ARGPARSE)
    message(STATUS "Mustard will use built-in argparse")
    # check built-in version
    if(MUSTARD_BUILTIN_ARGPARSE_VERSION VERSION_LESS MUSTARD_ARGPARSE_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MUSTARD_BUILTIN_ARGPARSE_VERSION is ${MUSTARD_BUILTIN_ARGPARSE_VERSION}, which is less than the requirement (${MUSTARD_ARGPARSE_MINIMUM_REQUIRED}). Changing to ${MUSTARD_ARGPARSE_MINIMUM_REQUIRED}")
        set(MUSTARD_BUILTIN_ARGPARSE_VERSION ${MUSTARD_ARGPARSE_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MUSTARD_BUILTIN_ARGPARSE_SRC_DIR "${MUSTARD_PROJECT_3RDPARTY_DIR}/argparse-${MUSTARD_BUILTIN_ARGPARSE_VERSION}")
    set(MUSTARD_BUILTIN_ARGPARSE_URL "https://github.com/p-ranav/argparse/archive/refs/tags/v${MUSTARD_BUILTIN_ARGPARSE_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(argparse SOURCE_DIR "${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}")
        message(STATUS "Reusing argparse source ${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}")
    else()
        FetchContent_Declare(argparse SOURCE_DIR "${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}"
                                      URL "${MUSTARD_BUILTIN_ARGPARSE_URL}")
        message(STATUS "argparse will be downloaded from ${MUSTARD_BUILTIN_ARGPARSE_URL} to ${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}")
    endif()
    # set options
    set(ARGPARSE_INSTALL ${MUSTARD_INSTALL} CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring argparse (version: ${MUSTARD_BUILTIN_ARGPARSE_VERSION})")
    FetchContent_MakeAvailable(argparse)
    message(STATUS "Downloading (if required) and configuring argparse (version: ${MUSTARD_BUILTIN_ARGPARSE_VERSION}) - done")
    # # check download
    # if(NOT EXISTS "${MUSTARD_BUILTIN_ARGPARSE_SRC_DIR}/CMakeLists.txt")
    #     file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/argparse-build")
    #     file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/argparse-subbuild")
    #     message(FATAL_ERROR "It seems that the download of argparse has failed. You can try running cmake again, or manually download argparse from ${MUSTARD_BUILTIN_ARGPARSE_URL} and extract it to ${MUSTARD_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    # endif()
endif()

if(NOT MUSTARD_BUILTIN_ARGPARSE)
    message(STATUS "Looking for argparse - found (version: ${argparse_VERSION})")
else()
    message(STATUS "Looking for argparse - built-in (version: ${MUSTARD_BUILTIN_ARGPARSE_VERSION})")
endif()
