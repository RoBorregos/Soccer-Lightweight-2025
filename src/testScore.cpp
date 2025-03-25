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
if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    testStricker.goToGoal();
}
}