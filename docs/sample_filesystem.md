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
```shell
# put board in force recovery mode

Connect Power Unit
Turn of the power, if on
Push RECOVERY_FORCE
While pushing RECOVERY_FORCE, press the POWER button
After the board boots up, release POWER button first
Release RECOVERY_FORCE button

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
$ scp $HOME/Downloads/nvidia/sdkm_downalods_43/cuda-repo-l4t-10-0-local-10.0.326_1.0.1_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/Downloads/nvidia/sdkm_downloads_43/libcudnn7_7.6.3.28-1+cuda10.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/Downloads/nvidia/sdkm_downloads_43/libcudnn7-dev_7.6.3.28-1+cuda10.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
$ scp $HOME/Downloads/nvidia/sdkm_downloads_43/libcudnn7-doc_7.6.3.28-1+cuda10.0_arm64.deb nvidia@JETSON_IP_ADDRESS:/home/nvidia
# Doesn't match from here
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
