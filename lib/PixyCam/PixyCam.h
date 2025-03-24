
#ifndef ARDUINO_PIXYCAM_H
#define ARDUINO_PIXYCAM_H
#include <Arduino.h>
#include <Wire.h>
// #include <Pixy2.h>
#include "Pixy2UART.h"


struct GoalData{
	uint16_t signature;
	int x,y,width,height;
	float angle;
};

class PixyCam 
{
	private:
	Pixy2UART pixy_;
	uint8_t block;

	public:
	PixyCam();
	void Init();
	std::vector<GoalData> DetectGoals();
	void updateData();
	float angleGoal(float x);
	int numBlocks();
	int getSignature();
	int getX(uint8_t block);
	int getY(uint8_t block);
	int getWidth(uint8_t block);
	int getHeight(uint8_t block);
	

};

#endif 