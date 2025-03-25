#include "Arduino.h"
#include "stateMachineStricker.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"
#include "Photo.h"
#include "constants.h"
Photo testPhototransistors;
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
    Serial.println("frontLine check");
    bool rightLine=testPhototransistors.CheckPhotoRight();
    Serial.println("frontLine check");
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
    }    
}