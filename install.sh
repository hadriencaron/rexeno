#! /bin/sh

regularFiles='/usr/rexeno/'

mkdir build
mkdir /usr/include/rexeno
cd build && cmake ../libraries && make -j 2 && cd ..
cp build/session/libsession.a build/recorder/librecorder.a build/driver/libdriver.a build/configuration/libconfiguration.a /usr/lib/

cp libraries/includes/* /usr/include/rexeno
cd libraries/Matrix && ./install.sh && cd ../..
cp libraries/configuration/option.hh libraries/configuration/parser.hh /usr/include/rexeno

cp configFiles/rexeno ~/.rexeno
cp -r protocoles/default $regularFiles



