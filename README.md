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
cd ..
mv ./spdlog /usr/local/include/
```

## Installation

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
git clone --recurse-submodules https://github.com/upoque/popt-dev.git
cd popt-dev
pip3 install -e .
```
