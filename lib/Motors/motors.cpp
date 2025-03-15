#include "motors.h"
#include "Arduino.h"
#include "constants.h"

Motors::Motors(uint8_t speed1, uint8_t in1_1, uint8_t in2_1, uint8_t speed2, uint8_t in1_2, uint8_t in2_2, uint8_t speed3, uint8_t in1_3, uint8_t in2_3, uint8_t speed4, uint8_t in1_4, uint8_t in2_4) 
:upper_right_motor_(speed1, in1_1, in2_1),
  upper_left_motor_(speed2, in1_2, in2_2),
  lower_right_motor_(speed3, in1_3, in2_3),
  lower_left_motor_(speed4, in1_4, in2_4)
{};

void Motors::InitializeMotors()
{
    upper_right_motor_.InitializeMotor();
    upper_left_motor_.InitializeMotor();
    lower_right_motor_.InitializeMotor();
    lower_left_motor_.InitializeMotor();
};
// Sets the speed for all motors simultaneously.

void Motors::SetAllSpeeds(uint8_t speed)
{
    upper_right_motor_.SetSpeed(kMotor1Pwm, speed);
    upper_left_motor_.SetSpeed(kMotor2Pwm, speed);
    lower_right_motor_.SetSpeed(kMotor3Pwm, speed);
    lower_left_motor_.SetSpeed(kMotor4Pwm, speed);
};

// Prints the current speed of all motors to the serial monitor.
void Motors::GetAllSpeeds()
{
    Serial.print("Motor 1: ");
    Serial.println(upper_right_motor_.GetSpeed());
    Serial.print("Motor 2: ");
    Serial.println(upper_left_motor_.GetSpeed());
    Serial.print("Motor 3: ");
    Serial.println(lower_right_motor_.GetSpeed());
    Serial.print("Motor 4: ");
    Serial.println(lower_left_motor_.GetSpeed());
};

// Stops all motors by setting their speed to zero.
void Motors::StopAllMotors()
{
    upper_right_motor_.StopMotor();
    upper_left_motor_.StopMotor();
    lower_right_motor_.StopMotor();
    lower_left_motor_.StopMotor();
};

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


void Motors::MoveBaseInDirection(int degree, uint8_t speed)
{
    float m1 = cos(((45 + degree) * PI / 180));
    float m2 = cos(((135 + degree) * PI / 180));
    float m3 = cos(((225 + degree) * PI / 180));
    float m4 = cos(((315 + degree) * PI / 180));
    int speedA = abs(int(m1 * speed));
    int speedB = abs(int(m2 * speed));
    int speedC = abs(int(m3 * speed));
    int speedD = abs(int(m4 * speed));

    analogWrite(upper_right_motor_.GetSpeed(), speedA);
    analogWrite(upper_left_motor_.GetSpeed(), speedB);
    analogWrite(lower_right_motor_.GetSpeed(), speedC);
    analogWrite(lower_left_motor_.GetSpeed(), speedD);
};

void Motors::MoveBaseWithImu(double degree, uint8_t speed, double speed_w)
{
    float m2 = cos(((45 + degree) * PI / 180)) * speed + speed_w;
    float m3 = cos(((135 + degree) * PI / 180)) * speed + speed_w;
    float m4 = cos(((225 + degree) * PI / 180)) * speed + speed_w;
    float m1 = cos(((315 + degree) * PI / 180)) * speed + speed_w;
    int speedA = abs(int(m1));
    int speedB = abs(int(m2));
    int speedC = abs(int(m3));
    int speedD = abs(int(m4));

    analogWrite(upper_right_motor_.GetSpeed(), speedA);
    analogWrite(upper_left_motor_.GetSpeed(), speedB);
    analogWrite(lower_right_motor_.GetSpeed(), speedC);
    analogWrite(lower_left_motor_.GetSpeed(), speedD);

};