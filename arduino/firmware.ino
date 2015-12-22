// ros libs
#include <ros.h>
#include <std_msgs/UInt16.h>

// other libs
#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

ros::NodeHandle  nh;

float rightMotorSpeed = 0;
float leftMotorSpeed = 0;

void driveMotorsCb( const std_msgs::UInt16& cmd_msg){
  rightMotorSpeed =
  leftMotorSpeed =

}


ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

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
