#include "motors.h"
#include "BNO.h"
#include "PID.h"
#include "constants.h"

unsigned long start_millis;
unsigned long current_millis;
double yaw;
double speed_w;
int setpoint = 0;

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

Bno bno;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100); // PID parameters: kp, ki, kd, max_error update for demo robot on april 5 2025

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors();  // Inicializar los motores
    bno.InitializeBNO();
    start_millis = millis();
}

void loop() {
    yaw = bno.GetBNOData();
    speed_w = pid.Calculate(setpoint, yaw);
    Serial.print("Yaw: ");
    Serial.println(yaw);
    Serial.print("   Speed_w: ");
    Serial.println(speed_w);
    motors.MoveOmnidirectionalBase(0, 0.65, 0);
    if (speed_w > 0.1 || speed_w < -0.1) {
        motors.StopAllMotors();
        motors.MoveOmnidirectionalBase(0, 0, speed_w);
    }
    // if(abs(yaw) > 5){
    //     motors.MoveOmnidirectionalBase(0, 0, speed_w);
    // }
    // else if(abs(yaw) < 5){
    //     motors.StopAllMotors();
    // }
}