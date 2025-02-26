#include "ADS.h"  

ADS::ADS(){}
ADS::ADS(Adafruit_ADS1115 _Right, Adafruit_ADS1115 _Left, Adafruit_ADS1115 _Back)
    : right(_Right), left(_Left), back(_Back) {}

// Initializes the Adafruit ADS sensors with specific gain settings and checks if they start correctly.
bool ADS::InitializeAdafruit(){
    right.setGain(GAIN_FOUR);
    left.setGain(GAIN_FOUR);
    back.setGain(GAIN_FOUR);
    if (!right.begin(0x48)||!left.begin(0x49)||!back.begin(0x4A)) {
        return false;
    }
}
<<<<<<< HEAD
double ADS::GetAverageRight(){
=======
double ADS::getAverageRight(){
>>>>>>> a3b404393f8d725ac4ae8b311e010b7817c458a4
    const int16_t ads5=right.readADC_SingleEnded(0);
    const int16_t ads6=right.readADC_SingleEnded(1);
    const int16_t ads7=right.readADC_SingleEnded(2);
    const int16_t ads8=right.readADC_SingleEnded(3);

    return (ads5+ads6+ads7+ads8)/4.0;
}
double ADS::GetAverageLeft(){
    const int16_t ads0=left.readADC_SingleEnded(0);
    const int16_t ads1=left.readADC_SingleEnded(1);
    const int16_t ads2=left.readADC_SingleEnded(2);
    const int16_t ads3=left.readADC_SingleEnded(3);

    return (ads0+ads1+ads2+ads3)/4.0;
}
double ADS::GetAverageBack(){
    const int16_t ads9=back.readADC_SingleEnded(0);
    const int16_t ads10=back.readADC_SingleEnded(1);
    const int16_t ads11=back.readADC_SingleEnded(2);
    const int16_t ads12=back.readADC_SingleEnded(3);

    return (ads9+ads10+ads11+ads12)/4.0;
}
const int16_t ADS::GetIndividualValueRight(int channel){
    return right.readADC_SingleEnded(channel);
}
const int16_t ADS::GetIndividualValueLeft(int channel){
    return left.readADC_SingleEnded(channel);
}
const int16_t ADS::GetIndividualValueBack(int channel){
    return back.readADC_SingleEnded(channel);
}
bool ADS::DetectLineRight(){
    double _right=getAverageRight();
    return _right<threshold_line;
}
bool ADS::DetectLineLeft(){
    double _left=getAverageLeft();
    return _left<threshold_line;
}
bool ADS::DetectLineBack(){
    double _back=getAverageBack();
    return _back<threshold_line;
}

