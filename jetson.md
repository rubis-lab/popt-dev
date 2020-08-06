<!-- # Building a Jetson TX2 image and flashing it to eMMC
[Link to required NVIDIA packages](https://github.com/kozyilmaz/nvidia-jetson-rt#nvidia-jetson-tx2-configuration) -->

# This will install...
[L4T 32.4.2](https://developer.nvidia.com/embedded/linux-tegra-r32.4.2)

## Creating NVIDIA Jetson TX2 image
[Driver Package: L4T Driver Package (BSP)](https://developer.nvidia.com/embedded/L4T/r32_Release_v4.2/t186ref_release_aarch64/Tegra186_Linux_R32.4.2_aarch64.tbz2)
Download required packages
```shell
$ mkdir -p $HOME/nvidia/docs
$ cd $HOME/nvidia
$ wget https://developer.nvidia.com/embedded/L4T/r32_Release_v4.2/t186ref_release_aarch64/Tegra186_Linux_R32.4.2_aarch64.tbz2
$ wget -O NV_Jetson_Linux_Driver_Package.tar https://developer.nvidia.com/nvidia-jetson-linux-driver-package
$ wget https://developer.nvidia.com/embedded/L4T/r32_Release_v4.2/t186ref_release_aarch64/Tegra_Linux_Sample-Root-Filesystem_R32.4.2_aarch64.tbz2
```

Unpack
```shell
$ tar -xf NV_Jetson_Linux_Driver_Package.tar -C $HOME/nvidia/docs
$ sudo tar -xf Tegra186_Linux_R32.4.2_aarch64.tbz2
# (3 min)
$ sudo tar -xf Tegra_Linux_Sample-Root-Filesystem_R32.4.2_aarch64.tbz2 -C $HOME/nvidia/Linux_for_Tegra/rootfs
$ cd $HOME/nvidia/Linux_for_Tegra
$ sudo ./apply_binaries.sh
```

## Flashing NVIDIA Jetson TX2 internal eMMC
![Screenshot](https://github.com/kozyilmaz/nvidia-jetson-rt/raw/master/docs/console.jpg "NVIDIA Jetson TX2 Console Connection")
```shell
# put board in recovery mode
Connect Power Unit
Press POWER
Release POWER
Push RECOVERY_FORCE
Push RESET (after one second)
Release RESET
Release RECOVERY_FORCE (after two second)

# run flash command (5 min)
$ sudo ./flash.sh -t jetson-tx2 mmcblk0p1
Push RESET (after done)
```

## [HOST] Check for available SSH connection to Jetson TX2
```shell
# to connect Jetson board
$ ssh nvidia@JETSON_IP_ADDRESS
```

## Using JetPack to install CUDA, OpenCV4Tegra and cuDNN is highly recommended, manual installation may be problematic!

## [HOST] Copy CUDA/TensorFlow packages to Jetson TX2
```shell
$ scp $HOME/nvidia/jetpack_download/cuda-repo-l4t-8-0-local_8.0.84-1_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/nvidia/jetpack_download/libcudnn6_6.0.21-1+cuda8.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/nvidia/jetpack_download/libcudnn6-dev_6.0.21-1+cuda8.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/nvidia/jetpack_download/libcudnn6-doc_6.0.21-1+cuda8.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/nvidia/jetpack_download/nv-gie-repo-ubuntu1604-ga-cuda8.0-trt2.1-20170614_1-1_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/nvidia/jetpack_download/libopencv4tegra-repo_2.4.13-17-g5317135_arm64_l4t-r26.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
```

## [TARGET] Update Ubuntu packages
```shell
$ sudo apt update
$ sudo apt upgrade
$ sudo apt autoremove
```

## [TARGET] Install CUDA and TensorFlow
```shell
$ sudo dpkg -i /home/nvidia/cuda-repo-l4t-8-0-local_8.0.84-1_arm64.deb
$ sudo dpkg -i /home/nvidia/libcudnn6_6.0.21-1+cuda8.0_arm64.deb
$ sudo dpkg -i /home/nvidia/libcudnn6-dev_6.0.21-1+cuda8.0_arm64.deb
$ sudo dpkg -i /home/nvidia/libcudnn6-doc_6.0.21-1+cuda8.0_arm64.deb
$ sudo dpkg -i /home/nvidia/nv-gie-repo-ubuntu1604-ga-cuda8.0-trt2.1-20170614_1-1_arm64.deb
$ sudo dpkg -i /home/nvidia/libopencv4tegra-repo_2.4.13-17-g5317135_arm64_l4t-r26.deb
$ sudo apt update
$ sudo apt install cuda-toolkit-8.0
$ sudo apt install tensorrt-2.1.2
```

Add these commands at the end of `$HOME.profile`
```shell
export PATH=/usr/local/cuda-8.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH
```

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

## [TARGER] Check Kernel Parameters after Reboot
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