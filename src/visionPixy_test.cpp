#include <Arduino.h>
#include "PixyCam.h"
#include <Pixy2UART.h>

PixyCam pixyCamRobot;
void setup()
{
    Serial.begin(19200);
    pixyCamRobot.Init();
    pixyCamRobot.updateData();
}
void loop(){
    Serial.println("Get blocks:");
    Serial.println(pixyCamRobot.numBlocks());
    Serial.println("X:");
    Serial.println(pixyCamRobot.getX(1));
    Serial.println("Y:");
    Serial.println(pixyCamRobot.getY(1));
    Serial.println("Height:");
    Serial.println(pixyCamRobot.getHeight(1));
    Serial.println("Signature:");
    Serial.println(pixyCamRobot.getSignature());
    Serial.println("Weidth:");
    Serial.println(pixyCamRobot.getWidth(1));
}