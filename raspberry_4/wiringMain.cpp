#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"
#include "MJPEGWriter.h"
// #include <wiringSerial.h>
// #include <wiringPiI2C.h>
#include <unistd.h>
// #include "Adafruit_PWMServoDriver.h"
// #include "rfcomm-server.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <thread>
using namespace cv;
using namespace std;
// void motor_control(int motor, int speed){
//   int dir=speed>0;
//   if (motor==0)
//   {
//     digitalWrite (24, dir) ;
//     digitalWrite (25, !dir) ;
//     softPwmWrite (23, abs(speed));
//   }else{
//     digitalWrite (28, dir) ;
//     digitalWrite (27, !dir) ;
//     softPwmWrite (26, abs(speed));
//   }
// }

int main(int argc, char** argv)
{
  wiringPiSetup () ;
  // pinMode (24, OUTPUT) ;
  // pinMode (25, OUTPUT) ;

  // pinMode (28, OUTPUT) ;
  // pinMode (27, OUTPUT) ;
  
  // softPwmCreate (23, 0, 100) ;
  // softPwmCreate (26, 0, 100) ;
  // Motor motor1(23,24,25);
  // Motor motor2(26,28,27);
  MJPEGWriter test(7777);
  // while(1){
  //   for (int i = -100; i < 100; i++)
  //   {
  //     // softPwmWrite (23, i);
  //     // softPwmWrite (26, i);
  //     motor1.motor_control(i);
  //     motor2.motor_control(i);
  //     usleep(10000);
  //   }
  // }
  return 0;
}