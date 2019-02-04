/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/Phoenix.h>

#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
using namespace frc;
class Robot : public frc::TimedRobot {
 public:



  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;

  
cs::UsbCamera camera{}; 

  SmartDashboard *smartDashboard;

  double ant;
  
  Joystick stick1{0}; //left
  Joystick stick2{1}; //right
  Joystick stick3{2}; //arm

  Spark m_left{1};
  Spark m_right{0};
  Spark m_updown{3};

  double gyro[3];
  double x = -.65;
  double A = -.65;

  Talon wheels{2};

  frc::Relay visionlight {0, frc::Relay::Direction::kForwardOnly};

  PigeonIMU myGyro{01}; 

  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
		
};
