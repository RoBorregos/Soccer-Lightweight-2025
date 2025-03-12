#include "motors.h"
#include "BNO.h"
#include "PID.h"
#include "ADS.h"

unsigned long start_millis;
unsigned long current_millis;
int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;

unsigned long motor_start_millis = 0;
unsigned long motor_photo_correction = 90;

int photo_value_left1;
int photo_value_left2;
int photo_value_right;
int photo_value_back1;
int photo_value_back2;



Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

Bno bno;

PID pid(1.5, 0.00735, 45, 200); // parametros para correccion angular (1.5, 0.00735, 45, 200)
ADS ads;

void setup() {
    Serial.begin(9600);
    analogReadResolution(12);
    //ads.initializeAds();
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");

    bno.bno_begin();

    start_millis = millis();

}

void loop() {
 //----------------------------Correction with PID--------------------------------/
    
 bno.getEuler();
 double yaw = bno.getYaw();    
 translation_angle = 0;
 adjust_angle = translation_angle - 90;
 double speed_w = pid.Calculate(setpoint, yaw);
 // motors.MoveMotorsImu(setpoint, 150, 0);

 if(speed_w != 0){
     motors.StopMotors();
     motors.MoveMotorsImu(0, 0, speed_w);
 }
//----------------------------Photoresistors detection--------------------------------/
photo_value_left1 = analogRead(A2); //Izquierda > 2000
photo_value_left2 = analogRead(A7); //Izquierda > 2000
photo_value_right = analogRead(A3); //Derecha > 2500
photo_value_back1 = analogRead(A10); //Back > 1300
photo_value_back2 = analogRead(A11); //Back > 1300

//unsigned long current_millis = millis();

Serial.print("Photoresistor left1: ");
Serial.println(photo_value_left1);
Serial.print("Photoresistor left2: ");
Serial.println(photo_value_left2);
Serial.print("Photoresistor right: ");
Serial.println(photo_value_right);

if (photo_value_left1 > 2000 || photo_value_left2 > 2000)
{
    Serial.println("Detectó linea izquierda"); 
    motors.MoveMotorsImu(90,255,0);
    motor_start_millis = current_millis;
    if (current_millis - motor_start_millis >= motor_photo_correction)
    {
    motors.StopMotors();
    }
}

if (photo_value_right > 2500)
{
    Serial.println("Detectó linea derecha"); 
    motors.MoveMotorsImu(270,255,0);
    motor_start_millis = current_millis;
    if (current_millis - motor_start_millis >= motor_photo_correction)
    {
    motors.StopMotors();
    }
}
//if (photo_value_back1 > 1300 || photo_value_back2 > 1300)
//{
    // motors.MoveMotorsImu(0,200,0);
//}

/*
    //----------------------------Ball detection--------------------------------/
    
    ball_seen_openmv = digitalRead(ball_pin);
    if (ball_seen_openmv == 1)
    {
        motors.StopMotors();
        goal_angle = 0;
    }
    else
    {
        goal_angle = 90;
    }
    */
    //----------------------------Motor movement--------------------------------/
    /*
    if (ball_seen_openmv == 1)
    {
        motors.StopMotors();
    }
    else
    {
        motors.MoveMotorsImu(0, 0, 0);
    }
    */
    //----------------------------Motor movement with PID--------------------------------/

   /*
        on_motors = digitalRead(on_pin);
        if (on_motors == 1)
        {
            bno.GetEuler();
            ball_angle = bno.GetBallAngle();
            speed_w = pid.Calculate(rotation_angle, bno.GetYaw);
    
            if (speed_w != 0)
            {
              //----------------------- Photoresistors detection ---------------------------//
        
              //------------------ Angle normalization ------------------//
              if (ball_angle < 180)
              {
                ball_angle_180 = -ball_angle;
              }
              else if (ball_angle > 180)
              {
                ball_angle_180 = 360 - ball_angle;
              }
              ball_angle_180 = ball_angle_180 * (-1);
        
              if (goal_angle < 180)
              {
                goal_angle_180 = -goal_angle;
                shoot_angle = 45;
              }
              else if (goal_angle > 180)
              {
                goal_angle_180 = 360 - goal_angle;
                shoot_angle = -45;
              }
              goal_angle_180 = goal_angle_180 * (-1);
        
              Serial.print("goal angle: ");
              Serial.println(goal_angle_180);
            }
        }else if (goal_angle==0 && !ball_seen_openmv)
        {motors.MoveMotorsImu(0, 0, speed_w);}
        else{
            motors.StopMotors();
        }
    }
*/
   

    //----------------------------Motor movement funcrions--------------------------------/

    /*
    Serial.println("Mover hacia adelante");
    motors.SetAllSpeeds(90);
    motors.MoveForward();
    
    Serial.println("Mover hacia atrás");
    motors.MoveBackward();
    delay(2000);

    Serial.println("Girar a la izquierda");
    motors.MoveLeft();
    delay(2000);

    Serial.println("Girar a la derecha");
    motors.MoveRight();
    delay(2000);

    Serial.println("Girar en círculos");
    for (int angle = 0; angle < 360; angle += 45) {  // Gira en múltiples ángulos
        motors.MoveMotors(angle, 255);
        delay(500);
    }

    Serial.println("Detener motores");
    motors.StopMotors();
    delay(3000);  
    */
}

