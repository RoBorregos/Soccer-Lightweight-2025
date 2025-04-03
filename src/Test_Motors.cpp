#include "motors.h"

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
    // motors.MoveBaseWithImu(0, 120, 0);
    
    motors.SetAllSpeeds(120);
    motors.MoveMotor1();
    delay(2000);
    motors.StopAllMotors();
    motors.MoveMotor2();
    delay(2000);
    motors.StopAllMotors();
    motors.MoveMotor3();
    delay(2000);
    motors.StopAllMotors();
}