#include "motors.h"
#include<Wire.h>
#include "Bno.h"
#include "PID.h"
#include <Servo.h>

#include <PID.h>

// Definir PID con parámetros (ajústalos según tu caso)
PID pid(6.0, 0.000, 30, 200);

double speed_w = 0;
double target_angle = 0;
float ball_angle_180 = 0;
float goal_angle_180 = 0;
float ball_angle = 0;
float ball_distance = 0;
float goal_angle = 0;

double adjust_angle = 0;
double translation_angle = 0;
int rotation_angle = 0;

double last_time = 0;
double current_time = 0;
double last_ball_angle = 0;
int on_pin = 7;
int on_motors = 0;

const int delay_time = 3000;
const int min_speed = 1000;
const int mid_speed = 1500;
const int max_speed = 2000;
int shoot_angle = 0;
unsigned long start_millis;

BNO bno;
Servo esc;
/*PID pid(0.6, 0.00735, 45, 200);*/
Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

void setup() 
    {
    Serial.begin(9600);
    bno.Bno_begin();
    pinMode(on_pin, INPUT);
    analogReadResolution(12);
    motors.InitializeMotors();
    delay(delay_time);
    start_millis = millis();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");}
    double radiansToDegrees(double radians)
    {
      return radians * (180.0 / M_PI);
    }
    
    void timeLoop(long int startMillis, long int interval)
    {
      while (millis() - startMillis < interval)
      {
      }
}

void loop() {
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
    /*else
    {
        motors.StopMotors();
    }*/
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
   
    



