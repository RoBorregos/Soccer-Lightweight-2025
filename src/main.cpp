#include "motors.h"


Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");
}

void loop() {
    Serial.println("Mover hacia adelante");
    motors.SetAllSpeeds(90);
    motors.MoveForward();
    }