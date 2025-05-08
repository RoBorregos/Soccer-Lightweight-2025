#include <Arduino.h>

void setup() {
    Serial.begin(9600);    // Para ver datos en el monitor serie
    Serial2.begin(9600);   // Comunicación UART con el Uno
  }
  
  void loop() {
    if (Serial1.available()) {
      String mensaje = Serial1.readStringUntil('\n');
      Serial.print("Recibido: ");
      Serial.println(mensaje);
    }
  }