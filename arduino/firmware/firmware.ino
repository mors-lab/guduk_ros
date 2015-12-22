// ros libs
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Twist.h>

// other libs
#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

ros::NodeHandle  nh;

float rightMotorSpeed = 0;
float leftMotorSpeed = 0;

void driveMotorsCb( const geometry_msgs::Twist& cmd_vel){
  rightMotorSpeed = cmd_vel.linear.x;
  leftMotorSpeed = cmd_vel.linear.x;

}


ros::Subscriber<geometry_msgs::Twist> sub("/guduk/cmd_vel", driveMotorsCb);

void setup(){

  md.init();                  // Initialize motor driver
  delay(50);                  // Delay for 50ms

  nh.initNode();
  nh.subscribe(sub);

}

void loop(){
  md.setM1Speed(leftMotorSpeed);
  md.setM2Speed(rightMotorSpeed);
  nh.spinOnce();
  delay(1);
}
