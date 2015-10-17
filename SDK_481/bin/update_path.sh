#!/bin/sh

script_path=$(cd $(dirname $0) && pwd)

SDK_ROOT=`realpath ${script_path}/..`
mkdir -p ${SDK_ROOT}/share/cmake

CMAKE_TOOLCHAIN_FILE_ARM=${SDK_ROOT}/share/cmake/arm_conf.cmake
TARGET_ARM='arm-obreey-linux-gnueabi'

CMAKE_TOOLCHAIN_FILE_PC=${SDK_ROOT}/share/cmake/pc_conf.cmake

#Update ARM config
echo "\
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1.0)
set(CMAKE_SYSTEM_PROCESSOR armv7a)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_FIND_ROOT_PATH \"${SDK_ROOT}/${TARGET_ARM}/sysroot/\")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
list(APPEND CMAKE_MODULE_PATH "${SDK_ROOT}/share/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
#set(PKG_CONFIG_EXECUTABLE -pkg-config)
set(QT_QMAKE_EXECUTABLE \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/qt4/bin/qmake\")


set(CMAKE_C_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-gcc\")
set(CMAKE_CXX_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-g++\")

set(CMAKE_CXX_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_RELEASE \"${CMAKE_CXX_FLAGS_RELEASE}\" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS \"-Wl,-z,defs\" CACHE STRING \"\" FORCE)

add_definitions(-DPLATFORM_FC)
set(PB_PLATFORM \"ARM\" CACHE STRING \"ARM|PC Readonly!\")

set(CMAKE_INSTALL_PREFIX \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/local\" CACHE PATH \"Installation Prefix\")
set(CMAKE_BUILD_TYPE Release CACHE STRING \"Debug|Release|RelWithDebInfo|MinSizeRel\")" > ${CMAKE_TOOLCHAIN_FILE_ARM}

#Update PC config
echo "\
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_FIND_ROOT_PATH \"${SDK_ROOT}\")
list(APPEND CMAKE_MODULE_PATH "${SDK_ROOT}/share/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
set(QT_QMAKE_EXECUTABLE \"${SDK_ROOT}/local/qt4/bin/qmake\")

set(CMAKE_CXX_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=native -mtune=native \" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_RELEASE \"\${CMAKE_CXX_FLAGS_RELEASE}\" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE \" -s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)

set(CMAKE_SHARED_LINKER_FLAGS \"-Wl,-z,defs\" CACHE STRING \"\" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG \"-ggdb -O0 -pipe -fno-omit-frame-pointer\" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_DEBUG \"\${CMAKE_CXX_FLAGS_DEBUG}\" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG \"\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG \"\" CACHE STRING \"\" FORCE)

set(CMAKE_INSTALL_PREFIX \"${SDK_ROOT}/local\" CACHE PATH \"Installation Prefix\")
add_definitions(-DEMULATOR -DPLATFORM_NX)

set(PB_PLATFORM \"PC\" CACHE STRING  \"ARM|PC Readonly!\")

set(CMAKE_BUILD_TYPE Release CACHE STRING \"Debug|Release|RelWithDebInfo|MinSizeRel\")" > ${CMAKE_TOOLCHAIN_FILE_PC}
