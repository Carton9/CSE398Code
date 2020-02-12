#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
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
    cout << "TP3.111"<<endl;
    char buffer[40960];
    int isBegin=0;
    while (1)
    {
       if(isBegin==0){
            buffer[length]=(char)serialGetchar(fd);
            length++;
            usleep(100);
            if(buffer[length-1]==0){
                isBegin=0;
                break;
            }
       }
    }
    cout << "TP3.112"<<endl;
    // (char*)malloc(sizeof(char)*length)
    char* frame=new char[length];
    memcpy(frame,buffer,length);
    cout << "TP3.113"<<endl;
    dp->data=frame;
    dp->length=length;
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}