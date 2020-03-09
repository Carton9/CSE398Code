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
  pinMode (24, OUTPUT) ;
  pinMode (25, OUTPUT) ;
  digitalWrite (24, 0) ;
  digitalWrite (25, 1) ;
  softPwmCreate (23, 0, 100) ;
  while(1){
    softPwmWrite (23, 50);
    sleep(100);
  }
  return 0;
}