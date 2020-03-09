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
int main(int argc, char** argv)
{
  wiringPiSetup () ;
  pinMode (24, OUTPUT) ;
  pinMode (25, OUTPUT) ;

  pinMode (27, OUTPUT) ;
  pinMode (22, OUTPUT) ;
  
  softPwmCreate (23, 0, 100) ;
  // softPwmCreate (17, 0, 100) ;
  while(1){
    digitalWrite (24, 0) ;
    digitalWrite (25, 1) ;

    // digitalWrite (27, 0) ;
    // digitalWrite (22, 1) ;
    for (int i = 0; i < 100; i++)
    {
      softPwmWrite (23, i);
      // softPwmWrite (17, i);
      sleep(1);
    }

    // digitalWrite (24, 1) ;
    // digitalWrite (25, 0) ;

    // digitalWrite (27, 1) ;
    // digitalWrite (22, 0) ;
    // for (int i = 0; i < 100; i++)
    // {
    //   softPwmWrite (23, i);
    //   softPwmWrite (17, i);
    //   sleep(10);
    // }
    
  }
  return 0;
}