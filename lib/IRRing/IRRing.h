
#ifndef ARDUINO_IRRING_H
#define ARDUINO_IRRING_H
#include <Arduino.h>

class IRRing  
{
	private:
	double angle;
	double strength;
	double offset;
	unsigned long& current_time;
	unsigned long last_time=0;

	public:
	IRRing();
	void init(unsigned long& current_time);
	void UpdateData();
	void SetOffset(double offset);
	double GetAngle();
	double GetStrength();

};
#endif
