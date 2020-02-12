#ifndef SERIAL_HANDLE
#define SERIAL_HANDLE
#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "Datapacket.h"
#include <unistd.h>

using namespace std;


class SerialHandler
{
    public:
        SerialHandler();
        ~SerialHandler(); // unexport all pins opened by this class only
        void send(Datapacket* p){
            serialPuts(fd,p->data);
            if (p->data[p->length-1]==0)
            {
                serialPutchar(fd,'/0');
            }
            
        }
        void operator<< (Datapacket* p); 
        void operator>> (Datapacket* p);
    private:
        int fd;
};

#endif 