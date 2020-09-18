# How to build image with DockerFile


## Requirement
* Docker


## Usage
```
$ docker build -f <dockerfile name> -t <image name and tag> .

# Example
$ docker build -f l4t-ros2-dashing-base -t ros2:base .

```

- . is build context on your container. You can set to other path.

# How to run with your image
```
$ docker run <image name>:<tag name> <command>
```
You can find more options [here](https://docs.docker.com/engine/reference/run/)
