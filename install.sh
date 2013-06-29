#! /bin/sh

mkdir build
cd build && cmake ../libraries && make -j 2 && cd ..
cp build/session/libsession.so /usr/lib/


