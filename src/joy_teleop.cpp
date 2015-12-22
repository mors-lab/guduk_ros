#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class GudukJoyTeleop
{
public:
  GudukJoyTeleop();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle ph_, nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


GudukJoyTeleop::GudukJoyTeleop():
  linear_(3),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("guduk/cmd_vel", 1, true);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &GudukJoyTeleop::joyCallback, this);

}

void GudukJoyTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

  geometry_msgs::Twist vel_;
  vel_.angular.z = 400*joy->axes[angular_];
  vel_.linear.x = 400*joy->axes[linear_];
  vel_pub_.publish(vel_);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy_teleop");
  GudukJoyTeleop teleop;

  ros::spin();
}
