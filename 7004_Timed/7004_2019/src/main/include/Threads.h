#include "Robot.h"
#include "Tankdrive.h"
#include <iostream>
#include <cstdlib>
using namespace frc;

//background autonomous driver assists for threads 
class threading_functions {
    public:
        double gyro_i; //initial gyro value
        double gyro_c; //current gyro value

        void left_90() { //rotate 90 degrees to the left
            gyro_i = Robot::gyroArray[0];
            while (true) {
                gyro_c = Robot::gyroArray[0];

                if (gyro_c - gyro_i <= 90) {
                    Robot::tdrive -> SetPower(0.0, -0.4);
                }
                else {
                    Robot::tdrive -> SetPower(0.0, 0.0);
                }
            }
        }

        void right_90() { //rotate 90 degrees to the right
            gyro_i = Robot::gyroArray;
            while (true) {
                gyro_c = Robot::gyroArray;
                if (gyro_c - gyro_i <= 90) {
                    Robot::tdrive -> SetPower(0.4, 0.0);
                }
                Robot::tdrive -> SetPower(0.0, 0.0);
            }
        }

        void rotate_180() { //rotate 180 degrees
            gyro_i = Robot::gyroArray;
            while (true){
                gyro_c = Robot::gyroArray;
                if (gyro_c - gyro_i <= 180) {
                    Robot::tdrive -> SetPower(0.4, 0.4);
                }
                Robot::tdrive -> SetPower(0.0, 0.0);
            }
        }

        void options() { //rotation functions are called through here
            if (j_right.GetRawButton(5)) {
                right_90();
            }
            else if (j_right.GetRawButton(4)){
                left_90();
            }
            else if (j_right.GetRawButton(3)){
                rotate_180();
            }
        }
}func;