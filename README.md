# popt-dev Parallelization Optimization (dev)

## Requires

[Python 3.7](https://www.python.org/downloads/release/python-376/)
[spdlog](https://github.com/gabime/spdlog)

```shell
(osx) brew install spdlog
(ubuntu)
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j8
sudo mv ../include/spdlog /usr/local/include/
```

## Installation

```shell
git clone --recurse-submodules https://github.com/upoque/popt-dev.git
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
cd samples/dev
mkdir build
cd build
cmake ..
make
./dev
```

## popt-gui

```shell
sudo apt-get install python3-pyqt5 python3-numpy python3-matplotlib
pip3 install -e .
```
