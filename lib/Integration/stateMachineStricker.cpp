#include "stateMachineStricker.h"
void stateMachineStricker::startObjects(){
    Serial.begin(115200);
    unsigned long currentTime = millis();
    robotPid.setKp(0.2);
    robotPid.setMinToMove(40);
    bno.InitializeBNO();
    unsigned long current_time = millis();
    robotIrRing.Init(&current_time);
    robotIrRing.UpdateData();
    motorsRobot.InitializeMotors();

    pinMode(ConstantsStricker::kAnalogReadPin, INPUT);
    //pinMode(ConstantsStricker::trigPin, OUTPUT); Cuando se incluya ultrasónico
    //pinMode(ConstantsStricker::echoPin, INPUT);
} //está sos ver si se puede quitar 
//-------------------------------------IR Ring
//Search and move according to the position of the ball
void stateMachineStricker::searchBall(){
    Serial.println("iniciando searchBall function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    unsigned long currentTime = millis();
    robotIrRing.Init(&currentTime);
    robotIrRing.SetOffset(0.0);
    translation_angle = 0;
    adjust_angle = translation_angle - 90;
    double speed_w = robotPid.Calculate(setpoint, yaw);
    if(speed_w != 0){
        motorsRobot.StopAllMotors();
        motorsRobot.MoveBaseWithImu(0, 0, speed_w);
    }

    robotIrRing.UpdateData();
    double angle=robotIrRing.GetAngle();
    double newAngle=(angle<0 ? 360+angle:angle);
    //newAngle=360-newAngle;
    double strength=robotIrRing.GetStrength();

    // Added this condition to have control of the robot during the test
    if (newAngle >= 45 && newAngle <= 315) {
        motorsRobot.MoveBaseWithImu(newAngle,150,0);
        Serial.println("fuera de rango");
    }
    else if (newAngle < 45 || newAngle > 315) {
        motorsRobot.StopAllMotors();
        Serial.println("dentro de rango");
    }
    Serial.print("Angle: ");
    Serial.print(newAngle);
    Serial.print("\tradio: ");
    Serial.println(strength);
    delay(50);
}
void stateMachineStricker::goToGoal(){
    Serial.println("atack function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    unsigned long currentTime = millis();
    static unsigned long lastMoveTime=0;
    robotIrRing.Init(&currentTime);
    Pixy.updateData();
    int numberObjects=Pixy.numBlocks();
    int bestBlock=-1;
    int maxWidth=0;
    for(int i=0;i<numberObjects;i++){
        if (Pixy.getHeight(i)>heightGoalMax){
        int width=Pixy.getWidth(i);
        if(width>maxWidth){
            maxWidth=width;
            bestBlock=i;
        }
    }
}
    float x= Pixy.getX(bestBlock);
    int setpoint= Pixy.angleGoal(x);
    double speed_w = robotPid.Calculate(setpoint, yaw);
    if(millis()-lastMoveTime>1000){
            motorsRobot.MoveBaseWithImu(setpoint,ConstantsStricker::kVelocityAtack, speed_w);
            lastMoveTime=millis();
    }
    if (millis()-lastMoveTime>2000){
        motorsRobot.StopAllMotors();

}
}

void stateMachineStricker::avoidLine(int angle){
    Serial.println("avoid line function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    double speed_w = robotPid.Calculate(0, yaw);
    unsigned long currentTime = millis();
    while(millis()-currentTime<1000){
        motorsRobot.MoveBaseWithImu(angle,ConstantsStricker::kVelocityCorrectionLine, speed_w);
    }
    motorsRobot.StopAllMotors();

}