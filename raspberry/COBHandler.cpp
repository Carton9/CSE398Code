#include "COBHandler.h"
COBHandler::COBHandler(){}
COBHandler::~COBHandler(){} // unexport all pins opened by this class only
Datapacket* COBHandler::operator << (float p){
    union FloatConverter
    {
        float floatNumber;
        char array[4];
    };
    FloatConverter s;
    s.floatNumber=p;
    // (char*)malloc(sizeof(char)*6)
    char* data=new char[6];
    memcpy(data+1,s.array,4);
    int currentIndex=0;
    int nextIndex=0;
    for (int i = 1; i < 6; i++)
    {
        nextIndex++;
        if(data[i]==0){
            data[currentIndex]=nextIndex;
            currentIndex=i;
            nextIndex=0;
        }
    }
    Datapacket* dp=new Datapacket();
    dp->data=data;
    dp->length=6;
}
float COBHandler::operator << (Datapacket* p){
    char* rawData=p->data;
    int index=0;
    int nextIndex=0;
    while (index<p->length-1)
    {
        nextIndex=(uint16_t)rawData[index];
        rawData[index]=0;
        index+=nextIndex;
    }
    union FloatConverter
    {
        float floatNumber;
        char array[4];
    };
    FloatConverter s;
    memcpy(rawData,rawData+1,4);
    memcpy(s.array,rawData,4);
    return s.floatNumber;
}
void COBHandler::operator<= (Datapacket* p){
    // (char*)malloc(sizeof(char)*(p->length+2))
    char* data=new char[(p->length+2)];
    memcpy(data+1,p->data,p->length);
    int currentIndex=0;
    int nextIndex=0;
    for (int i = 1; i < p->length+2; i++)
    {
        nextIndex++;
        if(data[i]==0){
            data[currentIndex]=nextIndex;
            currentIndex=i;
            nextIndex=0;
        }
    }
    // for (int i = 0; i < p->length+2; i++)
    // {
    //     cout << hex << (uint64_t)data[i] << " ";
    // }
    // cout << endl;
    Datapacket* dp=new Datapacket();
    p->data=data;
    p->length=p->length+2;
}
void COBHandler::operator>= (Datapacket* p){
//    cout << "TP3.12" << endl;
    char* rawData=p->data;
    int index=0;
    int nextIndex=0;
     while (index<p->length-1)
    {
        nextIndex=(uint16_t)rawData[index];
        rawData[index]=0;
        index+=nextIndex;
    }
    // cout << "TP3.12" << endl;
    // (char*)malloc(sizeof(char)*(p->length-2))
    char* newData=new char[p->length-2];
    memcpy(newData,rawData+1,p->length-2);
    p->length-=2;
    p->data=newData;
    // cout << "TP3.13" << endl;
} 