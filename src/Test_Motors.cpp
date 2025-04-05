#include "motors.h"
#include "motor.h"
#include "constants.h"

Motor upper_left_motor(kMotor1Pwm, kMotor1In1, kMotor1In2);
Motor lower_center_motor(kMotor2Pwm, kMotor2In1, kMotor2In2);
Motor upper_right_motor(kMotor3Pwm, kMotor3In1, kMotor3In2);

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
int i = 0;

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors();
    Serial.println("Prueba de motores iniciada.");
}

void loop() {
    motors.MoveOmnidirectionalBase(0, 0, 0.18);
    // upper_left_motor.SetSpeed(255);
    // upper_left_motor.MovePositive();
    // delay(2000);
    // motors.StopAllMotors();
    // lower_center_motor.SetSpeed(255);
    // lower_center_motor.MovePositive();
    // delay(2000);
    // motors.StopAllMotors();
    // upper_right_motor.SetSpeed(255);
    // upper_right_motor.MovePositive();
    // delay(2000);
    // motors.StopAllMotors();
}