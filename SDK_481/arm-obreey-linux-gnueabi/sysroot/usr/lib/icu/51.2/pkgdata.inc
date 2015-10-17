GENCCODE_ASSEMBLY_TYPE=-a gcc
SO=so
SOBJ=so
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.51.2
COMPILE=/home/igor/sources/buildroot-2014.05/output/host/usr/bin/arm-obreey-linux-gnueabi-gcc -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_REENTRANT   -DU_ATTRIBUTE_DEPRECATED= -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -pipe -mcpu=cortex-a8 -march=armv7-a -mfpu=neon -mfloat-abi=softfp -Os  -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings  -c
LIBFLAGS=-I/usr/include -DPIC -fPIC
GENLIB=/home/igor/sources/buildroot-2014.05/output/host/usr/bin/arm-obreey-linux-gnueabi-gcc -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -pipe -mcpu=cortex-a8 -march=armv7-a -mfpu=neon -mfloat-abi=softfp -Os  -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings   -shared -Wl,-Bsymbolic
LDICUDTFLAGS=-nodefaultlibs -nostdlib
LD_SONAME=-Wl,-soname -Wl,
RPATH_FLAGS=
BIR_LDFLAGS=-Wl,-Bsymbolic
AR=/home/igor/sources/buildroot-2014.05/output/host/usr/bin/arm-obreey-linux-gnueabi-ar
ARFLAGS=r
RANLIB=/home/igor/sources/buildroot-2014.05/output/host/usr/bin/arm-obreey-linux-gnueabi-ranlib
INSTALL_CMD=/usr/bin/install -c
