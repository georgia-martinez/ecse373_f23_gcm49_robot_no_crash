#include "sensor_msgs/LaserScan.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

ros::Publisher *p_pub;

geometry_msgs::Twist des_vel;
geometry_msgs::Twist cmd_vel;

int main(int argc, char* argv[]) {
	ros::init(argc, argv, "lab4");
}
