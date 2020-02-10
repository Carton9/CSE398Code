#include "protocolHandler.h"
        ProtocolHandler::ProtocolHandler(SerialHandler* sh){
            this->sh=sh;
        }
        ProtocolHandler::~ProtocolHandler(){
            
        }
        void ProtocolHandler::sendCommand(byte command,Datapacket* dp){
            byte data[2]={COMMAND,command};
            if(dp==NULL)
                return;
            cout << "TP2.5";
            memcpy(dp->data,data,2);
            dp->length=2;
             cout << "TP2.6";
            cod<=dp;
            *sh << dp;
            cout << "TP2.7";
        }
        void ProtocolHandler::sendData(float* data,int length,Datapacket* dp){
            if(dp==NULL)
                return;
            byte dataBuffer[length*4];
            for (int i = 0; i < length; i++)
            {
                floatToChar(data[i],(dataBuffer+4*i));
            }
            byte packet[length*4+2];
            packet[0]=DATA;
            packet[1]=(byte)length;
            memcpy(packet+2,dataBuffer,length*4);
            dp->data=packet;
            dp->length=length*4+2;
            cod<=dp;
            *sh << dp;
        }
        byte ProtocolHandler::receiveCommand(Datapacket* dp){
            if(dp==NULL)
                return -1;
            while (CommandBuffer.empty()&&DataBuffer.size()<255)
            {
                recevice();
            }
            if (CommandBuffer.empty())
            {
                return -1;
            }
            Datapacket* dpBuffered=CommandBuffer[0];
            dp->data=dpBuffered->data;
            dp->length=dpBuffered->length;
            CommandBuffer.erase(CommandBuffer.begin());
            delete dpBuffered;
            return dp->data[1];
            
        }
        int ProtocolHandler::receiveFloatData(float* data,Datapacket* dp){
            if(dp==NULL||data==NULL)
                return -1;
            while (DataBuffer.empty()&&CommandBuffer.size()<255)
            {
                recevice();
            }
            if (DataBuffer.empty())
            {
                return -1;
            }
            Datapacket* dpBuffered=DataBuffer[0];
            dp->data=dpBuffered->data;
            dp->length=dpBuffered->length;
            DataBuffer.erase(DataBuffer.begin());
            int length=dp->data[1];
            char* pointer=dp->data;
            pointer+=2;
            for (int i = 0; i < length; i++)
            {
                char buffer[4];
                memcpy(buffer,pointer+4*i,4);
                data[i]=byteToFloat(buffer);
            }
            delete dpBuffered;
            return length;
            
        }
        float ProtocolHandler::byteToFloat(byte* data){
            BFC convertor;
            for(int i = 0; i < 4; i++) {
                convertor.data[i]=data[i];
            }
            return convertor.value;
        }
        void ProtocolHandler::floatToChar(float value,byte* data){
            BFC convertor;
            convertor.value=value;
            memcpy(data,convertor.data,4);
        }
        void ProtocolHandler::recevice(){
            Datapacket* dp=new Datapacket;
            *sh>>dp;
            cod>=dp;
            if (dp->length<2)
                return;
            if (dp->data[0]==COMMAND)
            {
                CommandBuffer.push_back(dp);
            }else if (dp->data[0]==DATA)
            {
                DataBuffer.push_back(dp);
            }
            
        }