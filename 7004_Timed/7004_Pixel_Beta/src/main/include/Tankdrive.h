/*Is not working, do not include*/

#pragma once
#include <frc/WPIlib.h>
#include "Constants.h"
#include "OECPigeonIMU.h"
#include "OECPIDController.h"
using namespace frc;
class Tankdrive{
    public:
        enum LoopMode{internal, external};
        enum DriveSide{left, right};

        Tankdrive(int leftPort, int rightPort, int leftPort1, int rightPort1, int leftEncoder1, int leftEncoder2, int rightEncoder1, int rightEncoder2, OECPigeonIMU *pigeonIMU, SmartDashboard *smartDashboard);
        void SetPower(double leftPower, double rightPower);
        void SetThrottle(double throttle);
        void ResetEncoders();
        void SetLoopMode(LoopMode mode);
        double GetEncoderDist(DriveSide encoderSide);
        double GetRightEncoderDist();
        double GetLeftEncoderDist();
        void DriveCurveEncoder(double radius, double degrees, double avgPower);
        void DriveGyro(double degreesPerInch, double degrees, double avgPower, double timeoutSec);
        void DriveGyroByRadius(double radius, double degrees, double avgPower, double timeoutSec);
    private:
        SmartDashboard *smartDashboard;
        OECPIDController *pidController;
        OECPigeonIMU *pigeonIMU;
        Spark *leftDrive;
        Spark * leftDrive1;
        Spark *rightDrive;
        Spark * rightDrive1;
        Encoder *leftEncoder;
        Encoder *rightEncoder;
        double throttle;
        LoopMode loopMode;
            
};