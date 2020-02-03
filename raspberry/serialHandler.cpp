#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
    
}
void SerialHandler::operator << (Datapacket* p){
    for (int i = 0; i < p->length; i++)
    {
        char c=(p->data[i]);
        serialPutchar(fd,c);
    }
    serialFlush(fd);
}
void SerialHandler::operator >>(Datapacket* dp){
    int length=serialDataAvail(fd);
    dp->data=new char[length];
    for(int i=0;i<length;i++){
        dp->data[i]=serialGetchar(fd);
    }
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}