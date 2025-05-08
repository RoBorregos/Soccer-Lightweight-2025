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
float kBallFollowOffsetBack = 1.2;
float kBallFollowOffsetSide = 1.0;
float kBallFollowOffsetFront = 1.0;
uint8_t targetSignature = 2;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 375;
double kCorrectionDegreeOffset = 10;
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
PID pid_w(0.75/kMaxPWM, 0/kMaxPWM, 0.005/kMaxPWM, 100); //0.125 0.1 0.0125 domingo 4 de mayo 21:30
//0.9375 0.01 0.01
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In2, kMotor2In1,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

uint8_t switchPin = 42;

unsigned long lastUltrasonicReadTime = 0; // Último tiempo de lectura del ultrasonido
const unsigned long ultrasonicReadInterval = 50; // Intervalo de lectura en milisegundos
float distanceY = 0; // Última lectura de distancia Y
float distanceX = 0; // Última lectura de distancia X
TargetGoalData targetGoalData = {0, 0, 0, 0, 0, 0}; // Estructura para almacenar los datos del objetivo

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
    motors.StartStopMotors(switchPin); // Switch a pin digital 
    pixy.updateData();
    irring.UpdateData();
    uint8_t numberObjects = pixy.numBlocks();
    float yaw = bno.GetBNOData();
    float ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    float speed_w = pid_w.Calculate(setpoint, yaw);

    PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
    PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
    PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);

    motors.MoveOmnidirectionalBase(ballAngle, 0.45, speed_w, 0);

    if (photoDataLeft.is_on_line) {
        motors.MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0, 0);
        delay (kLineCorrectionTime);
        motors.StopAllMotors();
    } else if (photoDataRight.is_on_line) {
        motors.MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0,0 );
        delay (kLineCorrectionTime);
        motors.StopAllMotors();
    } else if (photoDataFront.is_on_line) {
        motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, 0, 0);
        delay (kLineCorrectionTime);
        motors.StopAllMotors();
    }


    
    // if (valueFront >0|| valueLeft  > 0 || valueRight >0){
    //     Serial.println("Linea detectada");
    //     motors.StopAllMotors();
    //     delay(kLineCorrectionTime);

    //     if (valueFront >0){
    //         motors.MoveOmnidirectionalBase(180,0.35,speed_w,kCorrectionDegreeOffset);
    //     }else if (valueLeft >0){
    //         motors.MoveOmnidirectionalBase(45,0.35,speed_w,kCorrectionDegreeOffset);
    //     }else if(valueRight>0){
    //         motors.MoveOmnidirectionalBase(-45,0.35,speed_w,kCorrectionDegreeOffset);
    //     }
    //     return;
    // }
    // // Fase 1: Seguir el balón con el aro IR
    // if (!ballControlled) {
    //     Serial.println("Siguiendo el balón...");
    //     float speed = (abs(ballAngle) > 10) ? 0.35 : 0.55; // Ajustar velocidad según el ángulo
    //     motors.MoveOmnidirectionalBase(ballAngle, speed, speed_w, kCorrectionDegreeOffset);

    //     // Si el balón está controlado (dentro de un rango pequeño de ángulo)
    //     if (abs(ballAngle) <= 10) {
    //         Serial.println("Balón controlado. Verificando portería...");
    //         ballControlled = true; // Cambiar a la siguiente fase
    //         Serial.println("Balón controlado. Cambiando a la portería...");
    //     }
    // }
    // // Fase 2: Ir hacia la portería
    // else if (!goalDetected) {
    //     Serial.println("Buscando portería...");
    //     targetGoalData = pixy.getTargetGoalData(numberObjects, targetSignature);
    //     double angleGoal = targetGoalData.cameraAngle;
    //     Serial.print("Angle goal:");
    //     Serial.println(angleGoal);

    //     // Moverse hacia la portería
    //     motors.MoveOmnidirectionalBase(angleGoal, 0.35, speed_w, kCorrectionDegreeOffset);

    //     // Si la portería es detectada
    //     if (targetGoalData.signature == targetSignature) {
    //         goalDetected = true; // Cambiar a la siguiente fase
    //         Serial.println("Portería detectada. Verificando distancia...");
    //     }
    // }
    // 
    
}
