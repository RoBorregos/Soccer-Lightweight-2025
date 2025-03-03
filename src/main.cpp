#include "motors.h"
#include "BNO.h"
#include "PID.h"
#include "ADS.h"

unsigned long start_millis;
unsigned long current_millis;
int setpoint = 0;
int translation_angle = 0;
int adjust_angle = 0;


Motors motors(
    MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, 
    MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, 
    MOTOR3_PWM, MOTOR3_IN1, MOTOR3_IN2, 
    MOTOR4_PWM, MOTOR4_IN1, MOTOR4_IN2
);

Bno bno;

PID pid(1.5, 0.0, 45, 200); // parametros para correccion angular (1.5, 0.00735, 45, 200)
ADS ads;

void setup() {
    Serial.begin(9600);
    ads.initializeAds();
    motors.InitializeMotors();  // Inicializar los motores
    Serial.println("Prueba de motores iniciada.");

    bno.bno_begin();

    start_millis = millis();

}

void loop() {
int photoValue = analogRead(A2);
int photoValue1 = analogRead(A7);
int photoValue2 = analogRead(A3); // no
int photoValue3 = analogRead(A12);
int photoValue4 = analogRead(A13);
int photoValue5 = analogRead(A14);
int analogPin1 = analogRead(A8);
int analogPin2 = analogRead(A9);
int photo_value5 = analogRead(A15);
int photo_value6 = analogRead(A17);
int photo_value7 = analogRead(A6);

Serial.println(photoValue);
Serial.println(photoValue1);
Serial.println(photoValue2);
Serial.println(photoValue3);
Serial.println(photoValue4);
Serial.println(photoValue5);
Serial.println(analogPin1);
Serial.println(analogPin2);
Serial.println(photo_value5);
Serial.println(photo_value6);
Serial.println(photo_value7);


/*
bool LeftLine = ads.detectLineLeft();
bool RightLine = ads.detectLineRight();
bool BackLine = ads.detectLineBack();

ads.moveComplementary(RightLine, LeftLine, BackLine);

    //----------------------------ADS detection--------------------------------/
    /*
    bool AdsLeft = ads.detectLineLeft();
    bool AdsRight = ads.detectLineRight();
    bool AdsBack = ads.detectLineBack();
    */
    //----------------------------ADS movement--------------------------------/

/*
if(AdsLeft== true){
  motors.MoveRight();
}
if(AdsRight== true){
  motors.MoveLeft();
}
if(AdsBack== true){
  motors.MoveForward();
}

    //----------------------------Ball detection--------------------------------/
    /*
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

    //----------------------------Linear correction with PID--------------------------------/
    /*
    bno.getEuler();
    double yaw = bno.getYaw();

    double output = pid.Calculate(setpoint, yaw);
    Serial.println(output);

    motors.MoveMotorsImu(setpoint, 150, output);

    //----------------------------Angular correction with PID--------------------------------/
    /*
    translation_angle = 0;
    adjust_angle = translation_angle - 90;
    double speed_w = pid.Calculate(setpoint, yaw);
    if(speed_w != 0){
    motors.MoveMotorsImu(0, 0, speed_w);
    Serial.print(speed_w);
     Serial.print("angle");
     Serial.println(yaw);
    }

    //----------------------------Motor movement funcrions--------------------------------/

    
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

