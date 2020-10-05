from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2-dagsim',
            node_namespace='simple_chain',
            node_executable='entry_node',
            node_name='node0',
	    parameters=[
		{
			"child_num" : 1,
			"child_idx" : [1],
			"waste_time" : 1000 # ms
		}
	    ],
        ),
	Node(
            package='ros2-dagsim',
            node_namespace='simple_chain',
            node_executable='leaf_node',
            node_name='node1',
		output='screen',
	    parameters=[
		{
			"parent_num" : 1,
			"parent_idx" : [0],
			"waste_time" : 1000 # ms
		}
	    ],
        )
    ])
