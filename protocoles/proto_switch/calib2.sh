#! /bin/sh

RUN_MODE='single_core'
RUN_MODE='dual_core'

if [ $RUN_MODE = 'dual_core' ] ; then
    sudo ../../../../trunk/prototypes/Recorder/Recorder &
    sudo taskset 0x00000001 ./display &
    sudo taskset 0x00000002 ../../../../trunk/prototypes/Launcher/launcher.bin

    sudo pkill display
    sudo pkill -9 Recorder
else
    echo MONO CORE
    
    sudo ../../../../trunk/prototypes/Recorder/Recorder &
    sudo ./display &
    sudo ../../../../trunk/prototypes/Launcher/launcher.bin
    sudo pkill display
    sudo pkill -9 Recorder
fi

