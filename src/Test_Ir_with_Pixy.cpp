#include <Arduino.h>
#include "motors.h"
#include "BNO.h"
#include "IRRing.h"
#include "PID.h"
#include "PixyCam.h"

int setpoint = 0;
Bno bno;
PID pid(1.125/kMaxPWM, 0/kMaxPWM, 0/kMaxPWM, 100);
IRRing irring;
PixyCam pixy;
int targetSignature = 1;
double KCorrectionDegreeOffset = 16;
const uint32_t kCommunicationMode = SPI_MODE0; // This mode is used because we are using the SPI communication
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
void setup() {
    Serial.begin(9600);
    unsigned long currentTime = millis();
    bno.InitializeBNO();
    motors.InitializeMotors();
    pixy.Init(kCommunicationMode);
    irring.init(&currentTime);
    irring.SetOffset(0.0);
}
void loop() {
    irring.UpdateData();
    double ballAngle = irring.GetAngle(1.1, 0.96, 0.95); // Ángulo hacia la pelota
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    if (ballAngle>15){
        motors.MoveOmnidirectionalBase(ballAngle, 0.5, speed_w,KCorrectionDegreeOffset);
    }else{
        pixy.updateData();
        int numberObjects = pixy.numBlocks();
        Serial.print("Number of objects: ");
        Serial.println(numberObjects);
        for (int i = 0; i < numberObjects; i++){
            int signature = pixy.getSignature();
            if (signature == targetSignature){
                int x = pixy.getX(i);
                int y = pixy.getY(i);
                float angle = (x-160)*(60.0/320.0)*-1;
                motors.MoveOmnidirectionalBase(angle, 0.5, speed_w,KCorrectionDegreeOffset); 
            }
        }
    }
}  
