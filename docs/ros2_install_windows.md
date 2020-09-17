# ROS2 Install on Jetson TX2
This will install [ROS2 Dashing Diademata](https://index.ros.org/doc/ros2/Installation/Dashing/Windows-Install-Binary/) using debian packages
You'd better install windows PowerShell at Microsoft appstore

## Install Chocolatey Software
Follow the steps on [choco](https://chocolatey.org/install)

## Install Python 3.7.5
You can download installation file on [python](https://www.python.org/downloads/release/python-375/)
Check the version and download executable installer

## Install  Visual C++ Redistributables
On powershell

```shell
choco install -y vcredist2013 vcredist140
```

## Install OpenSSL
You can download on [open ssl](https://slproweb.com/products/Win32OpenSSL.html)
Should download **Win64 OpenSSL v1.0.2u**

You will need to append the OpenSSL-Win64 bin folder to your PATH. 
You can do this by clicking the Windows icon, typing “Environment Variables”, then clicking on “Edit the system environment variables”. 
In the resulting dialog, click “Environment Variables”, then click “Path” on the bottom pane, finally click “Edit” and add the path below.

## Install Visual Studio
You can download community version on [visual studio](https://visualstudio.microsoft.com/ko/downloads/)
An easy way to make sure they’re installed is to select the **Desktop development with C++** workflow during the install.

**Do not select windows visual c++ tools for cmake and unselect two bottom one.**

## Install OpenCV
Download OpenCV click [here](https://github.com/ros2/ros2/releases/download/opencv-archives/opencv-3.4.6-vc16.VS2019.zip)

You have to extend the PATH variable to **C:\opencv\x64\vc16\bin**

## Install dependencies
- Install cmake with using choco

```shell
choco install -y cmake
```

You will need to append the CMake bin folder **C:\Program Files\CMake\bin** to your PATH.

- Download all *.nupkg on [here](https://github.com/ros2/choco-packages/releases/tag/2020-02-24)

```shell
choco install -y -s <PATH\TO\DOWNLOADS\> asio cunit eigen tinyxml-usestl tinyxml2 log4cxx
```

<PATH\TO\DOWNLOADS> => Your download folder's path

- You must also install some python dependencies for command-line tools

```shell
python -m pip install catkin_pkg empy lark-parser lxml numpy opencv-python pyparsing pyyaml setuptools
```

- You must also install rqt dependencies

```shell
python -m pip install -U pydot PyQt5
```

## Downloading ROS 2

 Download [here](https://github.com/ros2/ros2/releases)


## Environment setup
Create dev foler in C drive and move the ros2-widows to dev

```shell
call C:\dev\ros2-windows\local_setup.bat
```