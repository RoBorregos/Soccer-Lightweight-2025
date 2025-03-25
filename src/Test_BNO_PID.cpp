#include "motors.h"
#include "BNO.h"
#include "PID.h"

unsigned long start_millis;
unsigned long current_millis;
int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;


Motors motors(
    kMotor1In1, kMotor2In2, kMotor1Pwm,
    kMotor2In1, kMotor2In2, kMotor2Pwm,
    kMotor3In1, kMotor3In2, kMotor3Pwm,
    kMotor4In1, kMotor4In2, kMotor4Pwm 
);

Bno bno;
PID pid(1.5, 0.00735, 45, 200); // parametros para correccion angular (1.5, 0.00735, 45, 200)

void setup() {
    Serial.begin(9600);
    analogReadResolution(12);
    //ads.initializeAds();
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");
    bno.InitializeBNO();
    start_millis = millis();
}

void loop() {
    
bno.GetBNOData();
double yaw = bno.GetYaw();    
translation_angle = 0;
adjust_angle = translation_angle - 90;
double speed_w = pid.Calculate(setpoint, yaw);
Serial.println(yaw);

if(speed_w != 0){
    motors.StopAllMotors();
    motors.MoveBaseWithImu(0, 0, speed_w);
}
}