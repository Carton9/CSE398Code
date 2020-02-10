#ifndef COB_HANDLER
#define COB_HANDLER
#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <unistd.h>
#include "Datapacket.h"
using namespace std;
class COBHandler
{
    public:
        COBHandler();
        ~COBHandler(); // unexport all pins opened by this class only
        Datapacket* operator << (float p); 
        float operator << (Datapacket* p); 
        void operator<= (Datapacket* p);//encode
        void operator>= (Datapacket* p);//decode
    private:
        int fd;

};

#endif