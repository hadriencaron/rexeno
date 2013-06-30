#! /bin/sh

regularFiles='/usr/rexeno/'

mkdir build
cd build && cmake ../libraries && make -j 2 && cd ..
cp build/session/libsession.so /usr/lib/
cp configFiles/rexeno ~/.rexeno


