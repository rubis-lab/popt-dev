# ROS 2 DAG Simulator

## Requirement
- rts library

You must add `/usr/local/lib` to `LD_LIBRARY_PATH` environment variable.

(Recommnend to add below line in ~/.bashrc)
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

## Build

```
colcon build --packages-select ros2-dagsim
```

## Run
```
# Get path from bash file
. install/setup.bash

# You can run each node or launch file
ros2 run ros2-dagsim <node name>
ros2 launch launch/<launch file name>
```

## Example
```
ros2 launch launch/simple_chain.launch.py
```
