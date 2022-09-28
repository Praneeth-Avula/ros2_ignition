import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():

    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    pkg_dolly_gazebo = get_package_share_directory('dolly_gazebo')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py')
        )
    )
    pubs = Node(
    	package='dolly_ignition',
    	executable='reading_laser',
    	output='screen',
    	remappings=[
            ('laser_scan', '/dolly/laser_scan'),('cmd_vel', '/dolly/cmd_vel')]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world',
            default_value=[os.path.join(pkg_dolly_gazebo, 'worlds', 'dolly_empty.world'), ''],
            description='SDF world file',
        ),
        gazebo,
        pubs
    ])
