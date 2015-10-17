
ssh $me "cd /home/igor/x-tools/arm-obreey-linux-gnueabi/ && tar cz arm-obreey-linux-gnueabi  bin include  lib  libexec  share" | tar xzv -C SDK-481

chmod 755 SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/

( cd SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/ && mv include include_xtools && mv lib lib_xtools )

ssh $me "cd /home/igor/sources/buildroot-2014.05/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/ && tar cz include  lib" | tar xzv -C SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/
mkdir -p SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/local 


ln -s json-c ../../SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/include/json

chmod 555 SDK-481/arm-obreey-linux-gnueabi/sysroot/usr/
