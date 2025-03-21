#include "Photo.h"
#include "Arduino.h"

int PhotoLeft;
int PhotoRight;
bool PhotoLeftOnLine;
bool PhotoRightOnLine;

Photo photo;

void setup() {
    Serial.begin(9600);
    analogReadResolution(12);
}

void loop() {
    Serial.println("Reading photos");
    PhotoLeft = photo.ReadPhotoLeft();
    PhotoRight = photo.ReadPhotoRight();
    Serial.print("Photo Left: ");
    Serial.print(PhotoLeft);
    Serial.print("   Photo Right: ");
    Serial.println(PhotoRight);
    delay(1000);

    Serial.println("Checking photos");
    PhotoLeftOnLine = photo.CheckPhotoLeft();
    PhotoRightOnLine = photo.CheckPhotoRight();
    Serial.print("Photo Left on line: ");
    Serial.print(PhotoLeftOnLine);
    Serial.print("   Photo Right on line: ");
    Serial.println(PhotoRightOnLine);
    delay(1000);
}