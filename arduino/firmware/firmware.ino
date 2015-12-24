// ros libs
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int16MultiArray.h>

// other libs
#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

ros::NodeHandle  nh;

int rightMotorVel = 0;
int leftMotorVel = 0;

void driveMotorsCb(const std_msgs::Int16MultiArray& motorVels){

  rightMotorVel = motorVels[0];
  leftMotorVel = motorVels[1];

  
}


ros::Subscriber<std_msgs::Int16MultiArray> sub("/guduk/cmd_vel", driveMotorsCb);

void setup(){

  md.init();                  // Initialize motor driver
  delay(50);                  // Delay for 50ms

  nh.initNode();
  nh.subscribe(sub);

}

void loop(){
  // md.setM1Speed(leftMotorSpeed);
  // md.setM2Speed(rightMotorSpeed);
  nh.spinOnce();
  delay(1);
}
