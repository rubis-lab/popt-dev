## Steps to Verify and Simulate RT Kernel

1. Sample Codes to Run
	* [mlockall()](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/memory/mlockall_globals_sample?s[]=major&s[]=page&s[]=fault)
	* [mlockall()_2](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/application_base)	
	* [others](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/application_base)
2. [RT-Test Codes](https://git.kernel.org/pub/scm/linux/kernel/git/clrkwllms/rt-tests.git/)
```
sudo apt-get install libnuma-dev
make
```
3. [Preemption-Test](https://rt.wiki.kernel.org/index.php/Preemption_Test)
	* Note: suffers from path collision of kconfig.h file
4. [rt-app](https://github.com/scheduler-tools/rt-app)
	* Need to install autoconf, automake, libtool, libjson-c, libnuma-dev
```
export ac_cv_lib_json_c_json_object_from_file=yes
export ac_cv_lib_numa_numa_available=yes
./autogen.sh
./configure
make
make install
./rt-app /doc/examples/tutorial/example1.json
```
5. [RT-SPIN](http://www-verimag.imag.fr/~tripakis/rtspin.html)
	* Note: i386 code is not compatible; fix makefiles by adding -m32 flag on CC=gcc
	* Update the RTSPIN variable with appropriate file path
	* make rtspin -> cd examples -> ../rtspin -a fischer
	* Or cd into examples folder and type make -> ./tpan


### Resolved Problems
1. mlockall() function requires root level permission using sudo
	* Normal user is allocated 64 kb of memory which (usually) is not enough for running RT programs
	* Either allocate more memory to user or just run it with sudo
	* [mlockall-user_permission](https://stackoverflow.com/questions/46978524/mlockall-cannot-allocate-memory)
2. 32/64-bit compatibility issue with RT-SPIN code


### Problems
1. Some legacy(?) header files
	* [RT-LINUX](https://www.tldp.org/HOWTO/RTLinux-HOWTO-4.html) -> "rtl.h" is not available
2. some detector modules and 'modules' can't be found
	* when running hwlatdetect test with "hwaletdetect --duration=120 --threshold=15"
3. path collision occurs with some linux header files that are not included in the rt-linux folder
	* some headers in /usr/bin or /usr/include are not present in /usr/src/linux-5.0.21/usr/bin ...

