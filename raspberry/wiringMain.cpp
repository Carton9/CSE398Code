#include <stdio.h>
#include <wiringPi.h>
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
  }
  
  return 0 ;
}