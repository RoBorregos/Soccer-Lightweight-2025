#include "motors.h"
#include "motor.h"
#include "constants.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "PixyCam.h" 


// Motor upper_left_motor(kMotor1Pwm, kMotor1In1, kMotor1In2);
// Motor lower_center_motor(kMotor2Pwm, kMotor2In1, kMotor2In2);
// Motor upper_right_motor(kMotor3Pwm, kMotor3In1, kMotor3In2);
Bno bno;
PixyCam pixy;
IRRing irring;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
int i = 0;

void setup() {
    Serial.begin(9600);
    Serial3.begin(19200);
    irring.init(&currentTime);
    irring.SetOffset(0.0);
    pixy.Init();
    motors.InitializeMotors();
    Serial.println("Prueba de motores iniciada.");
}

void loop() {
    currentTime = millis();
    irring.UpdateData();
    double ballAngle = irring.GetAngle();
    double yaw = bno.GetBNOData();

    pixy.updateData();
    int numberObjects=pixy.numBlocks();
    Serial.print("Number of objects:         ");
    Serial.print(numberObjects);
    for (int i=0;i<numberObjects;i++){
        int signature=pixy.getSignature();
        Serial.print("signature:        ");
        Serial.print(signature);
        if (signature==targetSignature){
            int x=pixy.getX(i);
            Serial.print("x:   ");
            Serial.print(x);
            int y=pixy.getY(i);
            Serial.print("y:    ");
            Serial.print(y);
            float angleX = (x - 158) * (60.0 / 316); 
            Serial.print("angleX:       ");
            Serial.print(angleX);
            motors.MoveOmnidirectionalBase(angleX, 0.5, 0);
            double speed_w = pid.Calculate(setpoint, yaw);
            if (speed_w > 0.1 || speed_w < -0.1) {
                motors.StopAllMotors();
                motors.MoveOmnidirectionalBase(0, 0, speed_w);
            delay(1000);
            }
        }
    }
}
    // motors.SetAllSpeeds(255);
    // motors.upper_left_motor_.MovePositive();
    // delay(2000);
    // motors.upper_right_motor_.MovePositive();
    // delay(2000);
    // motors.lower_center_motor_.MovePositive();
    // delay(2000);
    //motors.MoveOmnidirectionalBase(0, 0, 0.18);
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