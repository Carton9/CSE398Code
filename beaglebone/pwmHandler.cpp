#include "pwmHandler.h"
#include <cstring>
#include <unistd.h>
using namespace std;
	pwmHandle::pwmHandle(int pin){
        std::string cmd(string("config-pin ")+pwms[pin][0]+string(" pwm"));
        system(cmd.c_str());
        path="/sys/class/pwm/pwm";
        path+=pwms[pin][1];
        ofstream pinMode;
	    pinMode.open(path+"/period");
        pinMode << period << endl;
        pinMode.close();
        en.open(path+"/enable");
        en << "1" << endl;
        en.close();
        cout << path+"/enable" << endl;
    }
	pwmHandle::~pwmHandle(){
        duty_cycle.open(path+"/duty_cycle");
        en.open(path+"/enable");
        duty_cycle << "0"<< endl;
        en << "0"<< endl;
        duty_cycle.close();
        en.close();
    }
	int pwmHandle::setPinVal(int duty_cycle_in){
        char duty_cycle_value[21];
	    sprintf(duty_cycle_value, "%d", duty_cycle_in);

        duty_cycle.open(path+"/duty_cycle");
        duty_cycle << duty_cycle_value<< endl;
        duty_cycle.close();
    }