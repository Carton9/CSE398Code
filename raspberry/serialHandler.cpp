#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
    char buf[4096];
    read(fd,buf,4096);
    read(fd,buf,4096);
    read(fd,buf,4096);
    read(fd,buf,4096);
    read(fd,buf,4096);
}
void SerialHandler::operator << (Datapacket* p){
    serialFlush(fd);
    serialPuts(fd,p->data);
    serialFlush(fd);
}
void SerialHandler::operator >>(Datapacket* dp){
    int length=0;
    // while (length==0)length=serialDataAvail(fd);
    // dp->data=new char[length];
    // read(fd,dp->data,length);
    while (length==0)length=serialDataAvail(fd);
    int data=serialGetchar(fd);
    if(data!=-1)
        cout << (char)data;
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}