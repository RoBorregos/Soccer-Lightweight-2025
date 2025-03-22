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

    pinMode(ConstantsStricker::analogReadPin, INPUT);
    //pinMode(ConstantsStricker::trigPin, OUTPUT); Cuando se incluya ultrasónico
    //pinMode(ConstantsStricker::echoPin, INPUT);
} //está sos ver si se puede quitar 
//-------------------------------------IR Ring
//Search and move according to the position of the ball
void stateMachineStricker::searchBall(){
    Serial.println("iniciando searchBall function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    Serial.begin(115200);
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
    newAngle=360-newAngle;
    double strength=robotIrRing.GetStrength();

    // Added this condition to have control of the robot during the test
    if (newAngle > 45 && newAngle < 315) {
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

//Goalposts
//Incluir si se agrega ultrasonico o IR
/*void stateMachineStricker::gol(int xPosition, int y1){
    int change= getCorrectionsImu();
    if (xPosition == -1){
        motorsRobot.MoveBaseWithImu(170*lastP,ConstantsStricker::velocities, change);
    }else if (xPosition<10 || xPosition>310){
        motorsRobot.MoveBaseWithImu(150*lastP,ConstantsStricker::velocities, change);
    }else{
        attackGoal(xPosition, y1);
    }

    if(xPosition<160){
        lastP=-1;
    }else{
        lastP=1;
    } 

}
//Attack the goal
void stateMachineStricker::attackGoal(int xPosition, int y1){
    if (y1>100){
        motorsRobot.StopAllMotors();
    }
    if (y1==-1){
        int change= getCorrectionsImu();
        motorsRobot.MoveBaseWithImu(180-gyro.GetYaw(),ConstantsStricker::velocities, change);
    }
    if(y1>110 && atack<100){
        atack = static_cast<decltype(atack)>(static_cast<int>(atack) + 1);
        int change= getCorrectionsImu();
        bool r=gyro.GetisRight();

        if (xPosition>200){
            int change= getCorrectionsImuTarget(40);
            motorsRobot.MoveBaseWithImu(0,ConstantsStricker::velocities, change);  
            Serial.println("Derecha"); 
        }else if (xPosition<120){
            int change= getCorrectionsImuTarget(-40);
            motorsRobot.MoveBaseWithImu(0,ConstantsStricker::velocities, change);
            Serial.println("Izquierda");
        }else{ //centro
            motorsRobot.MoveBaseWithImu(0-gyro.GetYaw(),ConstantsStricker::velocities, change);
            Serial.println("Adelante");
        }
    }else{
    //Moverse a la porteria
    int change= getCorrectionsImu();
    int error= xPosition-160;
    double kp_=0.375;

    if (abs(error)<25){
        Serial.println("forward");
        motorsRobot.MoveBaseWithImu(0-gyro.GetYaw(),ConstantsStricker::velocities, change);
    }else{
        int ang=(error>0)?(error*kp_):(error*kp_);
        Serial.println("Move");
        motorsRobot.MoveBaseWithImu(ang-gyro.GetYaw(),ConstantsStricker::velocities, change);
    }
    if (y1<=100){
        atack=ConstantsStricker::sides::blue;
    }

}
}
//Correction of the IMU
//Return the value of the correction of the IMU
int stateMachineStricker::getCorrectionsImu(){
    gyro.GetBNOData();
    int change= robotPid.Calculate(0,gyro.GetYaw());
    return change;
}

int stateMachineStricker::getCorrectionsImuTarget(int target){
    gyro.GetBNOData();
    robotPid.Calculate(target,gyro.GetYaw());
    int error=abs(target-gyro.GetYaw());
    bool r=((target-gyro.GetYaw())>0)?true:false;
    robotPid.SetR(r);
    if (error<=5){
        return 0;
    }
    error = 0.9 * error;
    error = min(error, 255);
    error = map(error, 0, 255, robotPid.getMinToMove(), 255);
    // Serial.println(error);
    return error;
}*/

/*void stateMachineStricker::goOutOfLine(int angleC){
    int change= getCorrectionsImu();
    unsigned long ms2=millis();

    while((millis()-ms2)<700){
        gyro.GetBNOData();
        motorsRobot.MoveBaseWithImu(angleC,ConstantsStricker::velocities, change);

    }
}

bool stateMachineStricker::hasPosesion(){
    robotIrRing.UpdateData();
    double angle=robotIrRing.GetAngle();
    double str=robotIrRing.GetStrength();
    return (str>80 && abs(angle)<=40);
}*/
/*int stateMachineStricker::detector(){
    int pulseWidth=0;
    int deltaPulseWidth=5;
    const unsigned long startTime_us= micros();
        do{
            filterAnlogo.AddValue(analogRead(ConstantsStricker::analogReadPin));
            if (filterAnlogo.GetLowPass()>600){
                pulseWidth+=deltaPulseWidth;
            }   
        }while (micros()-startTime_us<833);
        return pulseWidth;
    
}*/
//Obtain and store the data of the camera
/*void stateMachineStricker::updateGoalData(){
    Pixy.DetectGoals();
}*/

void goToGoal(){
    Serial.println("atack function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    Serial.begin(115200);
    unsigned long currentTime = millis();
    float x= Pixy.DetectGoals()[0].x;
    int setpoint= Pixy.angle(x);
    double speed_w = robotPid.Calculate(setpoint, yaw);
    motorsRobot.MoveBaseWithImu(setpoint,ConstantsStricker::velocityAtack, speed_w);


}
void avoidLine(int angle){
    Serial.println("avoid line function");
    bno.GetBNOData();
    double yaw=bno.GetYaw();
    double speed_w = robotPid.Calculate(0, yaw);
    motorsRobot.MoveBaseWithImu(angle,ConstantsStricker::velocityCorrectionLine , speed_w);

}