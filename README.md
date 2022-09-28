Mini Project

#Simulate a differential drive robot obtaining cyclic commands to move around.

1. A ROS2 package of type C++ is created:
                
                ros2 pkg create my_cpp_pkg --build-type ament_cmake 
                
Changes are made in Cmakelist and Package.xml file

For the Project, A differnetial robot called Dolly is taken, which is launced on Ignition:
 		
 		git clone https://github.com/chapulina/dolly.git


The launch file is modified by removing some unneccessary nodes.

3. Source the bash:

		source /opt/ros/galactic/setup.bash
		. install/setup.bash
		
4. Build the package:

		Colcon build --symlink-install --packages-select dolly_ignition

5. Launch Dolly in the Ignition:

               ros2 launch dolly_ignition dolly.launch.py
               
6.A cpp is created and publisher node is written:

		touch publisher.cpp

7. Add the node to the main Launch file, like this:

  		pubs = Node(
    	package='dolly_ignition',
    	executable='reading_laser',
    	output='screen',parameters = [config],
    	remappings=[
            ('laser_scan', '/dolly/laser_scan'),('cmd_vel', '/dolly/cmd_vel')]
    )
    
8. Dump the parameters in to a .yaml file using:
 
 		ros2 param dump /your_amazing_node
 		
Direct change of parameters can be made using .yaml from now on


9. source the bash and Colcon build again.

10.   		ros2 launch dolly_ignition dolly.launch.py

11. Push the repository to Github by Creating a personal access token:
		
		Create a repository in Github
		git init (in the package)
		git pull .
		git commit -m "message"
		git remode add origin "http link of repository"
		git push origin master
		
 

                
