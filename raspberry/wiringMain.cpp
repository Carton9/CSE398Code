#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include "serialHandler.h"
int main (void)
{
  printf ("Raspberry Pi - Gertboard Blink\n") ;
  wiringPiSetup () ;
  SerialHandler sh;
  Datapacket* dp=new Datapacket;
  Datapacket* dp2=new Datapacket;
  dp->data="test";
  dp->length=4;
  
  while (1)
  {
    sh << dp;
    cout << "DP1" << dp->data << endl;
    sh >>dp2;
    // cout << "DP2" << dp2->data << endl;
    usleep(100000);
  }
  
  return 0 ;
}