#include "motors.h"
#include <Wire.h>
#include "BNO.h"
#include <PID.h>
#include "IRRing.h"

/*unsigned long start_millis;
unsigned long current_millis;
int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;

unsigned long motor_start_millis = 0;
unsigned long motor_photo_correction = 90;

IRRing irring;
// Definir PID con parámetros (ajústalos según tu caso)
PID pid(6.0, 0.000, 30, 200);

Bno bno;
//PID pid(0.6, 0.00735, 45, 200);//
Motors motors(
  kMotor1Pwm, kMotor1In1, kMotor1In2,
  kMotor2Pwm, kMotor2In1, kMotor2In2,
  kMotor3Pwm, kMotor3In1, kMotor3In2,
  kMotor4Pwm, kMotor4In1, kMotor4In2
);

void setup() {
    Serial.begin(9600);
    unsigned long currentTime = millis();
    analogReadResolution(12);
    //ads.initializeAds();
    motors.InitializeMotors(); 
    Bno.InitializeBNO();
    start_millis = millis();
    irring.init(&currentTime);
    irring.setOffset(0.0);
}

void loop() {

    double yaw = bno.GetYaw();    
    translation_angle = 0;
    adjust_angle = translation_angle - 90;
    double speed_w = pid.Calculate(setpoint, yaw);
    if(speed_w != 0){
        motors.StopAllMotors();
        motors.MoveBaseWithImu(0, 0, speed_w);
    }

    irring.updateData();
    double angle=irring.getAngle();
    double newAngle=(angle<0 ? 360+angle:angle);
    newAngle=360-newAngle;
    double strength=irring.getStrength();
    
    if (newAngle > 45 && newAngle < 315) {
        motors.MoveBaseWithImu(newAngle,150,0);
        Serial.println("fuera de rango");
    }
    else if (newAngle < 45 || newAngle > 315) {
        motors.StopAllMotors();
        Serial.println("dentro de rango");
    }
}*/



