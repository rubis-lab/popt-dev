## How to use shell files

**setfreq.sh**  
switch between performance and powersave modes of the CPU;  

```
sudo su
./setfreq.sh [perf/save] [1~12]
```

**cpuset.sh**  
mount the cpuset folder and set up the CPUs to guarantee exclusive cpu and mem nodes usage;  
note that /dev/cpuset has to be mounted first for the flags to work  
```
sudo su
./cpuset.sh [1~12]
// To unmount the cpuset: umount -l /dev/cpuset
```
