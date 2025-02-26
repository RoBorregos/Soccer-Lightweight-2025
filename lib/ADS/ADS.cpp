#include "ADS.h"  

ADS::ADS(){}
ADS::ADS(Adafruit_ADS1115 _Right, Adafruit_ADS1115 _Left, Adafruit_ADS1115 _Back)
    : right(_Right), left(_Left), back(_Back) {}


bool ADS::initializeAdafruit(){
    right.setGain(GAIN_FOUR);
    left.setGain(GAIN_FOUR);
    back.setGain(GAIN_FOUR);
    if (!right.begin(0x48)||!left.begin(0x49)||!back.begin(0x4A)) {
        return false;
    }
}
double ADS::getAverageRight(){
    const int16_t ads5=right.readADC_SingleEnded(0);
    const int16_t ads6=right.readADC_SingleEnded(1);
    const int16_t ads7=right.readADC_SingleEnded(2);
    const int16_t ads8=right.readADC_SingleEnded(3);

    return (ads5+ads6+ads7+ads8)/4.0;
}
double ADS::getAverageLeft(){
    int16_t ads0=left.readADC_SingleEnded(0);
    int16_t ads1=left.readADC_SingleEnded(1);
    int16_t ads2=left.readADC_SingleEnded(2);
    int16_t ads3=left.readADC_SingleEnded(3);

    return (ads0+ads1+ads2+ads3)/4.0;
}
double ADS::getAverageBack(){
    int16_t ads9=back.readADC_SingleEnded(0);
    int16_t ads10=back.readADC_SingleEnded(1);
    int16_t ads11=back.readADC_SingleEnded(2);
    int16_t ads12=back.readADC_SingleEnded(3);

    return (ads9+ads10+ads11+ads12)/4.0;
}
int16_t ADS::getIndividualValueRight(int channel){
    return right.readADC_SingleEnded(channel);
}
int16_t ADS::getIndividualValueLeft(int channel){
    return left.readADC_SingleEnded(channel);
}
int16_t ADS::getIndividualValueBack(int channel){
    return back.readADC_SingleEnded(channel);
}
bool ADS::detectLineRight(){
    double _right=getAverageRight();
    return _right<umbralLinea;
}
bool ADS::detectLineLeft(){
    double _left=getAverageLeft();
    return _left<umbralLinea;
}
bool ADS::detectLineBack(){
    double _back=getAverageBack();
    return _back<umbralLinea;
}
void ADS::moveComplementary( bool moveRight, bool moveLeft, bool moveBack){
    if(moveRight){
        //Mover a la derecha
        Serial.println("Right");
    } else if(moveLeft){
        //Mover a la izquierda
        Serial.println("Left");
    }else if(moveBack){
        //Mover hacia atras
        Serial.println("Back");
    }
}