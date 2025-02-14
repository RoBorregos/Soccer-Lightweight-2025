#include "Motors.h"  
#include "Arduino.h"
#include "constants.h"

Motors::Motors(int speed1, int in1_1, int in2_1, int speed2, uint8_t in1_2, int in2_2, uint8_t speed3, uint8_t in1_3, uint8_t in2_3, uint8_t speed4, uint8_t in1_4, uint8_t in2_4) 
: motor1(speed1, in1_1, in2_1),
  motor2(speed2, in1_2, in2_2),
  motor3(speed3, in1_3, in2_3),
  motor4(speed4, in1_4, in2_4)
{};
void Motors::InitializeMotors(){
    motor1.startMotors();
    motor2.startMotors();
    motor3.startMotors();
    motor4.startMotors();
};
void Motors::InitializeDriver(){
    motor1.InitializeDriver();
    motor2.InitializeDriver();
    motor3;.InitializeDriver();
    motor4.InitializeDriver();

};
void Motors::SetSpeed(int pwm, int speed){
    motor1.SetSpeed(pwm,speed);
    motor2.SetSpeed(pwm,speed);
    motor3.SetSpeed(pwm,speed);
    motor4.SetSpeed(pwm,speed);
};
void Motors::SetAllSpeeds(int speed){
    motor1.SetSpeed(MOTOR1_PWM,speed);
    motor2.SetSpeed(MOTOR1_PWM,speed);
    motor3.SetSpeed(MOTOR1_PWM,speed);
    motor4.SetSpeed(MOTOR1_PWM,speed);
};
void Motors::GetAllSpeeds(){
    Serial.print("Motor 1: ");
    Serial.println(motor1.GetSpeed_());
    Serial.print("Motor 2: ");
    Serial.println(motor2.GetSpeed_());
    Serial.print("Motor 3: ");
    Serial.println(motor3.GetSpeed_());
    Serial.print("Motor 4: ");
    Serial.println(motor4.GetSpeed_());

};
void Motors::StopMotors(){
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
};
void Motors::MoveForward(){
    motor1.forward();
    motor2.forward();
    motor3.forward();
    motor4.forward();

};
void Motors::MoveRight(){
    StopMotors();
    motor1.forward();
    motor2.backward();
    motor3.backward();
    motor4.backward();
};
void Motors::MoveLeft(){
    StopMotors();
    motor1.backward();
    motor2.forward();
    motor3.forward();
    motor4.forward();

};
void Motors::MoveBackward(){
    StopMotors();
    motor2.backward();
    motor3.forward();
};
void Motors::MoveMotor1(){
    motor1.forward();
};
void Motors::MoveMotor2(){
    motor2.forward();
};
void Motors::MoveMotor3(){
    motor3.forward();
};
void Motors::MoveMotor4(){
    motor4.forward();
};

void Motors::MoveMotors(int degree, int speed){
    float m1= cos(((45+degree)*PI/180));
    float m2= cos(((135+degree)*PI/180));
    float m3= cos(((225+degree)*PI/180));
    float m4= cos(((315+degree)*PI/180));
    int speedA=abs(int(m1*speed));
    int speedB=abs(int(m1*speed));
    int speedC=abs(int(m1*speed));
    int speedD=abs(int(m1*speed));

    analogWrite(motor1.getSpeed_(), speedA);
    analogWrite(motor2.getSpeed_(), speedB);
    analogWrite(motor3.getSpeed_(), speedC);
    analogWrite(motor4.getSpeed_(), speedD);

    if (m1 >=0){
        motor1.forward();
    }
    else{
        motor1.backward();
    }
    if (m2 >=0){
        motor2.forward();
    }
    else{
        motor2.backward();
    }
    if (m3 >=0){
        motor3.forward();
    }
    else{
        motor3.backward();
    }
    if (m4 >=0){
        motor4.forward();
    }
    else{
        motor4.backward();
    }
};
