#include "Robot.h"

void Robot::RobotInit() {
    camera= CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(426,240);
    camera.SetExposureAuto();
    camera.SetFPS(30);
    camera.SetBrightness(20);
    smartDashboard->init();
}

void Robot::AutonomousInit() {

}
void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {

}
void Robot::TeleopPeriodic() {
    Wait(2);
    myGyro.GetYawPitchRoll(gyro);
    myGyro.SetYaw(0);
    double sens = (stick2.GetZ() + 1) / 2; //sensitivity 

     while(IsOperatorControl() && IsEnabled()) {
         visionlight.Set(frc::Relay::Value::kOn);


            if (stick2.GetRawButton(2)) {
                myGyro.GetYawPitchRoll(gyro);
                if (stick2.GetRawButton(1)){
                myGyro.SetYaw(0);
                ant = (gyro[0]);
            }

            if (gyro[0] < ant + .05 && gyro[0] > ant - .05 && stick2.GetRawButton(2)) {
                m_left.Set(A*stick2.GetY());
                m_right.Set(x*stick2.GetY());
                m_updown.Set(.65*stick3.GetY());
            }
			else if (gyro[0] > ant + 0.5) {
                x = x - .001;
			}
			else if (gyro[0] < ant - 0.5) {
				A = A - .001;
			}
            m_left.Set(A*stick2.GetY());
            m_right.Set(x*stick2.GetY());
            m_updown.Set(0.4*stick3.GetY());
         }	
         else {
            m_left.Set(-((stick2.GetZ()+1)/2) * stick1.GetY()); //left wheels
            m_right.Set(-((stick2.GetZ()+1)/2) * stick2.GetY()); //right wheels
            m_updown.Set(0.65 * stick3.GetY()); //arm controls
            while(stick3.GetRawButton(1)) { //arm wheels
                if (stick3.GetRawButton(2)) {
                    wheels.Set(0.99); //outake
                }
                else {
                    wheels.Set(-0.25); //intake
                }
            }
            if (stick3.GetRawButton(8)){
                myGyro.SetYaw(0);
            }
            else{
                myGyro.GetYawPitchRoll(gyro);
                smartDashboard -> PutNumber("Gyro", gyro[0]);
            }
            wheels.Set(0);
            //smartDashboard -> PutNumber("Stick 3", stick3.GetZ());
            double x = gyro[0];
            if (x > 360 || x < -360){
                myGyro.SetYaw(0);
            }
            if (stick3.GetRawButton(9)){
                TeleopPeriodic();
            }
            smartDashboard -> PutNumber("Throttle", sens);
         }
     }

}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { 
    return frc::StartRobot<Robot>(); 
}
#endif
