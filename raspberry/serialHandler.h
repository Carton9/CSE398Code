#ifndef SERIAL_HANDLE
#define SERIAL_HANDLE

#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringSerial.h>
#include <wiringPi.h>
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
        void operator << (Datapacket p); 
        Datapacket operator >>();
    private:
        int fd;
};

#endif 