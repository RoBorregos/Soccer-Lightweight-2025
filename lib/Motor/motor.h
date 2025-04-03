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
    uint8_t GetInPWM();
    uint8_t GetIn1();
    uint8_t GetIn2();
    float GetRPM();
    float GetAngularVelocity();
    float GetDegree();
    void SetDirection(float value);
    void SetSpeed(float speed);

private:
    uint8_t inPWM_;
    uint8_t in1_;
    uint8_t in2_;
};

#endif
