#include "sensor_msgs/LaserScan.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

ros::Publisher cmd_vel_pub;

sensor_msgs::LaserScan lidar_msg;
geometry_msgs::Twist new_vel_msg;

double wall_dist;

void lidarCallback(const sensor_msgs::LaserScan msg) {
	lidar_msg = msg;
}

void velocityCallback(const geometry_msgs::Twist msg) {
	
	new_vel_msg = msg;
	
	float x_pos = msg.linear.x;
	int RANGE = 20;
	
	// If the robot is moving forwards
	if (x_pos > 0) {
	
		// Check the lasers in front of the robot
		int middle_index = lidar_msg.ranges.size() / 2;		
		int start = middle_index - RANGE;
		int end = middle_index + RANGE;
		
		float min_dist = lidar_msg.ranges[start]; // minimum distance from wall
		
		for (int i = start; i < end; i++) {
			if (min_dist > lidar_msg.ranges[i]) {
				min_dist = lidar_msg.ranges[i];
			}
		}
		
		// If wall is nearby, rotate robot to not face wall
		if (min_dist < wall_dist) {
			new_vel_msg.linear.x = 0;
			new_vel_msg.angular.z = 0.5;
		} else {
			new_vel_msg = msg;
		}
	}
	
	cmd_vel_pub.publish(new_vel_msg);
}

int main(int argc, char* argv[]) {
	ROS_INFO("Starting smart teleoperation");
	ros::init(argc, argv, "smart_teleop");
	
	ros::NodeHandle n;
	
  	cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  	ros::Subscriber laser_sub = n.subscribe("laser_1", 1000, lidarCallback);  	
  	ros::Subscriber des_vel_sub = n.subscribe("des_vel", 1000, velocityCallback);
  	
	// Loop to check the wall_dist param
    ros::Rate rate(1);
    
    while (ros::ok()) {
        n.getParamCached("wall_dist", wall_dist);
        ROS_INFO("wall_dist param: %2.2f", wall_dist);

        ros::spinOnce();
        rate.sleep();
    }

	return 0;	
}
