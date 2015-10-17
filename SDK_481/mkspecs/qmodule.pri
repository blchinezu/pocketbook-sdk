CONFIG +=  cross_compile compile_examples qpa largefile pcre
QT_BUILD_PARTS += libs
QT_NO_DEFINES =  CUPS DBUS EFFECTS EGL EGLFS EGL_X11 GLIB HARFBUZZ ICONV IMAGEFORMAT_JPEG OPENGL OPENVG PULSEAUDIO STYLE_GTK XRENDER ZLIB
QT_QCONFIG_PATH = 
host_build {
    QT_CPU_FEATURES.x86_64 =  mmx sse sse2
} else {
    QT_CPU_FEATURES.arm =  neon
}
QT_COORD_TYPE = double
QT_LFLAGS_ODBC   = -lodbc
OPENSSL_LIBS = -lssl -lcrypto
styles += mac fusion windows
DEFINES += QT_NO_MTDEV
QMAKE_CFLAGS_FONTCONFIG = -I/srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/home/igor/sources/buildroot-2014.05/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include -I/srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/home/igor/sources/buildroot-2014.05/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/freetype2 -I/srv/build/EP.515-experimental/SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/include/freetype2  
QMAKE_LIBS_FONTCONFIG = -lfontconfig -lfreetype  
DEFINES += QT_NO_LIBUDEV
sql-drivers = 
sql-plugins =  sqlite
