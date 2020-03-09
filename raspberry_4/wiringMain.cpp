#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <softPwm.h>
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
void motor_control(int motor, int speed){
  int dir=speed>0;
  if (motor==0)
  {
    digitalWrite (24, dir) ;
    digitalWrite (25, !dir) ;
    softPwmWrite (23, abs(speed));
  }else{
    digitalWrite (28, dir) ;
    digitalWrite (27, !dir) ;
    softPwmWrite (26, abs(speed));
  }
}

int main(int argc, char** argv)
{
  wiringPiSetup () ;
  pinMode (24, OUTPUT) ;
  pinMode (25, OUTPUT) ;

  pinMode (28, OUTPUT) ;
  pinMode (27, OUTPUT) ;
  
  softPwmCreate (23, 0, 100) ;
  softPwmCreate (26, 0, 100) ;
  while(1){
    // digitalWrite (24, 0) ;
    // digitalWrite (25, 1) ;

    // digitalWrite (28, 0) ;
    // digitalWrite (27, 1) ;
    for (int i = 0; i < 100; i++)
    {
      // softPwmWrite (23, i);
      // softPwmWrite (26, i);
      motor_control(0,i);
      motor_control(1,i);
      usleep(10000);
    }

    // digitalWrite (24, 1) ;
    // digitalWrite (25, 0) ;

    // // digitalWrite (27, 1) ;
    // // digitalWrite (22, 0) ;
    // for (int i = 0; i < 100; i++)
    // {
    //   softPwmWrite (23, i);
    //   // softPwmWrite (17, i);
    //   usleep(100000);
    // }

    
  }
  return 0;
}