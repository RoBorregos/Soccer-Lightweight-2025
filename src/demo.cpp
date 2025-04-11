#include "Photo.h"
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "BNO.h"
#include "PID.h"
#include "IRRing.h"

int PhotoLeft;
int PhotoRight;
int PhotoFront;
bool PhotoLeftOnLine;
bool PhotoRightOnLine;
bool PhotoFrontOnLine;
int currentTime;
unsigned long motor_start_millis = 0;
unsigned long motor_photo_correction = 200;
int setpoint = 0;
bool is_correcting_line = false;

Photo photo;
IRRing irring;
Bno bno;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);


void setup() {
    Serial.begin(9600);
    unsigned long currentTime = millis();
    motors.InitializeMotors();
    bno.InitializeBNO();
    irring.init(&currentTime);

}

void loop() {
    currentTime = millis();
    //---------------------------------Reading data for PID and IR---------------------------------
    irring.UpdateData();
    double ballAngle = irring.GetAngle(1.1);
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    // motors.MoveOmnidirectionalBase(0, 0.55, 0);
    // Serial.print("Angle: ");
    // Serial.println(ballAngle);
    // Serial.print("Yaw: ");
    // Serial.print(yaw);
    // Serial.print("   PID: ");
    // Serial.println(speed_w);

    //-------------------------------Initial robot movement instruction-----------------------------
    if (!is_correcting_line) {
        motors.MoveOmnidirectionalBase(90, 0.55, 0); // cahnge angol to ball Angle
    //-----------------------------------------------PID correction--------------------------------
        // if (speed_w > 0.1 || speed_w < -0.1) {
        //     motors.StopAllMotors();
        //     motors.MoveOmnidirectionalBase(0, 0, speed_w);
        // }
    }

    //---------------------------------Reading and checking phototransistors--------------------------------
    Serial.println("Reading photos");
    PhotoLeft = photo.ReadPhotoLeft();
    PhotoRight = photo.ReadPhotoRight();
    PhotoFront = photo.ReadPhotoFront();
    Serial.print("Photo Left: ");
    Serial.println(PhotoLeft);
    // Serial.print("   Photo Right: ");
    // Serial.println(PhotoRight);
    // Serial.print("   Photo Front: ");
    // Serial.println(PhotoFront);


    Serial.println("Checking photos");
    PhotoLeftOnLine = photo.CheckPhotoLeft();
    PhotoRightOnLine = photo.CheckPhotoRight();
    PhotoFrontOnLine = photo.CheckPhotoFront();
    Serial.print("Photo Left on line: ");
    Serial.println(PhotoLeftOnLine);
    // Serial.print("   Photo Right on line: ");
    // Serial.println(PhotoRightOnLine);
    // Serial.print("   Photo Front on line: ");
    // Serial.println(PhotoFrontOnLine);

    //-------------------------------------------------Line correction--------------------------------
    if (!is_correcting_line && PhotoLeftOnLine) {
        is_correcting_line = true; // Activar el estado de corrección
        motor_start_millis = currentTime; // Registrar el tiempo de inicio
        motors.MoveOmnidirectionalBase(-90, 1, 0); // Moverse a la derecha
    }

    if (!is_correcting_line && PhotoRightOnLine) {
        is_correcting_line = true; // Activar el estado de corrección
        motor_start_millis = currentTime; // Registrar el tiempo de inicio
        motors.MoveOmnidirectionalBase(90, 1, 0); // Moverse a la derecha
    }

    // if (!is_correcting_line && PhotoFrontOnLine) {
    //     is_correcting_line = true; // Activar el estado de corrección
    //     motor_start_millis = currentTime; // Registrar el tiempo de inicio
    //     motors.MoveOmnidirectionalBase(180, 1, 0); // Moverse a la derecha
    //     // Serial.println("Photo Left true, starting correction...");
    // }

    // Si está corrigiendo, verificar si ya pasó el tiempo de corrección
    if (is_correcting_line) {
        if (currentTime - motor_start_millis >= motor_photo_correction) {
            motors.StopAllMotors(); // Detener motores después del tiempo de corrección
            is_correcting_line = false; // Desactivar el estado de corrección
        }
    } 
    

    // if (PhotoLeftOnLine) {
    //     motors.StopAllMotors();
    //     Serial.println("Photo Left true");
    //     motor_start_millis = currentTime;
    //     motors.MoveOmnidirectionalBase(-90, 1, 0);
    //     if (currentTime - motor_start_millis >= motor_photo_correction)
    //     {
    //     motors.StopAllMotors();
    //     }
    // }

    // if (PhotoRightOnLine) {
    //     Serial.println("Photo Right on line");
    //     motor_start_millis = currentTime;
    //     motors.MoveOmnidirectionalBase(90, 1, 0);
    //     if (currentTime - motor_start_millis >= motor_photo_correction)
    //     {
    //     motors.StopAllMotors();
    //     }
    // }

    // if (PhotoFrontOnLine) {
    //     Serial.println("Photo Front on line");
    //     motor_start_millis = currentTime;
    //     motors.MoveOmnidirectionalBase(180, 1, 0);
    //     if (currentTime - motor_start_millis >= motor_photo_correction)
    //     {
    //     motors.StopAllMotors();
    //     }
    // }
}