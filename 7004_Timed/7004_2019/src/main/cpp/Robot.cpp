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

tdrive -> SetPower(0.2,-0.2);//right motor is neg
Wait(2);
tdrive -> SetPower(0.0,0.0);
Wait(2);

}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() { 
    smartDashboard -> PutNumber("Sensitivity: ", sens * -100); //display the speed of the wheels
    smartDashboard -> PutNumber("Lift Speed: ", liftSpeed * -100); //displays the speed of the lift
    smartDashboard -> PutNumber("Intake Speed:", armWheelSpeed * -100); //displays the intake speed
    Wait (2);

    while (IsOperatorControl() && IsEnabled()) {
    sens = (j_right.GetZ()-1)/2; //wheel sensitivity
    liftSpeed = (j_lift.GetZ()-1)/2; //lift sensitivity
    armWheelSpeed = (j_left.GetZ()-1)/2; //intake speed

        //straight forwards
        if (j_left.GetRawButton(2)) { 
            m_left1.Set(sens);
            m_left2.Set(sens);
            m_right1.Set(-sens);
            m_right2.Set(-sens);
        }

        //straight backwards
        else if (j_right.GetRawButton(2)) { 
            m_left1.Set(-sens);
            m_left2.Set(-sens);
            m_right1.Set(sens);
            m_right2.Set(sens);
        }

        else {
            //left controls
            m_left1.Set(sens * j_left.GetY()); 
            m_left2.Set(sens * j_left.GetY());

            //right controls
            m_right1.Set(-sens * j_right.GetY());
            m_right2.Set(-sens * j_right.GetY());

            //lift controls
            m_lift1.Set(-liftSpeed * j_lift.GetY());
            m_lift2.Set(liftSpeed * j_lift.GetY());
        }

        /*
        while (j_lift.GetRawButton(2)) { //If button one is pressed then intake 

            if (j_lift.GetRawButton(1)) {
                m_lift1.Set(armWheelSpeed); 
                m_lift2.Set(armWheelSpeed); 
            }

            else {
                m_lift1.Set(armWheelSpeed); 
                m_lift2.Set(armWheelSpeed); 
            }

        }
        */

       //arm wheel controls
       while (j_lift.GetRawButton(1)) {
           if (j_lift.GetRawButton(2)) {
                //intake
                m_arm1.Set(armWheelSpeed); 
                m_arm2.Set(armWheelSpeed);
            }
            else {
                //outake
                m_arm1.Set(-armWheelSpeed); 
                m_arm2.Set(-armWheelSpeed);
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
