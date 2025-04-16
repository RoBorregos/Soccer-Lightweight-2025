#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"

int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;

Bno bno;
IRRing irring;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

void setup() {
    Serial.begin(9600);
    unsigned long currentTime = millis();
    bno.InitializeBNO();
    motors.InitializeMotors();
    irring.init(&currentTime);
    irring.SetOffset(0.0);
}

void loop(){
    irring.UpdateData();
    double ballAngle = irring.GetAngle();
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    motors.MoveOmnidirectionalBase(ballAngle*1.1, 0.5, 0);
    if (speed_w > 0.1 || speed_w < -0.1) {
        motors.StopAllMotors();
        motors.MoveOmnidirectionalBase(0, 0, speed_w);
    }
    Serial.print("Angle: ");
    Serial.print(ballAngle);
    Serial.print(" Yaw: ");
    Serial.println(yaw);
}