#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"
#include "Ultrasonic.h"

int setpoint = 0;
float kBallFollowOffsetBack = 1.0;
float kBallFollowOffsetSide = 1.0;
float kBallFollowOffsetFront = 1.0;
unsigned long currentTime = millis();
float lastKnownGoalX = 0;
float lastKnownGoalY = 0;
int targetSignature = 2;
bool goalDetected = false;
bool ballControlled = false;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 275;
double kCorrectionDegreeOffset = 0;
Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
Bno bno;
PixyCam pixy;
IRRing irring;
Ultrasonic ultrasonic(kTrigPin, kEchoPin);
PID pid(0.56/kMaxPWM, 0.005/kMaxPWM, 0.5/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

uint8_t switchPin = 42;

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
    motors.StartStopMotors(switchPin);
    pixy.updateData();
    int numberObjects = pixy.numBlocks();
    float yaw = bno.GetBNOData();
    float speed_w = pid.Calculate(setpoint, yaw);
    // motors.MoveOmnidirectionalBase(ballAngle, 0.35, speed_w, kCorrectionDegreeOffset);
    for (int i = 0; i < numberObjects; i++){
        int signature = pixy.getSignature();
        if (signature == targetSignature){
            int x = pixy.getX(i);
            int y = pixy.getY(i);
            float angle = pixy.getGoalAngle(x);
            float distanceY = ultrasonic.getDistanceY();
            float distanceX = ultrasonic.getDistanceX(angle, distanceY);
            Serial.print("Signature: ");
            Serial.print(signature);
            Serial.print("  Angle: ");
            Serial.print(angle);
            Serial.print("  Distance Y: ");
            Serial.print(distanceY);
            Serial.print("  Distance X: ");
            Serial.println(distanceX);

            // if (distanceX >= 15){
            //     motors.MoveOmnidirectionalBase(-90, 0.35, speed_w, kCorrectionDegreeOffset);
            // } else if (distanceX <= -15){
            //     motors.MoveOmnidirectionalBase(90, 0.35, speed_w, kCorrectionDegreeOffset);
            // }
        }
    }
}





//--------------------------------------Simple arduino code to test the ultrasonic sensor--------------------------------------
// #include <Arduino.h>

// // sensor ultrasónico 
// int trigPin = 33; // mandar onda de sonido
// int echoPin = 32; // recibir onda de sonido
// int signal;
// int signalCM;

// void setup(){
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   Serial.begin(9600);
// }

// void loop(){
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10); // Mandar el pulso HIGH por 10 microsegundos
//   digitalWrite(trigPin, LOW);

//   // Leer el tiempo del eco
//   signal = pulseIn(echoPin, HIGH, 30000); // Espera hasta 30 ms (para 5 metros)
//   signalCM = signal * 0.0343 / 2; // Conversión de tiempo a distancia en cm

//   // Mostrar los resultados en el monitor serial
//   Serial.print("signal: "); Serial.print(signal); 
//   Serial.print(".  signalCM: "); Serial.print(signalCM);
//   Serial.println();
// }