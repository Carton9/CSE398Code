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
  char tp1[4]={'t','e','s','t'};
  dp->data=tp1;
  dp->length=4;
  
  while (1)
  {
    sh << dp;
    usleep(10000);
  }
  
  return 0 ;
}