#include "pwmHandler.h"
#include "adcHandler.h"
#include "gpioHandle.h"
#include "server.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
double absDouble(double value){
    if(value<0)return value*-1;
    return value;
}
int main(){
    // Server foo(1234);
	// foo.listen();
    pwmHandle ph(PWM0);
    pwmHandle ph2(PWM1);
    pwmHandle ph3(PWM2);
    adcHandle adc0(0);
    gpioHandle gpio;
    int res = gpio.initializePin(48,1,0);
    int max=1000000;
    int base=10000;
    int state=0;
    int valueSet[]={10000,10000,10000};
    
    while (1)
    {
        ph.setPinVal(valueSet[0]);
        ph2.setPinVal(valueSet[1]);
        ph3.setPinVal(valueSet[2]);
        if (gpio.getPinVal(48)==1)
        {
            usleep(100000);
            if (gpio.getPinVal(48)==1){
                state++;
                state%=3;
               
            }
        }
        double value=(adc0.getPinVal()/4096.0)*base+100;
        if (absDouble(value-valueSet[state])>10)
        {
            valueSet[state]=value;
        }
        cout << "Current Selected Pin is " << state << endl;
        cout << "PWM0: " << valueSet[0] << endl;
        cout << "PWM1: " << valueSet[1] << endl;
        cout << "PWM2: " << valueSet[2] << endl;
        char data[4096];
        sprintf(data,"Current Selected Pin is %d\nPWM0: %d\nPWM1: %d");
        foo.send();
        // usleep(100000);
    }
    Server foo(9090);
	foo.listen();
	std::cout<<"Got \"";
	std::cout<<foo.receive(12);
	std::cout<<"\" from the client\n";
	std::cout<<"Sending \"Hello Client\" to the client\n";
	foo.send("Hello Client");
	return 0;
}
