#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"
#include "Ultrasonic.h"

bool isCorrecting = false;
int setpoint = 0;
float kBallFollowOffsetBack = 1.0;
float kBallFollowOffsetSide = 1.0;
float kBallFollowOffsetFront = 1.0;
uint8_t targetSignature = 2;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 375;
double kCorrectionDegreeOffset = 16;
unsigned long currentTime = millis();

Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
Bno bno;
PixyCam pixy;
IRRing irring;
Ultrasonic ultrasonic(kTrigPin, kEchoPin);
PID pid_static(0.875/kMaxPWM, 0/kMaxPWM, 0/kMaxPWM, 100); 
PID pid_w(0.9375/kMaxPWM, 0.01/kMaxPWM, 0.01/kMaxPWM, 100); //0.125 0.1 0.0125 domingo 4 de mayo 21:30
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

uint8_t switchPin = 42;

unsigned long lastUltrasonicReadTime = 0; // Último tiempo de lectura del ultrasonido
const unsigned long ultrasonicReadInterval = 50; // Intervalo de lectura en milisegundos
float distanceY = 0; // Última lectura de distancia Y
float distanceX = 0; // Última lectura de distancia X
TargetGoalData targetGoalData = {0}; // Estructura para almacenar los datos del objetivo

int X;

uint8_t kGoalkeeperCorrectionTime = 50;
float correctionStartTime = 0;

void setup() {
    Serial.begin(9600);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors(switchPin);
    bno.InitializeBNO();
    ultrasonic.UltrasonicInit();
    irring.init(&currentTime);
    irring.SetOffset(0.0);
}

void loop() {
    uint8_t j = 0;
    motors.StartStopMotors(switchPin); // Switch a pin digital 
    pixy.updateData();
    irring.UpdateData();
    uint8_t numberObjects = pixy.numBlocks();
    float yaw = bno.GetBNOData();
    float ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    float speed_w = pid_w.Calculate(setpoint, yaw);
    float staticCorrection = pid_static.Calculate(setpoint, yaw);

    // Actualizar las lecturas del ultrasonido cada cierto tiempo
    if (millis() >= 450){ // Esperar para permitir que el sensor se comience a leer
        if ((millis() - lastUltrasonicReadTime >= ultrasonicReadInterval)) {
            lastUltrasonicReadTime = millis(); // Actualizar el tiempo de la última lectura
            targetGoalData = pixy.getTargetGoalData(numberObjects, targetSignature);
            distanceY = ultrasonic.getDistanceY();
            distanceX = ultrasonic.getDistanceX(targetGoalData.cameraAngle, distanceY);
            X = targetGoalData.x;
        }
    }

    // Serial.print("Signature: ");
    // Serial.print(targetGoalData.signature);
    // Serial.print("  Angle: ");
    // Serial.print(targetGoalData.cameraAngle);
    Serial.print("  Distance Y: ");
    Serial.print(distanceY);
    // Serial.print("  Distance X: ");
    // Serial.print(distanceX);
    Serial.print("  X: ");
    Serial.print(targetGoalData.x);
    // Serial.print("  Yaw: ");
    // Serial.print(yaw);
    Serial.print("  Ball angle: ");
    Serial.println(ballAngle);

    // Verificar si el robot está dentro del rectángulo
    bool dentroDelRectangulo = (distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY && (X <= kRightGoalKeeperTresholdX && X >= kLeftGoalKeeperTresholdX) || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX)); 
    Serial.print("  Dentro del rectangulo: ");
    Serial.println(dentroDelRectangulo);
    
//---------------------------Correccion portero con valor X de la cámara-------------------
if (!dentroDelRectangulo){
//     // Frente centro
    if (distanceY >= kMaxGoalKeeperTresholdY && (X >= kLeftGoalKeeperTresholdX && X <= kRightGoalKeeperTresholdX)){ // || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX))
        motors.MoveOmnidirectionalBase(180, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();;
//     // Atrás centro
    } else if (distanceY <= kMinGoalKeeperTresholdY && (X >= kLeftGoalKeeperTresholdX && X <= kRightGoalKeeperTresholdX)){ // || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(0, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
//     // Frente Izquierda
    } else if (distanceY >= kMaxGoalKeeperTresholdY && X <= kLeftGoalKeeperTresholdX){ // || distanceX >= kGoalKeeperTresholdX
        motors.MoveOmnidirectionalBase(-135, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
//     // Frente Derecha
    } else if (distanceY >= kMaxGoalKeeperTresholdY && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX
        motors.MoveOmnidirectionalBase(135, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
//     // Atrás Izquierda
    } else if (distanceY <= kMinGoalKeeperTresholdY && X <= kLeftGoalKeeperTresholdX){ //  || distanceX >= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(-45, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
//     // Atrás Derecha
    } else if (distanceY <= kMinGoalKeeperTresholdY && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(45, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
//     // Izquierda
    } else if ((distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY) && X <= kLeftGoalKeeperTresholdX){ // || distanceX >= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(-90, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors(); 
     // Derecha
    } else if ((distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY) && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(90, 0.37, speed_w, kCorrectionDegreeOffset);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    }
} if (dentroDelRectangulo) {
    float speed;
    if (ballAngle > 10 || ballAngle < -10){
        speed = 0.37;
    } else if (ballAngle <= 10 && ballAngle >= -10){
        speed = 0.5; 
    }   
    motors.MoveOmnidirectionalBase(ballAngle, 0.35, speed_w, kCorrectionDegreeOffset);
    // motors.StopAllMotors();
} 
}