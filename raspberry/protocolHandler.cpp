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
            // cout << "TP2.5"<<endl;
            dp->data=new char[2];
            memcpy(dp->data,data,2);
            dp->length=2;
            //  cout << "TP2.6"<<endl;
            cod<=dp;
            *sh << dp;
            delete[] dp->data;
            // cout << "TP2.7"<<endl;
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
            memcpy(dp->data,dpBuffered->data,dpBuffered->length);
            dp->length=dpBuffered->length;
            CommandBuffer.erase(CommandBuffer.begin());
            delete[] dpBuffered->data;
            delete dpBuffered;
            return dp->data[1];
            
        }
        int ProtocolHandler::receiveFloatData(float* data,Datapacket* dp){
            if(dp==NULL||data==NULL)
                return -1;
            cout << "TP3.1" << endl;
            while (DataBuffer.empty()&&CommandBuffer.size()<255)
            {
                recevice();
            }
            cout << "TP3.2" << endl;
            if (DataBuffer.empty())
            {
                return -1;
            }
            cout << "TP3.3" << endl;
            Datapacket* dpBuffered=DataBuffer[0];
            memcpy(dp->data,dpBuffered->data,dpBuffered->length);
            dp->length=dpBuffered->length;
            cout << "TP3.4" << endl;
            DataBuffer.erase(DataBuffer.begin());
            int length=dp->data[1];
            char* pointer=dp->data;
            cout << "TP3.5" << endl;
            pointer+=2;
            for (int i = 0; i < length; i++)
            {
                char buffer[4];
                memcpy(buffer,pointer+4*i,4);
                data[i]=byteToFloat(buffer);
            }
            cout << "TP3.6" << endl;
            delete[] dpBuffered->data;
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
            // cout << "TP3.11" << endl;
            *sh>>dp;
            // cout << "TP3.12 " << "Packet Size " << dp->length << endl;
            cod>=dp;
            for (int i = 0; i < dp->length; i++){
                cout << hex << (uint)dp->data[i] << " ";
            
            }
            cout << endl;
            if (dp->length<2)
                return;
            
            if (dp->data[0]==COMMAND)
            {
                CommandBuffer.push_back(dp);
            }else if (dp->data[0]==DATA)
            {
                DataBuffer.push_back(dp);
            }
            cout << "TP3.13" << endl;
        }