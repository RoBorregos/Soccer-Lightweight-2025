#include "motors.h"
#include "BNO.h"
#include "PID.h"
#include "constants.h"

unsigned long start_millis;
unsigned long current_millis;
double yaw;
double speed_w;
int setpoint = 0;
double kCorrectionDegreeOffset = 0;

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

Bno bno;
PID pid(0.125/kMaxPWM, 0.1/kMaxPWM, 0.0125/kMaxPWM, 100);
// 1.125
uint8_t switchPin = 42;

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors(switchPin);
    Serial.print("Test BNO");  // Inicializar los motores
    bno.InitializeBNO();
    start_millis = millis();
}

void loop() {
    motors.StartStopMotors(switchPin);
    yaw = bno.GetBNOData();
    speed_w = pid.Calculate(setpoint, yaw);
    Serial.print("Yaw: ");
    Serial.print(yaw);
    Serial.print("   Speed_w: ");
    Serial.println(speed_w);
    //----------------Correction with linear movement---------------------
    
    // motors.MoveOmnidirectionalBase(0, 0.4, speed_w, kCorrectionDegreeOffset);
    

    //--------------------------Correction on ist axis--------------------
    // if(abs(yaw) > 5){
    //     motors.MoveOmnidirectionalBase(0, 0, speed_w, 0);
    // }
    // else if(abs(yaw) < 5){
    //     motors.StopAllMotors();
    // }
}