#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo “This script must be run as root”
   exit 1
fi
# -lt is <, -gt is >
if [ $2 -lt 0 -o $2 -gt 12 ] ; then
	echo "Out of range"
	exit 1
fi

echo "before : "
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# -eq is ==
if [ $# -eq 2 ]
then
	case $1 in
		perf)
			for ((i=0;i<$2;i++));
			do
				echo performance > /sys/devices/system/cpu/cpu$i/cpufreq/scaling_governor
	
			done ;;
		save)
			for ((i=0;i<$2;i++));
			do
				echo powersave > /sys/devices/system/cpu/cpu$i/cpufreq/scaling_governor
	
			done ;;
		*)
			echo "There is no proper value"
			exit 1 ;;
	esac
	
else
	echo "There is no value"
	exit 1
fi

printf "\nafter : \n"
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

exit 0
