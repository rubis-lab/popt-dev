# [ROS 2 Foxy Fitzroy](https://index.ros.org/doc/ros2/Installation/Foxy/)

[Install from source](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Development-Setup/)

Ubuntu 20.04

Locale setup

```
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
```

Add apt repository

```
sudo apt update && sudo apt install curl gnupg2 lsb-release
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
```

Install dev tools
```
sudo apt install -y \
  build-essential \
  cmake \
  git \
  python3-pip \
```

dev tool (continued..)
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://pool.sks-keyservers.net --recv-key 0xAB17C654
sudo apt-get update
sudo apt-get install python3-vcstool python3-rosdep python3-colcon-common-extensions  
```

Test dependencies

```
pip3 install\
  argcomplete \
  flake8-blind-except \
  flake8-builtins \
  flake8-class-newline \
  flake8-comprehensions \
  flake8-deprecated \
  flake8-docstrings \
  flake8-import-order \
  flake8-quotes \
  pytest-repeat \
  pytest-rerunfailures \
  pytest
```

Fast-RTPS 
```
sudo apt install --no-install-recommends -y \
  libasio-dev \
  libtinyxml2-dev
```

Cyclone DDS dependencies
```
sudo apt install --no-install-recommends -y \
  libcunit1-dev
```

## hoxy
~/.local/bin script not on PATH


## ROS2 code
```
mkdir -p ~/ros2_foxy/src
cd ~/ros2_foxy
wget https://raw.githubusercontent.com/ros2/ros2/foxy/ros2.repos
vcs import src < ros2.repos
```

ROS2 dependencies
```
sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src --rosdistro foxy -y --skip-keys "console_bridge fastcdr fastrtps rti-connext-dds-5.3.1 urdfdom_headers"
```