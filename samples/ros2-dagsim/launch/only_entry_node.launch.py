from launch import LaunchDescription
from launch.substitutions import EnvironmentVariable
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
	SetEnvironmentVariable(name='LD_LIBRARY_PATH',
	value=[EnvironmentVariable('LD_LIBRARY_PATH'),
	'/usr/local/lib', '/home/nvidia/ros2_dashing/install/rclcpp/lib']),
        Node(
            package='ros2-dagsim',
            node_namespace='simple_chain',
            node_executable='entry_node',
            node_name='A',
	    parameters=[
		{"child_num" : 2}
	    ],
	    prefix=["sudo -E"]
        )
    ])
