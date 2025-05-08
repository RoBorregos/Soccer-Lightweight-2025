#include <Arduino.h>

void setup() {
    Serial.begin(9600); // Serial hardware del Uno
  }
  
  void loop() {
    Serial.println("Hola desde Arduino Uno!");
    delay(1000);
  }