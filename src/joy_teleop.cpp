#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int16MultiArray.h>


class GudukJoyTeleop
{
public:
  GudukJoyTeleop();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle ph_, nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  int rightMotorSpeed, leftMotorSpeed;
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

  vel_pub_ = nh_.advertise<std_msgs::Int16MultiArray>("guduk/cmd_vel", 1, true);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &GudukJoyTeleop::joyCallback, this);

}

void GudukJoyTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

  // geometry_msgs::Twist vel_;
  std_msgs::Int16MultiArray motorSpeeds;
  motorSpeeds.data.clear();


  if (joy->axes[linear_] == 0 && joy->axes[angular_] > 0) {
    rightMotorSpeed = 400*joy->axes[angular_];
    leftMotorSpeed = 400*(1 - joy->axes[angular_]);
  }
  else  if (joy->axes[linear_] == 0 && joy->axes[angular_] < 0) {
    /* code */
  }

  else if (joy->axes[linear_] != 0 && joy->axes[angular_] == 0) {
    rightMotorSpeed = 400*joy->axes[linear_];
    leftMotorSpeed = 400*joy->axes[linear_];
  }
  // motorSpeeds[0].label = "right";
  // motorSpeeds[0].data = rightMotorSpeed;
  // motorSpeeds[1].label = "left";
  // motorSpeeds[1].data = leftMotorSpeed;

  vel_pub_.publish(motorSpeeds);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy_teleop");
  GudukJoyTeleop teleop;

  ros::spin();
}
