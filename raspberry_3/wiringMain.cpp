#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "Adafruit_PWMServoDriver.h"
#include "rfcomm-server.h"
using namespace std;
#define SERVOMIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1000 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
union FloatArray
{
  float array[10];
  char data[sizeof(float)*10];
};
int main (void)
{
  printf ("Raspberry Pi - Gertboard Blink\n") ;
  wiringPiSetup () ;
  // int fd=wiringPiI2CSetup(0x70);
  Adafruit_PWMServoDriver pwm(0x40);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  int turn[3]={460,300,130};
  int rise[3]={420,400,250};
  rfcomm_server rout;
  rout<< "good news";
   while (1)
   {
    int value;
    cin >>value;
    // for (int i = 0; i < 3; i++)
    // {
      pwm.setPWM(0, 0, turn[value]);
      pwm.setPWM(1, 0, rise[value]);
      usleep(500*1000);
    // }
    
    
   }
   
   
  // cout << fd;
  return 0 ;
}




    // for (int i = 0; i < dp2->length; i++)
    // {
    //     cout << hex << (uint)dp2->data[i] << " ";
    // }
    // cout << endl;
    // if (dp2->length<1)continue;
    
    // // cout << dp2->length ;
    // cout << "Value" << (cod<<dp2) << endl;

        // sh << dp;
    // cout  << "DP1" << dp->data << endl;

    // sh >>dp2;
    // if (dp2->length<1)continue;
    // cod>=dp2;
    // FloatArray fa;
    // memcpy(fa.data,dp2->data,40);
    // for (int i = 0; i < 10; i++)
    // {
    //   cout << fa.array[i] << " ";
    // }
    // cout << endl;
    


    // usleep(100000);