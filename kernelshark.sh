#!/bin/bash

if [[ $EUID -ne 0 ]] ; then
    echo "This script must be run as root"
    exit 1
fi

current_date=$(date "+%m.%d.%y")
current_time=$(date "+%m.%d.%y-%H:%M:%S")

if [ ! -d $HOME/experiment ] ; then
	mkdir -p $HOME/experiment
fi

if [ ! -d $HOME/experiment/$current_date ] ; then
	mkdir -p $HOME/experiment/$current_date
fi

cd $HOME/experiment/$current_date
trace-cmd record -e sched -F $1 $2
mv trace.dat $current_time.dat
kernelshark $current_time.dat

exit 0
