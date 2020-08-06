## Download dev tools
```shell
$ mkdir -p $HOME/nvidia_rt
$ cd $HOME/nvidia_rt
$ wget -O l4t-gcc-7-3-1-toolchain-64-bit.tar.xz https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit
$ wget https://developer.nvidia.com/embedded/L4T/r32_Release_v4.2/Sources/T186/public_sources.tbz2
```

## Prepare build sources
```shell
$ cd $HOME/nvidia_rt
$ tar -xf l4t-gcc-7-3-1-toolchain-64-bit.tar.xz
$ tar -xf public_sources.tbz2
$ cd $HOME/nvidia_rt/Linux_for_Tegra/source/public
$ tar -xjf kernel_src.tbz2
```

## Create an `environment` file for envvars
```shell
$ cd $HOME/nvidia_rt
$ vim $HOME/nvidia_rt/rubis_env_rt
#!/bin/sh
# toolchain flags
export BSPTOOLCHAIN=$HOME/nvidia_rt/install/bin
export PATH=${BSPTOOLCHAIN}:${PATH}
# kernel flags
export ARCH=arm64
export CROSS_COMPILE=$HOME/nvidia_rt/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export TEGRA_KERNEL_OUT=$HOME/nvidia_rt/tegra-jetson-tx2-kernel
```

