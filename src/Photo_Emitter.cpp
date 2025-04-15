#include <Arduino.h>
#include "Photo.h"
#include "constants.h"

Photo photo;

void setup(){
    Serial.begin(9600);
}

void loop() {
    // Leer los datos de los fototransistores usando CheckPhotosOnField
    PhotoData left_data = photo.CheckPhotosOnField(Side::Left);
    PhotoData right_data = photo.CheckPhotosOnField(Side::Right);
    PhotoData front_data = photo.CheckPhotosOnField(Side::Front);

    // Enviar los datos a través de UART
    Serial.print(left_data.is_on_line);
    Serial.print(",");
    Serial.print(left_data.correction_degree);
    Serial.print(",");
    Serial.print(right_data.is_on_line);
    Serial.print(",");
    Serial.print(right_data.correction_degree);
    Serial.print(",");
    Serial.print(front_data.is_on_line);
    Serial.print(",");
    Serial.println(front_data.correction_degree);
}