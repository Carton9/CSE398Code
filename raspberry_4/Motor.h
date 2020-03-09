#ifndef __MOTOR_H
#define __MOTOR_H
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include <vector>
#include <thread>
class Motor{
    public:
        Motor(int motorPWM,int motorA,int motorB){
            pinMode (motorA, OUTPUT) ;
            pinMode (motorB, OUTPUT) ;
            softPwmCreate (motorPWM, 0, 100) ;
            motors[0]=motorPWM;
            motors[1]=motorA;
            motors[2]=motorB;
        }
        ~Motor(){
            softPwmWrite (motors[0], 0);
            digitalWrite (motors[1], 0) ;
            digitalWrite (motors[2], 0) ;
        }
        void motor_control(int speed){
            int dir=speed>0;
            digitalWrite (motors[1], dir) ;
            digitalWrite (motors[2], !dir) ;
            softPwmWrite (motors[0], abs(speed));
        }
    private:
        int motors[3];
}
#endif