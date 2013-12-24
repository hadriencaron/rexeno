#! /bin/sh

## done (but needs to be redone)
# boost sur le site officiel
# apt-get source freeglut3-dev OK
# apt-get source libx11-dev OK
# apt-get source libfreetype6-dev OK
# apt-get source libffi-dev OK
# apt-get source qt4-qmake OK

## not copied to target
# apt-get source libqt4-designer NO
# apt-get source libqt4-dev OK
# apt-get source libpcre3-dev OK

## not done
# apt-get source libxext-dev OK
# apt-get source libxi-dev OK
# apt-get source libxau-dev OK

## installation of a apt-get sourced lib
# configuration ./configure --prefix=/home/hadrien/Bureau/Work/GITs/xenomai/newRexeno/3rdparties/linux-ububuntu-12-04-noxeno/target/xau
# make
# make install

## installation of a boost
# ./boostrap.sh
# ./b2 
# ./b2 install --prefix=

# xcb:
# first install xcb-proto
# then export PKG_CONFIG_PATH=../../../target/xcb-proto/lib/pkgconfig

## properly installed
# libffi
# xau
# freeglut
# x11
# freetype
# boost
# xi
# xext
# pcre
# qt

cd boost/boost_1_48_0 && ./bootstrap.sh --prefix=../target/boost && ./b2 install && cd ../..
cd opengl/freeglut-2.6.0 && ./configure && make && cp -r && cd ../..
cd x11/libx11-1.4.99.1 && ./configure && make && cp -r && cd ../..

