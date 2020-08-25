#!/usr/bin/env bash
if [[ $EUID -ne 0 ]]; then
   echo “This script must be run as root”
   exit 1
fi
python3 pypopt/gui/gui.py $1
