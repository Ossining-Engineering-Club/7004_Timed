#include "Robot.h"
#include "Tankdrive.h"

void Robot::RobotInit() {
    //Set Camera Settings and send it to smartDashboard
    camera= CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(426,240);
    camera.SetExposureAuto();
    camera.SetFPS(30);
    camera.SetBrightness(20);
    smartDashboard->init();

    tdrive = new Tankdrive (1,0,1,2,3,4,myGyro,smartDashboard);
    myGyro = new OECPigeonIMU (01);
}

void Robot::AutonomousInit() {

}
void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {

}
void Robot::TeleopPeriodic() {
    Wait (2);
    while(IsOperatorControl()) {
        while(IsOperatorControl() && IsEnabled()) {

            sens = (j_lift.GetZ()-1)/2;
            smartDashboard -> PutNumber("Sensitivity: ", sens * -100);

            if(j_left.GetRawButton(2)) {
                m_left.Set(-sens);
                m_right.Set(-sens);
            }

            else if (j_right.GetRawButton(2)) {
                m_left.Set(sens);
                m_right.Set(sens);
            }

            else {
                m_left.Set(sens * j_right.GetY());               //when left joystick pushed, rotate left wheels
                m_right.Set(sens * j_left.GetY());               //when right joystick pushed, rotate right wheels
                m_lift.Set(0.20 * j_lift.GetY());                //move lift up and down
            }
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
