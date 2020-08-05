#!/bin/bash
if [[ $EUID -ne 0 ]]; then
   echo “This script must be run as root”
   exit 1
fi

printf "adding pid : $2\n"

if [ ! -d /dev/cpuset ] ; then
 mkdir -p /dev/cpuset
fi

cd /dev/cpuset

if !(grep -qs "/dev/cpuset" /proc/mounts); then
  mount -t cpuset cpuset /dev/cpuset
fi

if [ ! -d rubis ] ; then
 mkdir rubis
fi

if [ $1 -eq 1 ] ; then
   /bin/echo 1 > rubis/cpuset.cpus
else 
   /bin/echo 1-$1 > rubis/cpuset.cpus
fi   
/bin/echo 0 > cpuset.sched_load_balance
/bin/echo 0 > rubis/cpuset.mems
/bin/echo 1 > rubis/cpuset.cpu_exclusive
/bin/echo 1 > rubis/cpuset.mem_exclusive
sudo echo -1 > /proc/sys/kernel/sched_rt_runtime_us # sched rt check off
/bin/echo $2 > /dev/cpuset/rubis/tasks

printf "\nafter : \n"

printf "tasks: \n"
cat /dev/cpuset/rubis/tasks
printf "cpuset.sched_load_balance: "
cat /dev/cpuset/rubis/cpuset.sched_load_balance
printf "cpuset.mems: "
cat /dev/cpuset/rubis/cpuset.mems
printf "cpuset.cpu_exclusive: "
cat /dev/cpuset/rubis/cpuset.cpu_exclusive
printf "cpuset_mem.exclusive: "
cat /dev/cpuset/rubis/cpuset.mem_exclusive
