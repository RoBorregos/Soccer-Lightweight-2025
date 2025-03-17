#include "motors.h"
#include "BNO.h"
#include "PixyCam.h"
#include <Arduino.h>
#include"IRRing.h"
<<<<<<< HEAD
/*Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);*/
=======
#include "PID.h"
>>>>>>> daaa6f90ff30d9d204fbd92107ab015082f4e6f5

int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;

Bno bno;
IRRing irring;
PID pid(1.5, 0.00735, 45, 200);
Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

void setup() {
    Serial.begin(115200);
    unsigned long currentTime = millis();
    irring.init(&currentTime);
    irring.setOffset(0.0);
}
void loop() {
    bno.getEuler();
    double yaw = bno.getYaw();    
    translation_angle = 0;
    adjust_angle = translation_angle - 90;
    double speed_w = pid.Calculate(setpoint, yaw);
    // motors.MoveMotorsImu(setpoint, 150, 0);
   
    if(speed_w != 0){
        motors.StopMotors();
        motors.MoveMotorsImu(0, 0, speed_w);
    }

    irring.updateData();
    double angle=irring.getAngle();
    double newAngle=(angle<0 ? 360+angle:angle);
    newAngle=360-newAngle;
    double strength=irring.getStrength();
    
    if (newAngle > 45 && newAngle < 315) {
        motors.MoveMotorsImu(newAngle,150,0);
        Serial.println("fuera de rango");
    }
    else if (newAngle < 45 || newAngle > 315) {
        motors.StopMotors();
        Serial.println("dentro de rango");
    }
    Serial.print("Angle: ");
    Serial.print(newAngle);
    Serial.print("\tradio: ");
    Serial.println(strength);
    delay(50);
}

/*PixyCam pixy;
void setup() {
    Serial.begin(9600);
    pixy.init();
}
void loop() {
    pixy.detectGoals();
    delay(1000);
  
}*/


/*Bno bno;
void setup() {
    Serial.begin(9600);
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");

    bno.bno_begin();
}

void loop() {

    bno.getEuler();
    */
    /*
    Serial.println("Mover hacia adelante");
    motors.SetAllSpeeds(90);
    motors.MoveForward();
    
    Serial.println("Mover hacia atrás");
    motors.MoveBackward();
    delay(2000);

    Serial.println("Girar a la izquierda");
    motors.MoveLeft();
    delay(2000);

    Serial.println("Girar a la derecha");
    motors.MoveRight();
    delay(2000);

    Serial.println("Girar en círculos");
    for (int angle = 0; angle < 360; angle += 45) {  // Gira en múltiples ángulos
        motors.MoveMotors(angle, 255);
        delay(500);
    }

    Serial.println("Detener motores");
    motors.StopMotors();
    delay(3000);  
    */
//}