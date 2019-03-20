#pragma once

#include <frc/WPILib.h>
#include <frc/TimedRobot.h>
#include "Tankdrive.h"
#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <Tankdrive.h>
#include <cameraserver/CameraServer.h>
#include <frc/DigitalInput.h>
using namespace frc;

class Robot : public frc::TimedRobot {
 public:

  //encoders
  Encoder *leftEncoder;
  Encoder *rightEncoder;

  //pneumatics
  Solenoid *solenoid;

  //joysticks
  Joystick *j_left;
  Joystick *j_right;
  Joystick *j_lift;

  //spark motor controllers
  Spark *m_left1; //left wheel 0
  Spark *m_left2; //left wheel 1
  
  Spark *m_right1; //right wheel 2
  Spark *m_right2; //right wheel 3

  Spark *m_lift1;  //red line motor 4
  Spark *m_lift2;  //red line motor 5

  Spark *m_arm1;  //intake Left  
  Spark *m_arm2;  //intake Right


  Compressor *compressor;
  
  OECPigeonIMU *myGyro; //gyro

  SmartDashboard *smartDashboard; //smartdash

  double RobotSpeed; //sensitivity


 
  double liftSensitivity; //lift speed

  Tankdrive *tdrive; //tankdrive

  //switches

  DigitalInput *switch0;		// switch for center or side start
	DigitalInput *switch1;		// switch for left and right
  DigitalInput *switch2;		// switch for 2nd Hatch/Stop
	DigitalInput *switch3;		// switch for left or right (drive back)
	DigitalInput *switch4;		// center or side (place second hatch)
	DigitalInput *switch5;   // switch for far or close hatch (place second hatch)


  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
};
