/* Basic Robot Controls

Blue Joystick: Left Wheels
Blue Joystick Button 2: Straight Backwards
Blue Joystick Z: Arm Wheels Sensitivity

Red Joystick: Right Wheels
Red Joystick Button 2: Straight Forwards
Red Joystick Z: Wheels Sensitivity

Lift Joystick: Lift Controls
Lift Joystick Button 2: Intake
Lift Joystick Trigger: Outtake
Lift Joystick Z: Lift Speed
*/

#include "Robot.h"
#include "Tankdrive.h"

void Robot::RobotInit() {
    //set Camera Settings and send it to smartDashboard
    camera= CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(256,144);
    camera.SetExposureAuto();
    camera.SetFPS(30);
    camera.SetBrightness(20);
    smartDashboard->init();

   //tdrive = new Tankdrive (1,0,1,2,3,4,myGyro,smartDashboard);
   //myGyro = new OECPigeonIMU (01);
}

void Robot::AutonomousInit() {
    /*tdrive -> SetPower(0.2,-0.2); //right motor is negative
    Wait(2);
    tdrive -> SetPower(0.0,0.0);
    Wait(2);*/
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() { 
    smartDashboard -> PutNumber("Sensitivity: ",wheelSensitivity* -100); //displays the speed of the wheels
    smartDashboard -> PutNumber("Lift Sensitivity: ", liftSensitivity * -100); //displays the speed of the lift
    smartDashboard -> PutNumber("Arm Wheel Speed:", armWheelSpeed * -100); //displays the intake speed
    Wait (2);

    while (IsOperatorControl() && IsEnabled()) {
    wheelSensitivity = (j_right.GetZ()-1)/2; //wheel sensitivity
    liftSensitivity = (j_lift.GetZ()-1)/2; //lift sensitivity
    armWheelSpeed = (j_left.GetZ()-1)/2; //intake speed

        //straight forwards
        if (j_right.GetRawButton(2)) { 
            m_left1.Set(wheelSensitivity);
            m_left2.Set(wheelSensitivity);
            m_right1.Set(wheelSensitivity);
            m_right2.Set(wheelSensitivity);
        }

        //straight backwards
        else if (j_left.GetRawButton(2)) { 
            m_left1.Set(-wheelSensitivity);
            m_left2.Set(-wheelSensitivity);
            m_right1.Set(-wheelSensitivity);
            m_right2.Set(-wheelSensitivity);
        }

        else {
            //left wheels controls
            m_left1.Set(wheelSensitivity * j_left.GetY()); 
            m_left2.Set(wheelSensitivity * j_left.GetY());

            //right wheels controls
            m_right1.Set(-wheelSensitivity * j_right.GetY());
            m_right2.Set(-wheelSensitivity * j_right.GetY());

            //lift controls
            m_lift1.Set(-liftSensitivity * j_lift.GetY());
            m_lift2.Set(-liftSensitivity * j_lift.GetY());
        }

        //intake
        if (j_lift.GetRawButton(1)) {
            m_arm1.Set(armWheelSpeed); 
            m_arm2.Set(armWheelSpeed);
        }

        //outake
        else if (j_lift.GetRawButton(2)) {
            m_arm1.Set(-armWheelSpeed); 
            m_arm2.Set(-armWheelSpeed);
        }
        
        //pneumatic controls
        else if (j_lift.GetRawButton(3)){
            solenoid.Set(true);
            Wait(.1);
            solenoid.Set(false);
        }
    }
}

void Robot::TestInit() {
}

void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS

int main() {
    return frc::StartRobot<Robot>(); 
    }
#endif