#include "Motors.h"
#include "constants.h"
s.h
Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

void setup() {
    Serial.begin(9600);
    motors.InitializeDriver();  // Inicializar el driver de los motores
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");
}

void loop() {
    Serial.println("Moviendo hacia adelante...");
    motors.MoveForward();
    delay(2000);

    Serial.println("Moviendo hacia atrás...");
    motors.MoveBackward();
    delay(2000);

    Serial.println("Girando a la izquierda...");
    motors.MoveLeft();
    delay(2000);

    Serial.println("Girando a la derecha...");
    motors.MoveRight();
    delay(2000);

    Serial.println("Girando en círculos...");
    for (int angle = 0; angle < 360; angle += 45) {  // Gira en múltiples ángulos
        motors.MoveMotors(angle, 150);
        delay(500);
    }

    Serial.println("Deteniendo motores...");
    motors.StopMotors();
    delay(3000);  
}


