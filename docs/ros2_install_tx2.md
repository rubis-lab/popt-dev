## ROS2 Install on Jetson TX2
This will install [ROS2 Eloquent Elusor](https://index.ros.org/doc/ros2/Installation/Eloquent/) using debian packages  
  
Setup Locale
``` shell
$ sudo locale-gen en_US en_US.UTF-8
$ sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
$ export LANG=en_US.UTF-8
```
Setup Sources & add the repository to sources list
``` shell
$ sudo apt update && sudo apt install curl gnupg2 lsb-release
$ curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
$ sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
```
Install ROS2 Packages
```
$ sudo apt update
# ~ 1500MB, 10 mins on TX2
$ sudo apt install ros-eloquent-desktop
# sudo apt install ros-eloquent-ros-base
# downloading ros-eloquent-desktop contains ros-base
```
Talker & Listner (two terminals req'd)
```
$ source /opt/ros/eloquent/setup.bash
$ ros2 run demo_nodes_cpp talker
$ ros2 run demo_nodes_py listener
```
