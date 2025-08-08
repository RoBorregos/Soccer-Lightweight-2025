#ifndef motor_h
#define motor_h

#include <Arduino.h>
#pragma once

class Motor
{
public:
    Motor(const uint8_t inPWM,const  uint8_t in1, const uint8_t in2);
    void InitializeMotor();
    void MovePositive();
    void MoveNegative();
    void StopMotor();
    void SetPWM(const uint8_t pwm);
    void SetSpeed(float speed);

private:
    uint8_t inPWM_;
    uint8_t in1_;
    uint8_t in2_;
    uint16_t frequency = 1000;
    uint8_t resolution = 8;
};

#endif
