#ifndef __RFCOMM_SERVER_H
#define __RFCOMM_SERVER_H
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include "bluetooth.h"
#include "rfcomm.h"
using namespace std;
class rfcomm_server
{
private:
    int client=-1;
    int server=-1;
public:
    rfcomm_server(){
        struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
        char buf[1024] = { 0 };
        socklen_t opt = sizeof(rem_addr);

        // allocate socket
        server = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

        // bind socket to port 1 of the first available 
        // local bluetooth adapter
        loc_addr.rc_family = AF_BLUETOOTH;
        //loc_addr.rc_bdaddr = *BDADDR_ANY;
        loc_addr.rc_channel = (uint8_t) 1;
        bind(server, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

        // put socket into listening mode
        listen(server, 1);
        cout << "TP0.2 " << server << endl;
        // // accept one connection
        while (client==-1)
        {
             client = accept(server, (struct sockaddr *)&rem_addr, &opt);
             cout << "TP0.1 " << client << endl;
        }
       
        
    }
    ~rfcomm_server(){
        close(client);
        close(server);
    }
    rfcomm_server& operator<<(string s){
        write(client,s.c_str(),s.size());
        write(client,"\n",1);
        return *this;
    }
    rfcomm_server& operator>>(string& s){
        char buf[1024] = { 0 };
        int bytes_read=-1;
        while (bytes_read==-1)
        {
            memset(buf, 0, sizeof(buf));
            bytes_read= read(client, buf, sizeof(buf));
        }
        
        cout << "tp1.1 " <<bytes_read << endl;
        s=string(buf,bytes_read);
        return *this;
    }
};

#endif /* __RFCOMM_H */