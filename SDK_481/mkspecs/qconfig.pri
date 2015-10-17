#configuration
CONFIG +=  cross_compile shared qpa no_mocdepend release qt_no_framework
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = arm
} else {
    QT_ARCH = arm
    QMAKE_DEFAULT_LIBDIRS = /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/lib /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/lib /srv/build/EP.515-experimental/SDK-481/lib/gcc/arm-obreey-linux-gnueabi/4.8.1 /srv/build/EP.515-experimental/SDK-481/lib/gcc /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/lib
    QMAKE_DEFAULT_INCDIRS = /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/include/c++/4.8.1 /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/include/c++/4.8.1/arm-obreey-linux-gnueabi /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/include/c++/4.8.1/backward /srv/build/EP.515-experimental/SDK-481/lib/gcc/arm-obreey-linux-gnueabi/4.8.1/include /srv/build/EP.515-experimental/SDK-481/lib/gcc/arm-obreey-linux-gnueabi/4.8.1/include-fixed /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/include /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/include
}
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config fontconfig evdev linuxfb c++11 accessibility shared qpa reduce_exports clock-gettime clock-monotonic posix_fallocate mremap getaddrinfo ipv6ifname getifaddrs inotify eventfd system-jpeg system-png png system-freetype no-harfbuzz system-zlib nis openssl-linked rpath alsa icu concurrent release

#versioning
QT_VERSION = 5.3.0
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 3
QT_PATCH_VERSION = 0

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

# pkgconfig
PKG_CONFIG_SYSROOT_DIR = /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot
PKG_CONFIG_LIBDIR = /srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/lib/pkgconfig:/srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/share/pkgconfig:/srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/lib/arm-obreey-linux-gnueabi/pkgconfig

# sysroot
!host_build {
    QMAKE_CFLAGS    += --sysroot=$$[QT_SYSROOT]
    QMAKE_CXXFLAGS  += --sysroot=$$[QT_SYSROOT]
    QMAKE_LFLAGS    += --sysroot=$$[QT_SYSROOT]
}

QT_GCC_MAJOR_VERSION = 4
QT_GCC_MINOR_VERSION = 8
QT_GCC_PATCH_VERSION = 1
