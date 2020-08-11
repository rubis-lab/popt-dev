# popt-dev Parallelization Optimization (dev)

## Requires

[Python 3.7](https://www.python.org/downloads/release/python-376/)

## Installation

## popt-gui

```shell
git clone --recurse-submodules https://github.com/upoque/popt-dev
cd popt-dev
pip3 install -e .
```

## rts shared library

```shell
cd rts
mkdir build
cd build
cmake ..
make
```

## eg1

```shell
cd eg1
mkdir build
cd build
cmake ..
make
./EG1
```
