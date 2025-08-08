#ifndef motors_h
#define motors_h

#include "Arduino.h"
#include "motor.h"
#include "constants.h"

class Motors
{
public:
    Motor upper_right_motor_;
    Motor upper_left_motor_;
    Motor lower_center_motor_;
    Motors(uint8_t speed1, uint8_t in1_1, uint8_t in2_1,
           uint8_t speed2, uint8_t in1_2, uint8_t in2_2,
           uint8_t speed3, uint8_t in1_3, uint8_t in2_3);
    void InitializeMotors(uint8_t switchPin);
    void StartStopMotors(uint8_t switchPin);
    void SetAllSpeeds(uint8_t pwm);
    void StopAllMotors();
    
    void GetAllSpeeds();
    void MoveOmnidirectionalBase(double target_angle, float speed, double speed_w);
    void LineCorrection(double degree);

private:
};

#endif