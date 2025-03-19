
#ifndef ARDUINO_PIXYCAM_H
#define ARDUINO_PIXYCAM_H
#include <Arduino.h>
#include <Wire.h>
#include <Pixy2I2C.h>


class PixyCam 
{
	private:
	Pixy2I2C pixy;

	public:
	PixyCam();
	void init();
	void detectGoals();
};

#endif 
