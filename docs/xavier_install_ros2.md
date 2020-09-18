# This will install...
[ROS 2 Dashing](https://index.ros.org/doc/ros2/Installation/Dashing/Linux-Development-Setup/)

## Set locale
```
$ locale  # check for UTF-8
$ sudo apt update && sudo apt install locales
$ sudo locale-gen en_US en_US.UTF-8
$ sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
$ export LANG=en_US.UTF-8
$ locale  # verify settings
```

## Add the ROS 2 apt repository

```
$ sudo apt update && sudo apt install curl gnupg2 lsb-release
$ curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
$ sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
```

## Install development tools and ROS tools
```
$ sudo apt update && sudo apt install -y \
  build-essential \
  cmake \
  git \
  python3-colcon-common-extensions \
  python3-pip \
  python-rosdep \
  python3-vcstool \
  wget
# install some pip packages needed for testing
$ python3 -m pip install -U \
  argcomplete \
  flake8 \
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
  pytest \
  pytest-cov \
  pytest-runner \
  setuptools
# install Fast-RTPS dependencies
$ sudo apt install --no-install-recommends -y \
  libasio-dev \
  libtinyxml2-dev
# install Cyclone DDS dependencies
$ sudo apt install --no-install-recommends -y \
  libcunit1-dev
```

## Get ROS 2 code
```
$ mkdir -p ~/ros2_dashing/src
$ cd ~/ros2_dashing
$ wget https://raw.githubusercontent.com/ros2/ros2/dashing/ros2.repos
$ vcs import src < ros2.repos
```

## Install dependencies using rosdep
```
$ sudo rosdep init
$ rosdep update
$ rosdep install --from-paths src --ignore-src --rosdistro dashing -y --skip-keys \
  "console_bridge fastcdr fastrtps libopensplice67 libopensplice69 rti-connext-dds-5.3.1 urdfdom_headers"
```

## Build the code in the workspace
```
$ cd ~/ros2_dashing/
$ colcon build --symlink-install
```

## Verification
```
# (terminal 1)
$ . ~/ros2_dashing/install/setup.bash
$ ros2 run demo_nodes_cpp talker

# (terminal 2)
$ . ~/ros2_dashing/install/setup.bash
$ ros2 run demo_nodes_py listener
```

It is recommend to add alias `. ~/ros2_dashing/install/setup.bash` in your `~/.bashrc`

