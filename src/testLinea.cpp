#include "Arduino.h"
#include "stateMachineStricker.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"
#include "Photo.h"
#include "constants.h"
Photo testPhototransistors;
Bno bno;
stateMachineStricker testStricker;
ConstantsStricker::stateMachine state;
ConstantsStricker::sides atackSide = ConstantsStricker::sides::yellow;
void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  testStricker.startObjects();
  delay(1600);
    }
void loop(){
    bool leftLine=testPhototransistors.CheckPhotoLeft();
    Serial.println("leftLine check");
    bool rightLine=testPhototransistors.CheckPhotoRight();
    Serial.println("rightLine check");
    bool frontLine=testPhototransistors.CheckPhotoFront();
    Serial.println("frontLine check");

    state=ConstantsStricker::nothing;
    if((leftLine== false)||(rightLine== false)||(frontLine== false)){
        Serial.println("entrando a line");
        state=ConstantsStricker::line;
        if(state==ConstantsStricker::stateMachine::line){
            if(leftLine== false){
                testStricker.avoidLine(-45);
                Serial.println("searchBall left");
        
            }else if(rightLine== false){
                testStricker.avoidLine(45);
                Serial.println("searchBall right");
            }else if (frontLine== false){
                testStricker.avoidLine(-90);
                Serial.println("searchBall front");
       }}
       delay(500);
    }    

}
/*#include "Photo.h"
#include "Arduino.h"
#include "BNO.h"
#include "constants.h"
#include "PID.h"

int PhotoLeft;
int PhotoRight;
int PhotoFront;
bool PhotoLeftOnLine;
bool PhotoRightOnLine;
bool PhotoFrontOnLine;
int currentTime;
unsigned long motor_start_millis = 0;
unsigned long motor_photo_correction = 90;

Photo photo;
Bno bno;
PID pid;
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

void setup() {
    Serial.begin(9600);
    currentTime = millis();
    Serial.println("starting");
}

void loop() {
    Serial.println("checar todos los fotos");
    PhotoLeft = photo.ReadPhotoLeft();
    PhotoRight = photo.ReadPhotoRight();
    PhotoFront = photo.ReadPhotoFront();
    PhotoLeftOnLine = photo.CheckPhotoLeft();
    PhotoRightOnLine = photo.CheckPhotoRight();
    PhotoFrontOnLine = photo.CheckPhotoFront();
    Serial.println("Moviendo motores");
    motors.MoveBaseWithImu(90, 150, 0);
    /*
    Serial.print("Photo Left: ");
    Serial.print(PhotoLeft);
    Serial.print("   Photo Right: ");
    Serial.print(PhotoRight);
    Serial.print("   Photo Front: ");
    Serial.println(PhotoFront);
    
    Serial.print("Photo Left on line: ");
    Serial.print(PhotoLeftOnLine);
    Serial.print("   Photo Right on line: ");
    Serial.print(PhotoRightOnLine);
    Serial.print("   Photo Front on line: ");
    Serial.println(PhotoFrontOnLine);
    delay(1000);
*/
    /*if (PhotoFrontOnLine==false) {
        Serial.println("Photo front  on line");
        motor_start_millis = currentTime;
        if (currentTime - motor_start_millis >= motor_photo_correction)
        {
            bno.InitializeBNO();
            bno.GetBNOData();
            double yaw=bno.GetYaw();
            double speed_w = pid.Calculate(50, yaw);
            Serial.println("getting w speed");
            unsigned long currentTime = millis();
            int angle=-90;
            while(millis()-currentTime<1000){
                Serial.println("Starting movement");
                Serial.print("MoveBaseWithImu - Angle: "); Serial.print(angle);
                Serial.print(" Velocity: "); Serial.print(255);
                Serial.print(" Speed_W: "); Serial.println(speed_w);
                motors.MoveBaseWithImu(angle,255, speed_w);
                delay(100);
            }
            motors.StopAllMotors();
        
        }
    else if(PhotoLeftOnLine==false) {
        Serial.println("Photo Left on line");
        motor_start_millis = currentTime;
        if (currentTime - motor_start_millis >= motor_photo_correction)
        {
            bno.InitializeBNO();
            bno.GetBNOData();
            double yaw=bno.GetYaw();
            double speed_w = pid.Calculate(50, yaw);
            Serial.println("getting w speed");
            unsigned long currentTime = millis();
            int angle=-45;
            while(millis()-currentTime<1000){
                Serial.println("Starting movement");
                Serial.print("MoveBaseWithImu - Angle: "); Serial.print(angle);
                Serial.print(" Velocity: "); Serial.print(255);
                Serial.print(" Speed_W: "); Serial.println(speed_w);
                motors.MoveBaseWithImu(angle,255, speed_w);
                delay(100);
            }
            motors.StopAllMotors();
        }else if(PhotoRightOnLine==false){
            Serial.println("Photo right on line");
            motor_start_millis = currentTime;
            if (currentTime - motor_start_millis >= motor_photo_correction)
            {
                bno.InitializeBNO();
                bno.GetBNOData();
                double yaw=bno.GetYaw();
                double speed_w = pid.Calculate(50, yaw);
                Serial.println("getting w speed");
                unsigned long currentTime = millis();
                int angle=45;
                while(millis()-currentTime<1000){
                    Serial.println("Starting movement");
                    Serial.print("MoveBaseWithImu - Angle: "); Serial.print(angle);
                    Serial.print(" Velocity: "); Serial.print(255);
                    Serial.print(" Speed_W: "); Serial.println(speed_w);
                    motors.MoveBaseWithImu(angle,255, speed_w);
                    delay(100);
                }
                motors.StopAllMotors();
            
            }
        }
    }


    /*
    Serial.println("Checking photos");
    PhotoLeftOnLine = photo.CheckPhotoLeft();
    PhotoRightOnLine = photo.CheckPhotoRight();
    Serial.print("Photo Left on line: ");
    Serial.print(PhotoLeftOnLine);
    Serial.print("   Photo Right on line: ");
    Serial.println(PhotoRightOnLine);
    delay(1000);
    */
      //  }*/
   // }
