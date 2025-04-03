#include "Arduino.h"
#include "motor.h"

Motor::Motor(const uint8_t inPWM, const uint8_t in1,const  uint8_t in2)
{
    inPWM_ = inPWM;
    in1_ = in1;
    in2_ = in2;
}

void Motor::InitializeMotor()
{
    pinMode(in1_, OUTPUT);
    pinMode(in2_, OUTPUT);
    pinMode(inPWM_, OUTPUT);
};

void Motor::SetPWM(const uint8_t pwm)
{
    analogWrite(inPWM_, pwm);
};

void Motor::MovePositive()
{
    digitalWrite(in1_, HIGH);
    digitalWrite(in2_, LOW);
};

void Motor::MoveNegative()
{
    digitalWrite(in1_, LOW);
    digitalWrite(in2_, HIGH);
};

void Motor::StopMotor()
{
    digitalWrite(in1_, LOW);
    digitalWrite(in2_, LOW);
};

uint8_t Motor::GetInPWM()
{
    return inPWM_;
};

uint8_t Motor::GetIn1()
{
    return in1_;
};

uint8_t Motor::GetIn2()
{
    return in2_;
};

void Motor::SetSpeed(float speed) {
    if (speed >= 0) { 
        MovePositive();
    } else {
        MoveNegative();
    }
    speed = abs(speed);
    speed = speed * 255;
    analogWrite(inPWM_, speed);
}
