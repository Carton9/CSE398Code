#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
    char buf[4096];
}
void SerialHandler::operator << (Datapacket* p){
    // serialFlush(fd);
    serialPuts(fd,p->data);
    // serialFlush(fd);
}
void SerialHandler::operator >>(Datapacket* dp){
    int length=0;
    // while (length==0)length=serialDataAvail(fd);
    // dp->data=new char[length];
    // read(fd,dp->data,length);
    // cout << "tp2"<<endl;
    char buffer[40960];
    while (serialDataAvail(fd)!=0)
    {
       buffer[length]=(char)serialGetchar(fd);
       length++;
       if(buffer[length-1]==0)break;
    }
    char* frame=(char*)malloc(sizeof(char)*length);
    memcpy(frame,buffer,length);
    dp->data=frame;
    dp->length=length;
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}