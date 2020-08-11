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
./cpuset.sh [1~12] $$
// To unmount the cpuset: umount -l /dev/cpuset
```
fix: the pid of the terminal has to be given as a parameter;  
inside the shell program, '$$' accesses the pid of itself, which is not the desired pid.

**kernelshark.sh**  
automates ftrace using trace-cmd and extracting & visualizing data using kernelshark  
1. creates /experiment directory if not present  
2. creates /experiment/$current_date directory if not present  
3. extracts .dat files into $current_time.dat and opens it with kernelshark  
```
./kernelshark.sh /home/rubis/.../EG1 /home/rubis/.../sample.json
```
Need to pass the .exe file and .json file by their directories (currently only supports 1 input file)
