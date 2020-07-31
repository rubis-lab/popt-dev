#!/bin/bash

if [[ $EUID -ne 0 ]] ; then
    echo "This script must be run as root"
    exit 1
fi

current_time = $(date "+%Y.%m.%d-%H.%M.%S")
echo "Current time : $current_time"


#if [ ! -d /experiment/]