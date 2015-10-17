set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1.0)
set(CMAKE_SYSTEM_PROCESSOR armv7a)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_FIND_ROOT_PATH "/srv/einkbuild/SDK2FREE/SDK-481/arm-obreey-linux-gnueabi/sysroot/")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
list(APPEND CMAKE_MODULE_PATH /srv/einkbuild/SDK2FREE/SDK-481/share/cmake/modules)
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
#set(PKG_CONFIG_EXECUTABLE -pkg-config)
set(QT_QMAKE_EXECUTABLE "/srv/einkbuild/SDK2FREE/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/qt4/bin/qmake")


set(CMAKE_C_COMPILER "/srv/einkbuild/SDK2FREE/SDK-481/bin/arm-obreey-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "/srv/einkbuild/SDK2FREE/SDK-481/bin/arm-obreey-linux-gnueabi-g++")

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp " CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-z,defs" CACHE STRING "" FORCE)

add_definitions(-DPLATFORM_FC)
set(PB_PLATFORM "ARM" CACHE STRING "ARM|PC Readonly!")

set(CMAKE_INSTALL_PREFIX "/srv/einkbuild/SDK2FREE/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/local" CACHE PATH "Installation Prefix")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug|Release|RelWithDebInfo|MinSizeRel")
