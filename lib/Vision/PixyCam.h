#ifndef ARDUINO_PIXYCAM_H
#define ARDUINO_PIXYCAM_H
#include <Arduino.h>
#include <Pixy2.h>


struct TargetGoalData{
	uint8_t signature;
	int x;
	int y;
	int width;
	int height;
	float cameraAngle;
};

class PixyCam 

{
private:
	Pixy2 pixy_;
	uint8_t block;
	uint32_t communicationMode;

    static const int kMovingAverageSize = 10; // Tamaño del array circular
    float angle_values[kMovingAverageSize] = {0}; // Array circular 
	int width_values[kMovingAverageSize] = {0}; // Array circular
    uint8_t angle_index = 0; // Índice actual
	uint8_t width_index = 0; // Índice actual

public:
	PixyCam();
	void Init(uint32_t communicationMode);
	void updateData();
	uint8_t numBlocks();
	uint8_t getSignature();
	int getX(uint8_t block);
	int getY(uint8_t block);
	int getWidth(uint8_t block);
	int getHeight(uint8_t block);
	float getGoalAngle(int x);
	TargetGoalData getTargetGoalData(uint8_t numberObjects, uint8_t targetSignature);


};

#endif 