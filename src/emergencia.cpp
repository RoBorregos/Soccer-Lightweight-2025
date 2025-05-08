#include "motors.h"
#include "motor.h"
#include "constants.h"
#include <Arduino.h>
#include "PID.h"


Motor upper_left_motor(kMotor1Pwm, kMotor1In1, kMotor1In2);
Motor lower_center_motor(kMotor2Pwm, kMotor2In2, kMotor2In1);
Motor upper_right_motor(kMotor3Pwm, kMotor3In1, kMotor3In2);

// motor pins for striker jamaica
// Motor upper_left_motor(kMotor1Pwm, kMotor1In2, kMotor1In1);
// Motor lower_center_motor(kMotor3Pwm, kMotor3In2, kMotor3In1);
// Motor upper_right_motor(kMotor2Pwm, kMotor2In2, kMotor2In1);

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In2, kMotor2In1,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
// Motors motors( // motor pins for striker jamaica
//     kMotor1Pwm, kMotor1In2, kMotor1In1,
//     kMotor3Pwm, kMotor3In2, kMotor3In1,
//     kMotor2Pwm, kMotor2In2, kMotor2In1);
int i = 0;
uint8_t switchPin = 42;

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors(switchPin);
}

void loop() {
    motors.StartStopMotors(switchPin);
    // motors.MoveOmnidirectionalBase(0, 0.5, 0, 0);
    //--------------------------Test individual motor--------------------------
    upper_left_motor.SetSpeed(65);
    upper_left_motor.MovePositive();
    delay(2000);
    motors.StopAllMotors();
    lower_center_motor.SetSpeed(65);
    lower_center_motor.MovePositive();
    delay(2000);
    motors.StopAllMotors();
    upper_right_motor.SetSpeed(65);
    upper_right_motor.MovePositive();
    delay(2000);
    motors.StopAllMotors();
    
    // upper_left_motor.SetSpeed(65);
    // upper_left_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
    // lower_center_motor.SetSpeed(65);
    // lower_center_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
    // upper_right_motor.SetSpeed(65);
    // upper_right_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
}