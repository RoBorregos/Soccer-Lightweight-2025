#include "Arduino.h"
#include "Motor.h"  

motor::motor(){
    pin1_ = 0;
    pin2_ = 0;
    speed_ = 0;

};

motor::motor(int pin1, int pin2, int speed){
    pin1_ = pin1;
    pin2_ = pin2;
    speed_ = speed;
};
void startMotors(){
    pinMode(pin1_, OUTPUT);
    pinMode(pin2_, OUTPUT);
    pinMode(speed_, OUTPUT);

};
void Motor::SetSpeed(int pwm, int speed){
    analogWrite(pwm, speed);
};
void motor::forward(){
    digitalWrite(pin1_, HIGH);
    digitalWrite(pin2_, LOW);

};
void motor::backward(){
    digitalWrite(pin1_, LOW);
    digitalWrite(pin2_, HIGH);

};
void motor::stop(){
    digitalWrite(pin1_, LOW);
    digitalWrite(pin2_, LOW);

};