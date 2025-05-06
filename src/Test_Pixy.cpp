#include <Arduino.h>
#include "PixyCam.h"


PixyCam pixyCamRobot;
const uint32_t kCommunicationMode = SPI_MODE0; // UART communication mode
int targetSignature = 2; // Signature for yellow goal
TargetGoalData targetGoalData = {0, 0, 0, 0, 0, 0}; // Estructura para almacenar los datos del objetivo
void setup()
{
    Serial.begin(9600);
    pixyCamRobot.Init(kCommunicationMode);
}
void loop(){
    pixyCamRobot.updateData();
    targetGoalData = pixyCamRobot.getTargetGoalData(pixyCamRobot.numBlocks(), targetSignature); // 1 is the signature for yellow goal
    Serial.println("Weidth:");
    Serial.println(targetGoalData.width);
    Serial.println("Signature:");
    Serial.println(targetGoalData.signature);
    Serial.println("X:");
    Serial.println(targetGoalData.x);
    Serial.println("Y:");
    Serial.println(targetGoalData.y);
    Serial.println("Height:");
    Serial.println(targetGoalData.height);

}
/*#include <Arduino.h>
#include "PixyCam.h"
#include <Pixy2UART.h>
PixyCam pixyCamRobot;
void setup() {
    Serial.begin(9600);
    Serial3.begin(19200);
    pixyCamRobot.Init();
}
void loop() {
    pixyCamRobot.updateData();  // Actualiza la información de los bloques detectados
    int blocks = pixyCamRobot.numBlocks();  // Obtiene el número de bloques detectados
    Serial.println("Get blocks:");
    Serial.println(blocks);
    // Si hay bloques detectados
    if (blocks > 0) {
        // Recorre todos los bloques detectados
        for (int i = 0; i < blocks; i++) {
            int signature = pixyCamRobot.getSignature();  // Obtiene la firma de cada bloque
            // Verifica si la firma es la 1 (amarilla) o la 2 (azul)
            if (signature == 1) {
                Serial.println("Yellow Goal (Signature 1):");
                Serial.print("X: ");
                Serial.println(pixyCamRobot.getX(i));
                Serial.print("Y: ");
                Serial.println(pixyCamRobot.getY(i));
                Serial.print("Height: ");
                Serial.println(pixyCamRobot.getHeight(i));
                Serial.print("Width: ");
                Serial.println(pixyCamRobot.getWidth(i));
            }
            else if (signature == 2) {
                Serial.println("Blue Goal (Signature 2):");
                Serial.print("X: ");
                Serial.println(pixyCamRobot.getX(i));
                Serial.print("Y: ");
                Serial.println(pixyCamRobot.getY(i));
                Serial.print("Height: ");
                Serial.println(pixyCamRobot.getHeight(i));
                Serial.print("Width: ");
                Serial.println(pixyCamRobot.getWidth(i));
            }
        }
    }
    else {
        Serial.println("No blocks detected.");
    }
    delay(500);  // Pausa antes de la siguiente lectura
}*/