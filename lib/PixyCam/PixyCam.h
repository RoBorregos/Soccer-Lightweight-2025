
#ifndef ARDUINO_PIXYCAM_H
#define ARDUINO_PIXYCAM_H
#include <Arduino.h>
#include <Wire.h>
#include <Pixy2I2C.h>

struct GoalData{
	uint16_t signature;
	int x,y,width,height;
}

class PixyCam 
{
	private:
	Pixy2I2C pixy_;

	public:
	PixyCam();
	void Init();
	std::vector<GoalData> DetectGoals();
};

#endif 
