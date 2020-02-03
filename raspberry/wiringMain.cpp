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
  dp->data="test";
  dp->length=4;
  
  while (1)
  {
    sh << dp;
    for (int i = 0; i < 100000; i++)
    {
       for (int i = 0; i < 100000; i++)
        {
          /* code */
        }
    }
    
    usleep(10000);
  }
  
  return 0 ;
}