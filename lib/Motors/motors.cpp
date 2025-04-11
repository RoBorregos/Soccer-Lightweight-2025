#include "motors.h"
#include "Arduino.h"
#include "constants.h"

Motors::Motors(uint8_t speed1, uint8_t in1_1, uint8_t in2_1, uint8_t speed2, uint8_t in1_2, uint8_t in2_2, uint8_t speed3, uint8_t in1_3, uint8_t in2_3) :
    upper_right_motor_(speed2, in1_2, in2_2),
    upper_left_motor_(speed1, in1_1, in2_1),
    lower_center_motor_(speed3, in1_3, in2_3)
{};

void Motors::InitializeMotors()
{
    upper_right_motor_.InitializeMotor();
    upper_left_motor_.InitializeMotor();
    lower_center_motor_.InitializeMotor();
};

void Motors::SetAllSpeeds(uint8_t pwm)
{
    upper_right_motor_.SetPWM(pwm);
    upper_left_motor_.SetPWM(pwm);
    lower_center_motor_.SetPWM(pwm);
};

void Motors::StopAllMotors()
{
    upper_right_motor_.StopMotor();
    upper_left_motor_.StopMotor();
    lower_center_motor_.StopMotor();
};

void Motors::MoveOmnidirectionalBase(double degree, float speed, double speed_w)
{
    float upper_left_speed = cos(((degree - 150) * PI / 180)) * speed + speed_w;
    float lower_center_speed = cos(((degree - 270) * PI / 180)) * speed + speed_w;
    float upper_right_speed = cos(((degree - 30) * PI / 180)) * speed + speed_w;
    upper_left_motor_.SetSpeed(upper_left_speed);
    lower_center_motor_.SetSpeed(lower_center_speed);
    upper_right_motor_.SetSpeed( upper_right_speed);
};

void Motors::LineCorrection(double degree, float speed, int correction_time) {
    unsigned long start_time = millis(); // Registrar el tiempo de inicio
    MoveOmnidirectionalBase(degree, speed, 0); // Moverse en la dirección especificada
    while (millis() - start_time < correction_time) {
    // Mantener el movimiento hasta que pase el tiempo de corrección    
    }
    StopAllMotors(); 
}