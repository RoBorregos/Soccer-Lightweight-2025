#include "stateMachineStricker.h"

//-------------------------------------IR Ring
//Search and move according to the position of the ball
void stateMachineStricker::searchBall(){
    int change= getCorrectionsImu();
    robotIrRing.UpdateData();
    double angle=robotIrRing.GetAngle();
    double str=robotIrRing.GetStrength();
    if(str==0){
        motorsRobot.StopAllMotors();
        return;
    }else if(str>80 && abs(angle)<=90){
        motorsRobot.upper_right_motor_.MoveForward();
        motorsRobot.upper_left_motor_.MoveForward();
        motorsRobot.lower_right_motor_.MoveForward();
        motorsRobot.lower_left_motor_.MoveForward();

        motorsRobot.upper_right_motor_.SetSpeed(motorsRobot.upper_right_motor_.GetSpeed(), 50);
        motorsRobot.upper_left_motor_.SetSpeed(motorsRobot.upper_left_motor_.GetSpeed(), 50);
        motorsRobot.lower_right_motor_.SetSpeed(motorsRobot.lower_right_motor_.GetSpeed(), 50);
        motorsRobot.lower_left_motor_.SetSpeed(motorsRobot.lower_left_motor_.GetSpeed(), 50);

    }else{
        motorsRobot.StopAllMotors();
    }

    int result= -1000;

        if (abs(angle)<=20){
            result=0;
        }else if (abs(angle)<=50){
            result=(angle>0)?90:-90;
        }else if (abs(angle)<=75){
            result=(angle>0)?120:-120;
        }else if (abs(angle)<=90){
            result=(angle>0)?135:-135;
        }else if (abs(angle)<=140){
            result=180;
        }else{
            result=(angle>0)?-140:140;
        }

        if (str<30){
            if (result<=90)
            result= result*0.7;
        }else if (str<50){
            if (result<=90)
            result= result*0.7;
        }

        if (result== -1000){
            motorsRobot.StopAllMotors();
        }else{
            motorsRobot.MoveBaseWithImu(result-gyro.GetYaw(),ConstantsStricker::velocities, change);
            
        }
        if (angle>0){
            last=1;
        }else{
            last=-1;
        }
    }
//Goalposts
//Incluir si se agrega ultrasonico o IR
void stateMachineStricker::gol(int xPosition, int y1){
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
}

void stateMachineStricker::goOutOfLine(int angleC){
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
}
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
void stateMachineStricker::updateGoalData(){
    Pixy.DetectGoals();
}
void stateMachineStricker::startObjects(){
    Serial3.begin(115200);
    Serial3.setTimeout(100);
    Serial.begin(9600);
    Serial2.begin(9600);
    Serial2.setTimeout(100);

    robotPid.setKp(0.2);
    robotPid.setMinToMove(40);
    gyro.InitializeBNO();
    unsigned long current_time = millis();
    robotIrRing.Init(&current_time);
    robotIrRing.UpdateData();
    motorsRobot.InitializeMotors();

    pinMode(ConstantsStricker::analogReadPin, INPUT);
    //pinMode(ConstantsStricker::trigPin, OUTPUT); Cuando se incluya ultrasónico
    //pinMode(ConstantsStricker::echoPin, INPUT);
    if (ConstantsStricker::velocities>120){
        robotPid.setKp(0.09);
        robotPid.setAngle(120);
    }

}
bool stateMachineStricker::detectLeftLine(){
    return robotPthototransistors.CheckPhotoLeft();
}
bool stateMachineStricker::detectRightLine(){
    return robotPthototransistors.CheckPhotoRight();
}
bool stateMachineStricker::detectFrontLine(){
    return robotPthototransistors.CheckPhotoFront();
}
