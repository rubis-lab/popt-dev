# popt-dev Parallelization Optimization (dev)

## Requires

[Python 3.7](https://www.python.org/downloads/release/python-376/)
[spdlog](https://github.com/gabime/spdlog)

```shell
brew install spdlog (osx)
sudo apt-get install libspdlog-dev (ubuntu)
```

## Installation

## popt-gui

```shell
git clone --recurse-submodules https://github.com/upoque/popt-dev.git
cd popt-dev
pip3 install -e .
```

## rts shared library

```shell
cd rts
mkdir build
cd build
cmake ..
make -j8
make install (osx)
sudo make install (ubuntu)
```

## Examples

```shell
cd eg1
mkdir build
cd build
cmake ..
make
./EG1
```
