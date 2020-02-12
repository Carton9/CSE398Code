#ifndef CON_DATAPACKET
#define CON_DATAPACKET
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <unistd.h>
#define byte char
class Datapacket
{
    public:
        Datapacket(){
            data=new char[4096];
        }
        Datapacket(int length){
            data=new char[length];
            this->length=length;
        }
        Datapacket* operator+ (Datapacket* in){
            char newData[in->length+length];
            memcpy(newData,data,length);
            memcpy(newData+length,in->data,in->length);
            Datapacket* newPacket=new Datapacket();
            newPacket->data=newData;
            newPacket->length=in->length+length;
            return newPacket;
        }
        char* data;
        int length;
};

#endif