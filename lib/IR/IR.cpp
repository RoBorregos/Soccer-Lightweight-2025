#include "IR.h"  

IR::IR(){}
IR::IR(Adafruit_ADS1115 _Right, Adafruit_ADS1115 _Left, Adafruit_ADS1115 _Back)
    : right(_Right), left(_Left), back(_Back) {}

bool IR::initializeAdafruit(){
    right.setGain(GAIN_FOUR);
    left.setGain(GAIN_FOUR);
    back.setGain(GAIN_FOUR);
    if (!right.begin(0x48)||!left.begin(0x49)||!back.begin(0x4A)) {
        return false;
    }
}
double IR::getAverageRight(){
    int16_t ads5=right.readADC_SingleEnded(0);
    int16_t ads6=right.readADC_SingleEnded(1);
    int16_t ads7=right.readADC_SingleEnded(2);
    int16_t ads8=right.readADC_SingleEnded(3);

    return (ads5+ads6+ads7+ads8)/4.0;
}
double IR::getAverageLeft(){
    int16_t ads0=left.readADC_SingleEnded(0);
    int16_t ads1=left.readADC_SingleEnded(1);
    int16_t ads2=left.readADC_SingleEnded(2);
    int16_t ads3=left.readADC_SingleEnded(3);

    return (ads0+ads1+ads2+ads3)/4.0;
}
double IR::getAverageBack(){
    int16_t ads9=back.readADC_SingleEnded(0);
    int16_t ads10=back.readADC_SingleEnded(1);
    int16_t ads11=back.readADC_SingleEnded(2);
    int16_t ads12=back.readADC_SingleEnded(3);

    return (ads9+ads10+ads11+ads12)/4.0;
}
int16_t IR::getIndividualValueRight(int channel){
    return right.readADC_SingleEnded(channel);
}
int16_t IR::getIndividualValueLeft(int channel){
    return left.readADC_SingleEnded(channel);
}
int16_t IR::getIndividualValueBack(int channel){
    return back.readADC_SingleEnded(channel);
}
bool IR::detectLineRight(){
    double _right=getAverageRight();
    return _right<umbralLinea;
}
bool IR::detectLineLeft(){
    double _left=getAverageLeft();
    return _left<umbralLinea;
}
bool IR::detectLineBack(){
    double _back=getAverageBack();
    return _back<umbralLinea;
}
void IR::moveComplementary( bool moveRight, bool moveLeft, bool moveBack){
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