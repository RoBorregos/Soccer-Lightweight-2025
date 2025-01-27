
#ifndef ARDUINO_MOTORS_H
#define ARDUINO_MOTORS_H

#include "Arduino.h"
#include "motor.h"


class Motors  
{
	private:

	public:
		motor motor1;
		motor motor2;
		motor motor3;
		motor motor4;
		Motors(int pin1_1, int pin2_2, int speed_1, 
		int pin1_2, int pin2_2, int speed_2,
		int pin1_3, int pin2_3, int speed_3,
		int pin1_4, int pin2_4, int speed_4),;
		

};
#endif
