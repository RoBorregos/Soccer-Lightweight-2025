#include "stateMachineStricker.h"
void stateMachineStricker::startObjects(){
    Serial.begin(9600);
    this->current_time = millis();
    
    robotPid=new PID(0.2, 0.0735,45,200);
    bno= new Bno();
    robotIrRing= new IRRing();
    motorsRobot=new Motors(4, 22,23,5,24,25,6,26,27);
    Pixy= new PixyCam();
    robotPthototransistors=new Photo();

    this->robotPid->setKp(0.2);
    this->robotPid->setMinToMove(40);
    this->bno->InitializeBNO();
    this->robotIrRing->Init(&current_time);
    this->robotIrRing->UpdateData();
    this->motorsRobot->InitializeMotors();

    pinMode(ConstantsStricker::kAnalogReadPin, INPUT);
    //pinMode(ConstantsStricker::trigPin, OUTPUT); Cuando se incluya ultrasónico
    //pinMode(ConstantsStricker::echoPin, INPUT);
} //está sos ver si se puede quitar 
//-------------------------------------IR Ring
//Search and move according to the position of the ball
void stateMachineStricker::searchBall(){
    Serial.println("iniciando searchBall function");
    this->bno->GetBNOData();
    double yaw=this->bno->GetYaw();
   this ->current_time = millis();
    this->robotIrRing->Init(&this->current_time);
    this->robotIrRing->SetOffset(0.0);
    translation_angle = 0;
    adjust_angle = translation_angle - 90;
    double speed_w = this->robotPid->Calculate(setpoint, yaw);
    if(speed_w != 0){
        this->motorsRobot->StopAllMotors();
        this->motorsRobot->MoveBaseWithImu(0, 0, speed_w);
    }

    this->robotIrRing->UpdateData();
    double angle=this->robotIrRing->GetAngle();
    double newAngle=(angle<0 ? 360+angle:angle);
    //newAngle=360-newAngle;
    double strength=this->robotIrRing->GetStrength();

    // Added this condition to have control of the robot during the test
    if (newAngle >= 45 && newAngle <= 315) {
        this->motorsRobot->MoveBaseWithImu(newAngle,150,0);
        Serial.println("fuera de rango");
    }
    else if (newAngle < 45 || newAngle > 315) {
        this->motorsRobot->StopAllMotors();
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
    this->bno->GetBNOData();
    double yaw=this->bno->GetYaw();
    unsigned long currentTime = millis();
    static unsigned long lastMoveTime=0;
    this->robotIrRing->Init(&currentTime);
    this->Pixy->updateData();
    int numberObjects=this->Pixy->numBlocks();
    int bestBlock=-1;
    int maxWidth=0;
    for(int i=0;i<numberObjects;i++){
        if (this->Pixy->getHeight(i)>heightGoalMax){
        int width=this->Pixy->getWidth(i);
        if(width>maxWidth){
            maxWidth=width;
            bestBlock=i;
        }
    }
}
    float x= this->Pixy->getX(bestBlock);
    int setpoint= this->Pixy->angleGoal(x);
    double speed_w = this->robotPid->Calculate(setpoint, yaw);
    if(millis()-lastMoveTime>1000){
            this->motorsRobot->MoveBaseWithImu(setpoint,ConstantsStricker::kVelocityAtack, speed_w);
            lastMoveTime=millis();
    }
    if (millis()-lastMoveTime>2000){
        this->motorsRobot->StopAllMotors();

}
}

void stateMachineStricker::avoidLine(int angle){
    this ->bno->InitializeBNO();
    Serial.println("avoid line function");
    this->bno->GetBNOData();
    Serial.println("Getting BNO data");
    double yaw=this ->bno->GetYaw();
    Serial.println("Getting yaw");
    double speed_w = this->robotPid->Calculate(0, yaw);
    Serial.println("getting w speed");
    unsigned long currentTime = millis();
    while(millis()-currentTime<1000){
        Serial.println("Starting movement");
        Serial.print("MoveBaseWithImu - Angle: "); Serial.print(angle);
        Serial.print(" Velocity: "); Serial.print(ConstantsStricker::kVelocityCorrectionLine);
        Serial.print(" Speed_W: "); Serial.println(speed_w);
        this->motorsRobot->MoveBaseWithImu(angle,ConstantsStricker::kVelocityCorrectionLine, speed_w);
        delay(100);
    }
    this->motorsRobot->StopAllMotors();

}