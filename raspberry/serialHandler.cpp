#include "serialHandler.h"

SerialHandler::SerialHandler(){
    fd=serialOpen("/dev/ttyS0",9600);
    
}
void SerialHandler::operator << (Datapacket* p){
    serialFlush(fd);
    serialPuts(fd,p->data);
    serialFlush(fd);
}
void SerialHandler::operator >>(Datapacket* dp){
    int length=serialDataAvail(fd);
    dp->data=new char[length];
    read(fd,dp->data,length);
}
SerialHandler::~SerialHandler(){
    serialClose(fd);
}