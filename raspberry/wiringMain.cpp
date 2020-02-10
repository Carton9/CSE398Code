#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include "serialHandler.h"
#include "COBHandler.h"
#include "protocolHandler.h"
union FloatArray
{
  float array[10];
  char data[sizeof(float)*10];
};

int main (void)
{
  printf ("Raspberry Pi - Gertboard Blink\n") ;
  wiringPiSetup () ;
  SerialHandler sh;
    cout << "TP0.1";
  Datapacket* dp=new Datapacket;
  Datapacket* dp2=new Datapacket;
      cout << "TP0.2";
  COBHandler cod;
  cout << "TP1";
  // ProtocolHandler ph(&sh);
  // while (1){
  //   cout << "TP2";
  //   ph.sendCommand(REQUEST,dp2);
  //   cout << "TP3";
  //   float dataBuffer[200];
  //   int length=ph.receiveFloatData(dataBuffer,dp);
  //   cout << "TP4";
  //   for (int i = 0; i < length; i++)
  //   {
  //     cout << dataBuffer[i] << " ";
  //   }
  //   cout << endl;
  // }
  
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