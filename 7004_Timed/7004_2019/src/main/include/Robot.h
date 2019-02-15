#pragma once

#include <frc/WPILib.h>
#include <frc/TimedRobot.h>
#include "Tankdrive.h"
#include <ctre/Phoenix.h>
#include <Tankdrive.h>
using namespace frc;

class Robot : public frc::TimedRobot {
 public:

  //joysticks
  Joystick j_left{0};
  Joystick j_right{1};
  Joystick j_lift{2};

  //spark motor controllers
  Spark m_left1{0}; //left wheel 0
  Spark m_left2{1}; //left wheel 1
  
  Spark m_right1{2}; //right wheel 2
  Spark m_right2{3}; //right wheel 3

  Spark m_lift1{4};  //Red Line Motor 4
  Spark m_lift2{5};  //Red Line Motor 5

  Spark m_arm1{6};  //intake Left  
  Spark m_arm2{7};  //intake Right
  

  double sens; //sensitivity
 
  double liftSpeed; //lift speed

  double armWheelSpeed; //intake speed

  OECPigeonIMU *myGyro; //gyro

  //int gyroArray [3] = myGyro -> GetYawPitchRoll();

  cs::UsbCamera camera{}; //camera

  SmartDashboard *smartDashboard; //smartdash
  
  Tankdrive *tdrive; //tankdrive

  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
};
