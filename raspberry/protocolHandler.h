#ifndef PROTOCOL_HANDLE
#define PROTOCOL_HANDLE
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream> 
#include <fstream>
#include "Datapacket.h"
#include <unistd.h>
#include "serialHandler.h"
#include "COBHandler.h"

using namespace std;
#define COMMAND 0x01
#define DATA 0x02

#define EVENT   0x01
#define REQUEST 0x02


// 0x01 0x01 

// 0x02 <length byte> data .....
class ProtocolHandler
{
    public:
        ProtocolHandler(SerialHandler* sh);
        ~ProtocolHandler(); // unexport all pins opened by this class only
        void sendCommand(byte command,Datapacket* dp);
        void sendData(float* data,int length,Datapacket* dp);
        byte receiveCommand(Datapacket* dp);
        int receiveFloatData(float* data,Datapacket* dp);
    private:
        int fd;
        vector<Datapacket*> CommandBuffer;
        vector<Datapacket*> DataBuffer;
        SerialHandler* sh;
        COBHandler cod;
        void recevice();
        float byteToFloat(unsigned char* data);
        void floatToChar(float value,char* data);
        union BFC{
                float value;
                unsigned char data[4];
        };
};
#endif