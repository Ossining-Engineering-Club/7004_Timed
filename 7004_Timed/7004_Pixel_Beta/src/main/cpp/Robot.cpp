/* Basic Robot Controls

Blue Joystick: Left Wheels
Blue Joystick Button 2: Straight Backwards
Blue Joystick Z: Arm Wheels Sensitivity

Red Joystick: Right Wheels
Red Joystick Button 2: Straight Forwards
Red Joystick Z: Wheels Sensitivity

Lift Joystick: Lift Controls (Forwards = Down, Backwawrds = Up)
Lift Joystick Trigger: Outtake
Lift Joystick Button 2: Intake
Lift Joystick Button 3: Piston Controls
Lift Joystick Button 10: Compressor On
Lify Joystick Button 11: Compressor Off
Lift Joystick Z: Lift Speed
*/

#include "Robot.h"
#include "Tankdrive.h"
#include "frc/Compressor.h"

cs::UsbCamera Camera0;
cs::UsbCamera Camera1;
cs::VideoSink server;
void Robot::RobotInit()
{
    Camera0 = CameraServer::GetInstance()->StartAutomaticCapture(0);
    Camera1 = CameraServer::GetInstance()->StartAutomaticCapture(1);
    Camera0.SetResolution(320, 240);
    Camera0.SetFPS(15);
    Camera0.SetExposureAuto();
    Camera1.SetResolution(320, 240);
    Camera1.SetFPS(15);
    Camera1.SetExposureAuto();
    server = CameraServer::GetInstance()->GetServer();

    Wait(2);

    myGyro = new OECPigeonIMU(01); //gyro

    leftEncoder = new Encoder(0, false, Encoder::EncodingType::k4X); //left encoders
    rightEncoder = new Encoder(1, false, Encoder::EncodingType::k4X); //right encoders

    solenoid = new Solenoid (00); //piston

    m_left1 = new Spark(0); 
    m_left2 = new Spark(1);
    m_right1 = new Spark(2);
    m_right2 = new Spark(3);

    j_left = new Joystick (0); //left joystick
    j_right = new Joystick (1); //right joystick
    j_lift = new Joystick (2); //lift joystick

    //lift motors
    m_lift1 = new Spark(4);
    m_lift2 = new Spark(5); 

    //arm motors
    m_arm1 = new Spark(6);
    m_arm2 = new Spark(7);

    cs::UsbCamera camera0;
    cs::UsbCamera camera1;
    
    compressor = new Compressor(0); //compressor
}

void Robot::AutonomousInit() {
    tdrive -> SetThrottle(0.6); 
    tdrive -> SetPower(0.5, 0.5);
    tdrive->ResetEncoders();
    tdrive->DriveGyro(0.3, 80, 0.25, true);
    smartDashboard->PutNumber("Left Encoder Final", tdrive->GetLeftEncoderDist());
    smartDashboard->PutNumber("Right Encoder Final", tdrive->GetRightEncoderDist());
}
void Robot::AutonomousPeriodic() {
    if(switch0->Get()){

    }
    else {
        
    }
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() { 

    Wait (2);

    while (IsOperatorControl() && IsEnabled()) {
        liftSensitivity = ((j_lift -> GetZ()-1)/2); //lift sensitivity

//SmartDashboard Declarations
        smartDashboard -> PutNumber("Robot Speed: ", ((1- j_right -> GetZ()/4))); //displays the speed of the wheels
        smartDashboard -> PutNumber("Lift Speed: ", liftSensitivity * -100); //displays the speed of the lift
        smartDashboard -> PutNumber("Intake Speed: ", 0.4);//displays the speed of the intake
        smartDashboard -> PutNumber("Outtake Speed: ", 0.8); //displays the speed of the outake

        //Joystick 1 and 2 Declarations


        tdrive -> SetThrottle((1- j_right -> GetZ()/4)); //Setting the speed of the robot 
        tdrive -> SetPower(j_left -> GetY(), j_right -> GetY()); //Setting the power of the tandrive


        if(j_right -> GetRawButton(2)){ //straight
        tdrive -> SetPower(RobotSpeed, RobotSpeed);
       }

        else if (j_right -> GetRawButton(3)){ //back
        tdrive -> SetPower (-RobotSpeed, -RobotSpeed);
        }
  
        //lift controls
        m_lift1 -> Set(liftSensitivity * j_lift -> GetY());
        m_lift2 -> Set(-liftSensitivity * j_lift -> GetY()); //motor 5 needs negative power

//Joystick 3 Declarations

          //intake
        if (j_lift -> GetRawButton(2)) {
            m_arm1 -> Set(0.4); 
            m_arm2 -> Set(-0.4);
        }

        //outake
        else if (j_lift -> GetRawButton(3)) {
            m_arm1 -> Set(-0.8); 
            m_arm2 -> Set(0.8);
        }

        //turns off arm wheels when buttons are released
        else {
            m_arm1 -> Set(0);
            m_arm2 -> Set(0);
        }
     
        //piston controls
        if (j_lift -> GetRawButton(1)) {
            solenoid -> Set(true);
            Wait(0.25);  
            solenoid -> Set(false);
        }
        
        //compressor on
        if (j_lift -> GetRawButton(10)) {
            compressor ->SetClosedLoopControl(true);
            smartDashboard -> PutString("Compressor: ", "On"); 
        }

        //compressor off
        if (j_lift -> GetRawButton(11)) {
            compressor -> SetClosedLoopControl(false);
            smartDashboard -> PutString("Compressor: ", "Off"); 
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