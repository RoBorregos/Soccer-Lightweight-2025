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
    Motor lower_right_motor_;
    Motor lower_left_motor_;
    Motors(){};
    Motors(uint8_t speed1, uint8_t in1_1, uint8_t in2_1,
           uint8_t speed2, uint8_t in1_2, uint8_t in2_2,
           uint8_t speed3, uint8_t in1_3, uint8_t in2_3);
      // Getters
    Motor getUpperRightMotor() const { return upper_right_motor_; }
    Motor getUpperLeftMotor() const { return upper_left_motor_; }
    Motor getLowerRightMotor() const { return lower_right_motor_; }
  
      // Setters
    void setUpperRightMotor(const Motor& motor) { upper_right_motor_ = motor; }
    void setUpperLeftMotor(const Motor& motor) { upper_left_motor_ = motor; }
    void setLowerRightMotor(const Motor& motor) { lower_right_motor_ = motor; }
  
    void InitializeMotors();
    void SetAllSpeeds(uint8_t speed);
    void StopAllMotors();
    void MoveBaseForward();
    void MoveBaseBackward();
    void MoveBaseRight();
    void MoveBaseLeft();
    void MoveBaseInDirection(int degree, uint8_t speed);
    void IndividualMotor(uint8_t motor, uint8_t speed);
    void GetAllSpeeds();
    void MoveOneMotor(uint8_t motor, uint8_t speed);
    void MoveBaseWithImu(double target_angle, uint8_t speed, double speed_w);
    void MoveMotorsProportional(double target_angle, uint8_t setpoint);
};

#endif