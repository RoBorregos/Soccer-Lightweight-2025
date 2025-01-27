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
void Motors:: MoveForward(){

}