#ifndef ADC_HANDLE
#define ADC_HANDLE

#include <iostream>
#include <fstream>

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw"

using namespace std;
class adcHandle
{
public:
    adcHandle(int device);
	~adcHandle(); // unexport all pins opened by this class only
	int getPinVal(); // retuns -1 when pin is unusable, else returns 0

private:
    string path;
};

#endif