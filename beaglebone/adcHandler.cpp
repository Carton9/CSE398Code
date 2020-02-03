    #include "adcHandler.h"
    using namespace std;
    adcHandle::adcHandle(int device){
        if (device>7)return;
        char char_path[55];
        sprintf(char_path, ADC_PATH, device);
        path=char_path;
    }
	adcHandle::~adcHandle(){

    } // unexport all pins opened by this class only
	int adcHandle::getPinVal(){
        ifstream getVal;
        getVal.open(path);
        int result =0;
        getVal >> result;
        getVal.close();
        return result;
    } // retuns -1 when pin is unusable, else returns 0