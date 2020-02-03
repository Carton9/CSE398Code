#ifndef PWM_HANDLE
#define PWM_HANDLE

#include <iostream>
#include <fstream>

using namespace std;

// pinmode definitions
#define PINMODE_OUT	0
#define PINMODE_IN	1
#define period 1000000
#define PWM0 0
#define PWM1 1
#define PWM2 2

class pwmHandle
{
public:

	pwmHandle(int pin);
	~pwmHandle(); // unexport all pins opened by this class only
	int setPinVal(int duty_cycle_in); // retuns -1 when pin is unusable, else returns 0

private:
    string pwms[3][2]={{"P9_42","-0\:0"},{"P9_22","-1\:0"},{"P9_21","-1\:1"}};
    string name;
    ofstream duty_cycle;
    ofstream en;
	char *buffer;	// for sprintfs
    string path;
};

#endif