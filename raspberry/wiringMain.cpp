#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include "serialHandler.h"
#include "COBHandler.h"
int main (void)
{
  printf ("Raspberry Pi - Gertboard Blink\n") ;
  wiringPiSetup () ;
  SerialHandler sh;
  Datapacket* dp=new Datapacket;
  Datapacket* dp2=new Datapacket;
  COBHandler cod;
  dp->data="test";
  dp->length=4;
  
  while (1)
  {
    // sh << dp;
    // cout  << "DP1" << dp->data << endl;
    sh >>dp2;
    if (dp2->length<1)continue;
    
    // cout << dp2->length ;
    cout << "Value" << (cod<<dp2) << endl;
    for (int i = 0; i < dp2->length; i++)
    {
        cout << hex << (uint)dp2->data[i] << " ";
    }
    cout << endl;
    usleep(100000);
  }
  
  return 0 ;
}