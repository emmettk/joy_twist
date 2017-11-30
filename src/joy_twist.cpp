/*WHOI ROS Short Course Module 3 Joystick Assignment #3
 *Emmett Krupczak
 *30 Nov 2017
 *This subscribes to a sensor_msgs/Joy topic /joy 
 *and publishes to geometry_msgs/Twist topic /edumip/cmd
 *Inspired by wiki.ros.org/joy/Tutorials/WritingTeleopNode
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class JoyEduMip
{
public:
  JoyEduMip();

  //Take a joy message
private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  //create a node handler, publisher and subscriber
  ros::NodeHandle node_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
  int linear_, angular_;
  double l_scale_, a_scale_;
};

JoyEduMip::JoyEduMip():
  //Make some parameters to contain the variables that the joystick will tell me
  linear_(1),
  angular_(2)
  //  a_scale_(3),
  //l_scale_(4)
{
  node_.param("axis_linear", linear_, linear_);
  node_.param("axis_angular", angular_, angular_);
  node_.param("scale_linear", a_scale_, a_scale_);
  node_.param("scale_angular", l_scale_, l_scale_);

  //Publish to /edumip/cmd
  pub_ = node_.advertise<geometry_msgs::Twist>("edumip/cmd", 1);

  //Subscribe to /joy
  sub_ = node_.subscribe<sensor_msgs::Joy>("joy", 10, &JoyEduMip::joyCallback, this);
}

void JoyEduMip::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];
  pub_.publish(twist);
}

int main(int argc, char** argv)
  {
    ros::init(argc, argv, "joy_edumip");
    JoyEduMip joy_edumip;
    ros::spin();
}
    
  

