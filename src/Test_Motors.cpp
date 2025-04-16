#include "motors.h"
#include "motor.h"
#include "constants.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
// #include "PixyCam.h" 


Motor upper_left_motor(kMotor1Pwm, kMotor1In1, kMotor1In2);
Motor lower_center_motor(kMotor2Pwm, kMotor2In1, kMotor2In2);
Motor upper_right_motor(kMotor3Pwm, kMotor3In1, kMotor3In2);
// Bno bno;
// PixyCam pixy;
// IRRing irring;
// PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
int i = 0;

void setup() {
    Serial.begin(9600);
    // Serial3.begin(19200);
    // irring.init(&currentTime);
    // irring.SetOffset(0.0);
    // pixy.Init();
    motors.InitializeMotors();
    Serial.println("Prueba de motores iniciada.");
}

void loop() {
    // motors.MoveOmnidirectionalBase(-90, 0.6, 0);
    //--------------------------Test individual motor--------------------------
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
    
    // upper_left_motor.SetSpeed(255);
    // upper_left_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
    // lower_center_motor.SetSpeed(255);
    // lower_center_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
    // upper_right_motor.SetSpeed(255);
    // upper_right_motor.MoveNegative();
    // delay(2000);
    // motors.StopAllMotors();
}