## Export build variables and start compiling
Test kernel config with `CONFIG_LOCALVERSION="-rt"` and `CONFIG_PREEMPT_RT_FULL=y` can be found [here](https://github.com/kozyilmaz/nvidia-jetson-rt/raw/master/scripts/jetson-tx2-rt.config)

```shell
$ cd $HOME/nvidia_rt
$ source rubis_env_rt
$ mkdir -p $TEGRA_KERNEL_OUT
$ cd $HOME/nvidia_rt/Linux_for_Tegra/source/public/kernel/kernel-4.9
# list and apply real-time patches
$ for i in rt-patches/*.patch; do echo $i; done
$ for i in rt-patches/*.patch; do patch -p1 < $i; done
# create default config
$ make O=$TEGRA_KERNEL_OUT ARCH=$ARCH tegra_defconfig
# change CONFIG_LOCALVERSION="-rt", "CONFIG_HZ_1000=y" and  CONFIG_PREEMPT_RT_FULL=y for real-time scheduling
$ make O=$TEGRA_KERNEL_OUT ARCH=$ARCH menuconfig

```

## To make a stanalone kernel:

```shell
# create kernel image
$ make -j10 O=$TEGRA_KERNEL_OUT ARCH=$ARCH
# replace image to release kernel
$ cp $HOME/nvidia_rt/tegra-jetson-tx2-kernel/arch/arm64/boot/Image $HOME/nvidia/Linux_for_Tegra/kernel/
# replace dts
$ cd /nvidia/Linux_for_Tegra/kernel/dtb
$ rm -f ./*
$ cp -r $HOME/nvidia_rt/tegra-jetson-tx2-kernel/arch/arm64/boot/dts/* $HOME/nvidia/Linux_for_Tegra/kernel/dtb/

# make kernel modules
$ cd $HOME/Linux_for_Tegra/source/public/kernel/kernel-4.9
$ sudo make ARCH=arm64 O=$TEGRA_KERNEL_OUT modules_install INSTALL_MOD_PATH=$HOME/nvidia/Linux_for_Tegra/rootfs
$ cd $HOME/nvidia/Linux_for_Tegra/rootfs
$ sudo tar --owner root --group root -cjf kernel_supplements.tbz2 lib/modules
$ sudo mv kernel_supplements.tbz2 $HOME/nvidia/Linux_for_Tegra/kernel/
$ cd $HOME/nvidia/Linux_for_Tegra
$ sudo ./apply_binaries.sh
```

## To update an existing kernel:
```shell
$ cd $HOME/nvidia_rt
$ mkdir L4T
$ cd $HOME/nvidia_rt/Linux_for_Tegra/source/public/kernel/kernel-4.9
# create compressed kernel image
$ make -j10 O=$TEGRA_KERNEL_OUT ARCH=$ARCH zImage
# compile device tree
$ make O=$TEGRA_KERNEL_OUT ARCH=$ARCH dtbs
# compile and install kernel modules
$ make -j10 O=$TEGRA_KERNEL_OUT ARCH=$ARCH modules
$ make O=$TEGRA_KERNEL_OUT ARCH=$ARCH modules_install INSTALL_MOD_PATH=$TEGRA_KERNEL_OUT/modules

## Copy binaries to `L4T` for deployment
$ mkdir -p $HOME/nvidia_rt/L4T/kernel
$ cp $TEGRA_KERNEL_OUT/arch/arm64/boot/Image $HOME/nvidia_rt/L4T/kernel
$ mkdir -p $HOME/nvidia_rt/L4T/kernel/dtb
$ cp $TEGRA_KERNEL_OUT/arch/arm64/boot/dts/*.dtb $HOME/nvidia_rt/L4T/kernel/dtb
$ cd $TEGRA_KERNEL_OUT/modules
$ tar --owner root --group root -cjf kernel_supplements.tbz2 *
$ cp $TEGRA_KERNEL_OUT/modules/kernel_supplements.tbz2 $HOME/nvidia_rt/L4T/kernel/kernel_supplements.tbz2
$ cd $HOME/nvidia_rt
$ tar -cjf $HOME/nvidia_rt/L4T.tbz2 L4T
$ scp $HOME/nvidia_rt/L4T.tbz2 nvidia@JETSON_IP_ADDRESS:/home/nvidia

```

## [TARGET] Update Kernel and Drivers on Jetson Board
```shell
$ cd /home/nvidia
$ tar -xjvf L4T.tbz2
$ sudo cp L4T/kernel/Image /boot/Image
$ sudo cp L4T/kernel/dtb/* /boot/dtb
$ sudo cp L4T/kernel/dtb/* /boot
$ sudo tar -xvf L4T/kernel/kernel_supplements.tbz2 -C /
$ sudo reboot
```

## [TARGET] Check Kernel Parameters after Reboot
```shell
$ zcat /proc/config.gz |grep CONFIG_HZ
# CONFIG_HZ_PERIODIC is not set
# CONFIG_HZ_100 is not set
# CONFIG_HZ_250 is not set
# CONFIG_HZ_300 is not set
CONFIG_HZ_1000=y
CONFIG_HZ=1000
$ zcat /proc/config.gz |grep CONFIG_PREEMPT
CONFIG_PREEMPT_RCU=y
CONFIG_PREEMPT=y
CONFIG_PREEMPT_RT_BASE=y
CONFIG_PREEMPT_LAZY=y
# CONFIG_PREEMPT_NONE is not set
# CONFIG_PREEMPT_VOLUNTARY is not set
# CONFIG_PREEMPT__LL is not set
# CONFIG_PREEMPT_RTB is not set
CONFIG_PREEMPT_RT_FULL=y
CONFIG_PREEMPT_COUNT=y
# CONFIG_PREEMPTIRQ_EVENTS is not set
# CONFIG_PREEMPT_TRACER is not set
nvidia@tegra-ubuntu:~/devel/nvidia-jetson-rt$ uname -a
Linux nvidia 4.9.140-rt93-rt #1 SMP PREEMPT RT Thu Aug 6 16:40:53 KST 2020 aarch64 aarch64 aarch64 GNU/Linux
```

### Flashing NVIDIA TX2
1. Download Nvidia SDK Manager from [here](https://developer.nvidia.com/embedded/jetpack)
2. Type sdkmanger in shell command to launch the manager
3. Select Jetson TX2 (Not Jetson TX2 4GB) and connect your device
4. Continue with the installation and manually connect your device when prompted
* To connect your device:
* Have wired connection to the same router as your host PC
* Connect to the host PC using micro AB USB cabl
* Plug the power in
* **You need an extra monitor connected to TX2 board**
5. Before the installation completes, you will be prompted to set up ubuntu version xx.04 on your TX2
6. After setting the ubuntu up, the installation should complete  

Note: In order to set up your board manually, you have to force reboot the board into recovery mode:  
1. Turn the power off
2. While pressing the recovery button, press the power button.
3. Release the power button first and then the recovery button. 
Recovery button: 3rd button  
Power button: 4th button  
