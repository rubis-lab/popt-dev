### NVIDIA AGX XAVIER cpufreq HOW TO USE
``` shell
$ sudo nvpmodel -m [0-6] --verbose
```
- To check the avaialable options:
``` shell
$ cd /etc
$ cat nvpmodel.conf
```
- Note: it appears that shutting down one complete Denver core is not supported; **available options**: 0, 3
- To check the workings of the cpu's with htop:
``` shell
$ htop
$ stress -c [num_cpus] -t [timeout]
```
