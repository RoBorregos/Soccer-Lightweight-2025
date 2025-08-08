#include "Arduino.h"
#include "motor.h"
#include "constants.h"

Motor::Motor(const uint8_t inPWM, const uint8_t in1, const  uint8_t in2)
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

void Motor::SetSpeed(float speed) {
    if (speed >= 0) { 
        MovePositive();
    } else {
        MoveNegative();
    }
    speed = abs(speed);
    speed = speed * kMaxPWM;
    if (speed > kMaxPWM) {
        speed = kMaxPWM;
    } else if (speed < kMinPWM) {
        speed = 0;
    }
    analogWrite(inPWM_, speed);
}
