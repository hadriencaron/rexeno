#! /bin/sh

sudo analogyBindDriver.sh

xset s off
path=`pwd`
RUN_MODE='single_core'
#RUN_MODE='dual_core'

if [ $RUN_MODE == 'dual_core' ]; then
    sudo ../../../../trunk/prototypes/Recorder/Recorder &
    sudo taskset 0x00000002 ./display &
    sudo ../../../../trunk/prototypes/Rewarder/reward_server &
    sudo taskset 0x00000001 ../../../trunk/prototypes/Launcher/launcher.bin

    sudo pkill display
    sudo pkill -9 Recorder
    sudo pkill -9 reward_server
else
    echo MONO CORE
    
    sudo ../../../../trunk/prototypes/Recorder/Recorder &
    sudo ./display &
    sudo ../../../../trunk/prototypes/Rewarder/rewarder.sh $path 2> log_reward.txt &
    sudo ../../../../trunk/prototypes/Strober/strober &
    sudo ../../../../trunk/prototypes/Launcher/launcher.bin
    sudo pkill display
    sudo pkill -9 Recorder
    sudo pkill -9 strober
    sudo pkill -9 reward_server
    sudo pkill -9 rewarder.sh
fi

sudo ./save_session.sh
