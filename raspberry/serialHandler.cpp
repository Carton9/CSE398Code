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
    // serialFlush(fd);
    serialPuts(fd,p->data);
    // serialFlush(fd);
}
void SerialHandler::operator >>(Datapacket* dp){
    int length=0;
    // while (length==0)length=serialDataAvail(fd);
    // dp->data=new char[length];
    // read(fd,dp->data,length);
    while (length==0)length=serialDataAvail(fd);
    // cout << "tp2"<<endl;
    usleep(100);
    while (serialDataAvail(fd)!=0)
    {
       cout <<(char)serialGetchar(fd);
    }
    cout << endl;
    
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}