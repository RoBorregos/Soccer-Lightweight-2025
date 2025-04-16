#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "PID.h"

float angleGoal=0;
String incomingDataOpenMV="";
int setpoint = 0;
const int kBallFollowOffset=1.1;


Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
Bno bno;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);

void setup()
{
    Serial.begin(115200); //Modificar segun el serial al que se conecta la OpenMV
    Serial.begin(9600);
    motors.InitializeMotors();
    Serial.println("Prueba de motores iniciada.");
    bno.InitializeBNO();
}

void loop(){
    double yaw = bno.GetBNOData();

    incomingDataOpenMV = Serial.readStringUntil('\n');
    angleGoal = incomingDataOpenMV.toFloat();
    Serial.print("angleGoal: ");
    Serial.println(angleGoal);
    motors.MoveOmnidirectionalBase(angleGoal, 0.5, 0);
    double speed_w = pid.Calculate(setpoint, yaw);
            if (speed_w > 0.1 || speed_w < -0.1) {
                motors.StopAllMotors();
                motors.MoveOmnidirectionalBase(0, 0, speed_w);
            }
}