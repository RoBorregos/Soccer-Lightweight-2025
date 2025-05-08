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
}
