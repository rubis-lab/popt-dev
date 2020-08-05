## Applying RT Patch to NVIDIA TX2
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

### Download the req'd packages
[Nvidia L4T Download](https://developer.nvidia.com/embedded/linux-tegra-r281)  
From the above link, download:  
1. Documentation 
2. Jetson TX2 64-bit Driver Package
3. Sample Root File System
4. GCC 4.8.5 Tool Chain for 64-bit BSP
5. source_release.tbz2 Package

