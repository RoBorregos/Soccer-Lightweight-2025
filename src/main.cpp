#include "motors.h"
#include<Wire.h>
#include "BNO.h"
#include <PID.h>

// Definir PID con parámetros (ajústalos según tu caso)
PID pid(6.0, 0.000, 30, 200);

Bno bno;
/*PID pid(0.6, 0.00735, 45, 200);*/
Motors motors(
  kMotor1Pwm, kMotor1In1, kMotor1In2,
  kMotor2Pwm, kMotor2In1, kMotor2In2,
  kMotor3Pwm, kMotor3In1, kMotor3In2,
  kMotor4Pwm, kMotor4In1, kMotor4In2
);

void setup() {
    Serial.begin(9600);

}

void loop() {

    bno.GetBNOData();
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
}
    



