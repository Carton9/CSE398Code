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
  if (motor==0)
  {
    digitalWrite (24, 0) ;
    digitalWrite (25, 1) ;
  }else{

  }
  

 
}

int main(int argc, char** argv)
{
  wiringPiSetup () ;
  pinMode (24, OUTPUT) ;
  pinMode (25, OUTPUT) ;

  pinMode (2, OUTPUT) ;
  pinMode (3, OUTPUT) ;
  
  softPwmCreate (23, 0, 100) ;
  softPwmCreate (20, 0, 100) ;
  while(1){
    digitalWrite (24, 0) ;
    digitalWrite (25, 1) ;

    digitalWrite (5, 0) ;
    digitalWrite (6, 1) ;
    for (int i = 0; i < 100; i++)
    {
      softPwmWrite (23, i);
      softPwmWrite (20, i);
      usleep(100000);
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