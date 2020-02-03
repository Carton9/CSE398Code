#ifndef SERIAL_HANDLE
#define SERIAL_HANDLE
#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>

using namespace std;
struct Datapacket
{
    char* data;
    int length;
};

class SerialHandler
{
    public:
        SerialHandler();
        ~SerialHandler(); // unexport all pins opened by this class only
        void operator << (Datapacket* p); 
        void operator >> (Datapacket* p);
    private:
        int fd;
};

#endif 