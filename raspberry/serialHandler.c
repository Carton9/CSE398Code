#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
    
}
void SerialHandler::operator << (Datapacket* p);{
    for (int i = 0; i < p->length; i++)
    {
         serialPut(fd,p->data[i]);
    }
    serialFlush(fd);
}
Datapacket* SerialHandler::operator >>(){
    Datapacket dp=new Datapacket;
    int length=serialDataAvail(fd);
    dp->data=new char[length];
    for(int i=0;i<length;i++){
        dp->data[i]=serialGetchar(fd);
    }
    return dp;
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}