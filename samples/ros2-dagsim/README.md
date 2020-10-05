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

## Writing Launch File
You can add entry / middle / leaf nodes by adding Node Class in LaunchDescription.

You can set parameter for each node.

* child_num : # of child nodes (available for entry_node, middle_node)
* child_idx : index of child nodes (available for entry_node, middle_node)
* parent_num : # of parent nodes (available for middle_node, leaf_node)
* parent_idx : index of parent nodes (available for middle_node, leaf_node)
* waste_time : waste time (ms)

For child node which has multiple parents, it publish topics after subscribing all topics from parents.

For now, you should name each node like 'nodeX' (X : node index) and synchronize parent_idx, child_idx with that number.

For more detail, reference launch files in `launch` folder.


## Example
```
ros2 launch launch/simple_chain.launch.py
```

You can verify each node and topic with below command
```
ros2 run rqt_graph rqt_graph
```


![simple_chain](https://user-images.githubusercontent.com/44594966/95045533-333cca00-071d-11eb-83f1-117b9fe79352.png)

