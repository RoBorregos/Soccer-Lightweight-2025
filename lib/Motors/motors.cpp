#include "motors.h"
#include "Arduino.h"
#include "constants.h"

Motors::Motors(uint8_t speed1, uint8_t in1_1, uint8_t in2_1, uint8_t speed2, uint8_t in1_2, uint8_t in2_2, uint8_t speed3, uint8_t in1_3, uint8_t in2_3) 
:upper_right_motor_(speed1, in1_1, in2_1),
  upper_left_motor_(speed2, in1_2, in2_2),
  lower_center_motor_(speed3, in1_3, in2_3)
{};

void Motors::InitializeMotors()
{
    upper_right_motor_.InitializeMotor();
    upper_left_motor_.InitializeMotor();
    lower_center_motor_.InitializeMotor();
};
// Sets the speed for all motors simultaneously.

void Motors::SetAllSpeeds(uint8_t speed)
{
    upper_right_motor_.SetSpeed(kMotor1Pwm, speed);
    upper_left_motor_.SetSpeed(kMotor2Pwm, speed);
    lower_center_motor_.SetSpeed(kMotor3Pwm, speed);
};

// Prints the current speed of all motors to the serial monitor.
void Motors::GetAllSpeeds()
{
    Serial.print("Motor 1: ");
    Serial.println(upper_right_motor_.GetSpeed());
    Serial.print("Motor 2: ");
    Serial.println(upper_left_motor_.GetSpeed());
    Serial.print("Motor 3: ");
    Serial.println(lower_center_motor_.GetSpeed());
};


// Stops all motors by setting their speed to zero.
void Motors::StopAllMotors()
{
    upper_right_motor_.StopMotor();
    upper_left_motor_.StopMotor();
    lower_center_motor_.StopMotor();
};

void Motors::MoveMotor1()
{
    upper_right_motor_.MoveForward();
};

void Motors::MoveMotor2()
{
    upper_left_motor_.MoveForward();
};

void Motors::MoveMotor3()
{
    lower_center_motor_.MoveForward();
};
/*
void Motors::MoveBaseForward()
{
    upper_right_motor_.MoveForward();
    upper_left_motor_.MoveForward();
    lower_right_motor_.MoveForward();
    lower_left_motor_.MoveForward();
};

void Motors::MoveBaseRight()
{
    StopAllMotors();
    upper_right_motor_.MoveForward();
    upper_left_motor_.MoveBackward();
    lower_right_motor_.MoveBackward();
    lower_left_motor_.MoveBackward();
};

void Motors::MoveBaseLeft()
{
    StopAllMotors();
    upper_right_motor_.MoveBackward();
    upper_left_motor_.MoveForward();
    lower_right_motor_.MoveForward();
    lower_left_motor_.MoveForward();
};

void Motors::MoveBaseBackward()
{
    StopAllMotors();
    upper_left_motor_.MoveBackward();
    lower_right_motor_.MoveForward();
};
*/

void Motors::MoveBaseInDirection(int degree, uint8_t speed)
{
    float m1 = cos(((30 - degree) * PI / 180));
    float m2 = cos(((150 - degree) * PI / 180));
    float m3 = cos(((270 - degree) * PI / 180));
    int speedA = abs(int(m1 * speed));
    int speedB = abs(int(m2 * speed));
    int speedC = abs(int(m3 * speed));

    analogWrite(upper_right_motor_.GetSpeed(), speedA);
    analogWrite(upper_left_motor_.GetSpeed(), speedB);
    analogWrite(lower_center_motor_.GetSpeed(), speedC);

    if (m1 >= 0) upper_right_motor_.MoveForward(); else upper_right_motor_.MoveBackward();
    if (m2 >= 0) upper_left_motor_.MoveForward(); else upper_left_motor_.MoveBackward();
    if (m3 >= 0) lower_center_motor_.MoveForward(); else lower_center_motor_.MoveBackward();
};

void Motors::MoveBaseWithImu(double degree, uint8_t speed, double speed_w)
{
    float m1 = cos(((30 - degree) * PI / 180)) * speed + speed_w;
    float m2 = cos(((150 - degree) * PI / 180)) * speed + speed_w;
    float m3 = cos(((270 - degree) * PI / 180)) * speed + speed_w;
    int speedA = abs(int(m1));
    int speedB = abs(int(m2));
    int speedC = abs(int(m3));

    analogWrite(upper_right_motor_.GetSpeed(), speedA);
    analogWrite(upper_left_motor_.GetSpeed(), speedB);
    analogWrite(lower_center_motor_.GetSpeed(), speedC);

    if (m1 >= 0) upper_right_motor_.MoveForward(); else upper_right_motor_.MoveBackward();
    if (m2 >= 0) upper_left_motor_.MoveForward(); else upper_left_motor_.MoveBackward();
    if (m3 >= 0) lower_center_motor_.MoveForward(); else lower_center_motor_.MoveBackward();
};