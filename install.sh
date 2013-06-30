#! /bin/sh

regularFiles='/usr/rexeno/'

mkdir build
mkdir /usr/include/rexeno
cd build && cmake ../libraries && make -j 2 && cd ..
cp build/session/libsession.so /usr/lib/
cp build/includes/* /usr/include/rexeno
cp configFiles/rexeno ~/.rexeno
cp -r protocoles/default $regularFiles



