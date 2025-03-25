#ifndef motor_h
#define motor_h

#include <Arduino.h>
#pragma once

class Motor
{
public:
    Motor(){};
    Motor(const uint8_t speed,const  uint8_t in1, const uint8_t in2);
    void InitializeMotor();
    void MoveForward();
    void MoveBackward();
    void StopMotor();
    void SetSpeed(const uint8_t pwm, const  uint8_t speed);
    void setsSpeed(const uint8_t speed){speed_=speed;};
    void setsIn1(const uint8_t in1){in1_=in1;};
    void setsIn2(const uint8_t in2){in2_=in2;};
    const uint8_t getsSpeed(){return speed_;};
    const uint8_t getsIn1(){return in1_;};
    const uint8_t getsIn2(){return in2_;};
    uint8_t GetSpeed();
    uint8_t GetIn1();
    uint8_t GetIn2();
    float GetRPM();
    float GetAngularVelocity();
    float GetDegree();
    void SetDirectionAndMove(float value);
    void SetDirectionAndMoveWithImu(float value);

private:
    uint8_t speed_;
    uint8_t in1_;
    uint8_t in2_;
};

#endif
