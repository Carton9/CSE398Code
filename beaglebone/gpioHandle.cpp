#include "gpioHandle.h"
#include <cstring>
#include <unistd.h>

gpioHandle::gpioHandle()
{
}

gpioHandle::~gpioHandle()
{
}

//exports pin and sets mode
int gpioHandle::initializePin(const int pin, const int mode, const bool initialValue)
{
	char pinNum[21];
	std::string fordirection("/direction");
	std::string path("/sys/class/gpio/gpio");
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	ofstream exportPin;
	exportPin.open("/sys/class/gpio/export");
	if(!exportPin.is_open())
	{
		cout << "Error! exportPin not open.  \n";
		return (-1);
	}
	exportPin <<  pin;
	exportPin.close();

	path += fordirection;
	// usleep(100000);
	ofstream pinMode;
	pinMode.open(path);
	if(!pinMode.is_open())
	{
		cout << "Error! pinMode not open \n";
		return (-1);
	}
	if (PINMODE_OUT == mode)
	{
		pinMode <<  "out";
	}
	else {
		if (PINMODE_IN == mode) {
			pinMode <<  "in";
		}
		else {
			cout << "ERROR!!! \n";
			return (-1);
		}
	}
	pinMode.close();

	// usleep(100000);
	// cout << "Pin " << pin << " initialized to mode "; //debug only
	switch(mode){
	case(PINMODE_OUT):
		cout << "OUTPUT";
		break;
	case(PINMODE_IN):
		cout << "INPUT";
		break;
	default:
		cout << "INVALID PINMODE";
		break;
	}
	cout << " with an intial value of " << initialValue << endl;
	return(0);
}
// changes pin mode
int gpioHandle::setPinMode(const int pin, const int mode, const bool initialValue)
{
	char pinNum[21];
	std::string fordirection("/direction");
	std::string path("/sys/class/gpio/gpio");
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	path += fordirection;
	ofstream pinMode;
	pinMode.open(path);
	if(!pinMode.is_open())
	{
		cout << "Error! \n";
		return (-1);
	}

	if (PINMODE_OUT == mode) {
		pinMode <<  "out";
	}
	else {
		if (PINMODE_IN == mode) {
			pinMode <<  "in";
		}
		else {
			cout << "ERROR!!! \n";
			return (-1);
		}
	}
	pinMode.close();

	// usleep(100000);
        // cout << "Pin " << pin << " set to mode "; //debug only
	switch(mode){
	case(PINMODE_OUT):
		cout << "OUTPUT";
		break;
	case(PINMODE_IN):
		cout << "INPUT";
		break;
	default:
		cout << "INVALID PINMODE";
		break;
	}
	// cout << " with an intial value of " << mode << endl;
	return(0);
}
// retuns -1 when pin is unusable, else returns 0
int gpioHandle::setPinVal(const int pin, const bool val)
{
	char pinNum[21];
	std::string forvalue("/value");
	std::string path("/sys/class/gpio/gpio");;
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	path += forvalue;
	fstream setVal;
	setVal.open(path);
	if(!setVal.is_open())
	{
		cout << "Error! \n";
		return (-1);
	}
	// cout << "value is: " << (int)val << " Non cast: " << val << endl;
	setVal << val;
	// cout << "Pin " << pin << " set to " << val << endl;// debug only
	setVal.close();
	// usleep(100000);
	return(0);
}
// returns -1 when pin is unusable, else retuns value
int gpioHandle::getPinVal(const int pin)
{
	char pinNum[21];
	std::string forvalue("/value");
	std::string path("/sys/class/gpio/gpio");
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	path += forvalue;
	ifstream getVal;
	getVal.open(path);
	if(!getVal.is_open())
	{
		cout << "Error! \n";
		return (-1);
	}
	int value;
	getVal >> value;
	getVal.close();
	// usleep(100000);
	return(value);
}
// returns true if pin is usable
bool gpioHandle::pinOpen(const int pin)
{
	char pinNum[21];
	std::string path("/sys/class/gpio/gpio");
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	ofstream usePin;
	usePin.open(path);
	if(usePin.is_open())
	{
		cout << "The pin " << pin << " is usable!";
		return (true);
	}
	else {
		cout << "The pin " << pin << " is unusable!";
		return(false);
	}
	usePin.close();
	// usleep(100000);
	// cout << "Pin " << pin << " opened!" << endl; // debug only
}

// unexports pin
int gpioHandle::pinClose(const int pin)
{
	char pinNum[21];
	int pinNumber = pin;
	std::string path("/sys/class/gpio/gpio");
	sprintf(pinNum, "%d", pin);
	path += pinNum;
	ofstream unexportPin;
	unexportPin.open("/sys/class/gpio/unexport");
	if(!unexportPin.is_open())
	{
		cout << "Error! \n";
		return (-1);
	}
	unexportPin << pinNumber;
 	unexportPin.close();
	// cout << "Pin " << pin << " closed!" << endl; // debug only
	// usleep(100000);
	return(0);
}

