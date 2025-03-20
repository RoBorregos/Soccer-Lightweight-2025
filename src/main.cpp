#include "statusMachineStricker.h"
#include "Arduino.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include<Wire.h>
#include "BNO.h"
#include <PID.h>
#include "Photo.h"

int atack=1;
SingleEMAFilter<int>filterAnlogo(0.6);
Motors motorsRobot(kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2,
    kMotor4Pwm, kMotor4In1, kMotor4In2);

Bno bno;
Photo photo;
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
  //Search ball
  if(state==ConstantsStricker::searchBall){
    Serial.println("search");
    searchBall();
  }
  //Go to the goal with the ball
  if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    updateGoalData();
  }
}
