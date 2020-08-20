<!-- # Building a Jetson TX2 image and flashing it to eMMC
[Link to required NVIDIA packages](https://github.com/kozyilmaz/nvidia-jetson-rt#nvidia-jetson-tx2-configuration) -->

# This will install...
[L4T 32.4.2](https://developer.nvidia.com/embedded/linux-tegra-r32.4.2)

## Creating NVIDIA Jetson Xavier image
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

## Flashing NVIDIA AGX XAVIER internal eMMC
```shell
# put board in recovery mode
1. Power down the device. If connected, remove the AC adapter from the device. The device must be powered OFF, and not in a suspend or sleep state.
2. Connect the Type-C plug on the USB cable to the Recovery (USB Type-C) Port on the device and the other end to an available USB port on the host PC.
3. Connect the power adapter to the device.
4. Press and release the POWER button to power on device.
5. Press and hold the FORCE RECOVERY button: while pressing the FORCE RECOVERY button, press and release the RESET button; wait two seconds and release the FORCE RECOVERY button.
6. When the device is in recovery mode, lsusb command on host will list a line of "NVidia Corp"
# the board should boot up but the monitor won't turn on

# run flash command (5 min)
$ sudo ./flash.sh jetson-xavier mmcblk0p1
# NEVER use -t option 082020 (JSP)

7. push the reset RESET button.

```

## [HOST] Check for available SSH connection to Jetson Xavier
```shell
# to connect Jetson board
$ ssh nvidia@JETSON_IP_ADDRESS
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
export TEGRA_XAVIER_KERNEL_OUT=$HOME/nvidia_rt/tegra-jetson-xavier-kernel


## Export build variables and start compiling
Test kernel config with `CONFIG_LOCALVERSION="-rt"` and `CONFIG_PREEMPT_RT_FULL=y` can be found [here](https://github.com/kozyilmaz/nvidia-jetson-rt/raw/master/scripts/jetson-tx2-rt.config)

```shell
$ cd $HOME/nvidia_rt
$ source rubis_env_rt
$ mkdir -p $TEGRA_XAVIER_KERNEL_OUT
$ cd $HOME/nvidia_rt/Linux_for_Tegra/source/public/kernel/kernel-4.9
# list and apply real-time patches
$ for i in rt-patches/*.patch; do echo $i; done
$ for i in rt-patches/*.patch; do patch -p1 < $i; done
# create default config
$ make O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH tegra_defconfig
# change CONFIG_LOCALVERSION="-rt", "CONFIG_HZ_1000=y" and  CONFIG_PREEMPT_RT_FULL=y for real-time scheduling
$ make O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH menuconfig
```


## To update an existing kernel:
```shell
$ cd $HOME/nvidia_rt
$ mkdir L4T
$ cd $HOME/nvidia_rt/Linux_for_Tegra/source/public/kernel/kernel-4.9
# create compressed kernel image
$ make -j12 O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH zImage
# compile device tree
$ make O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH dtbs
# compile and install kernel modules
$ make -j12 O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH modules
$ make O=$TEGRA_XAVIER_KERNEL_OUT ARCH=$ARCH modules_install INSTALL_MOD_PATH=$TEGRA_XAVIER_KERNEL_OUT/modules

## Copy binaries to `L4T` for deployment
$ mkdir -p $HOME/nvidia_rt/L4T/kernel
$ cp $TEGRA_XAVIER_KERNEL_OUT/arch/arm64/boot/Image $HOME/nvidia_rt/L4T/kernel
$ mkdir -p $HOME/nvidia_rt/L4T/kernel/dtb
$ cp $TEGRA_XAVIER_KERNEL_OUT/arch/arm64/boot/dts/*.dtb $HOME/nvidia_rt/L4T/kernel/dtb
$ cd $TEGRA_XAVIER_KERNEL_OUT/modules
$ tar --owner root --group root -cjf kernel_supplements.tbz2 *
$ cp $TEGRA_XAVIER_KERNEL_OUT/modules/kernel_supplements.tbz2 $HOME/nvidia_rt/L4T/kernel/kernel_supplements.tbz2
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
Linux nvidia 4.9.140-rt93-rt #1 SMP PREEMPT RT Thu Aug 19 17:17:52 KST 2020 aarch64 aarch64 aarch64 GNU/Linux
```

### Force Recovery Mode for NVIDIA AGX XAVIER
1. Power down the device. If connected, remove the AC adapter from the device. The device must be powered OFF, and not in a suspend or sleep state.
2. Connect the Type-C plug on the USB cable to the Recovery (USB Type-C) Port on the device and the other end to an available USB port on the host PC.
3. Connect the power adapter to the device.
4. Press and release the POWER button to power on device.
5. Press and hold the FORCE RECOVERY button: while pressing the FORCE RECOVERY button, press and release the RESET button; wait two seconds and release the FORCE RECOVERY button.
6. When the device is in recovery mode, **lsusb** command on HOST will list a line of **Nvidia Corp**    
