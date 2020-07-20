## Linux Kernel RT-Preempt Patch

```
cd /usr/src
wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.19.132.tar.xz
wget https://www.kernel.org/pub/linux/kernel/projects/rt/4.19/patch-4.19.132-rt59.patch.xz
xz -cd linux-4.19.132.tar.xz | tar xvf -
cd linux-4.19.132
xzcat ../patch-4.19.132-rt59.patch.xz | patch -p1
cp -v /boot/config-$(uname -r) .config
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev bc
make menuconfig
CONFIG_PREEMPT_RT_FULL // General Setup -> Preemption Model -> Select Preemptible Kernel
// use </> to search "Preempt"; need the symbol PREEMPT [=y]
make -j 12
sudo make modules_install
sudo make install
sudo vi /etc/default/grub
GRUB_DEFAULT='4.19.132-rt59'
sudo update-grub
sudo reboot
```

Used the newest kernel patch version 4.19.132-rt59 and the matching linux kernel  
Verify that the installation was correct: uname -a -> PREEMPT should appear  

