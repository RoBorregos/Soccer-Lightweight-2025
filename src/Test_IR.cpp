#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "IRSOS.h"

int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;
float kBallFollowOffset = 1.1;

Bno bno;
int kLineCorrectionTime = 200; // Tiempo de corrección en milisegundos
IRRing irring;
PID pid(0.8437/kMaxPWM, 0.02/kMaxPWM, 0.1/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
int kCorrectionDegreeOffset = 16;

uint8_t switchPin = 42;

uint8_t LeftIRPin = 2; // Pin for the left IR sensor
uint8_t RightIRPin = 3; // Pin for the right IR sensor
uint8_t FrontIRPin = 4; // Pin for the front IR sensor

IRSOS irsos(LeftIRPin, RightIRPin, FrontIRPin);

void setup() {
    Serial.begin(115200);
    unsigned long currentTime = millis();
    bno.InitializeBNO();
    motors.InitializeMotors(switchPin);
    irring.init(&currentTime);
    irring.SetOffset(0.0);
    digitalWrite(LED_BUILTIN, LOW);
    irsos.IRInit();
}

void loop(){
    irring.UpdateData();
    double ballAngle = irring.GetAngle(1.0, 1.0, 1.0);
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    Serial.print("Ball angle: ");
    Serial.print(ballAngle);
    Serial.print(" Yaw: ");
    Serial.println(yaw);
    // if (ballAngle != 0){
    //     digitalWrite(LED_BUILTIN, HIGH);
    //     delay(600);
    //     digitalWrite(LED_BUILTIN, LOW);
    //     delay(600);
    // } else if (ballAngle == 0){
    //     digitalWrite(LED_BUILTIN, HIGH);
    // }
    // motors.MoveOmnidirectionalBase(ballAngle, 0.5, speed_w, kCorrectionDegreeOffset);
    // if (speed_w > 0.1 || speed_w < -0.1) {
    //      motors.StopAllMotors();
    //      motors.MoveOmnidirectionalBase(0, 0, speed_w);
    // }


    int IRLedto = irsos.getLeftIRSignal();
    int IRRightto = irsos.getRightIRSignal();
    int IRFrontto = irsos.getFrontIRSignal();

    Serial.print("Left IR: ");
    Serial.print(IRLedto);
    Serial.print(" Right IR: ");
    Serial.print(IRRightto);
    Serial.print(" Front IR: ");
    Serial.println(IRFrontto);
}





 // Esto es una idea de como se puede usar el PID para calcular el offset
    // double angleWithoutOffset = irring.GetAngle();
    // //Usar pid para calcular el offset
    // double offset = pid.Calculate(setpoint, angleWithoutOffset);
    // Serial.print("Offset: ");
    // Serial.println(offset);
    // double ballAnglewithOffset = irring.GetAnglewithOffset(offset);
    // Serial.print("Ball angle with offset: ");
    // Serial.println(ballAnglewithOffset);
    // //Usar el offset para corregir el movimiento
    // motors.MoveOmnidirectionalBase(ballAnglewithOffset, 0.5, 0);