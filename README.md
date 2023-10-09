# ECSE 373 Laboratory #4

Run the smart_teleop node by itself:

`roslaunch robot_no_crash robot_supervisor.launch`

Run the smart_teleop node with stdr_launchers and rqt_gui:

`roslaunch robot_no_crash lab4.launch`

With the second launch method, the optional param `robot_ns` can be set to change the robot namespace (default is robot0). 

When the node is running, you can update the `wall_dist` param to change how sensitive the wall detection is by running the following (default is 1):

`rosparam set /<robot_ns>/wall_dist <value>`
