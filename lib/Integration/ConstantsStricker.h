#ifndef ARDUINO_CONSTANTSSTRICKER_H
#define ARDUINO_CONSTANTSSTRICKER_H
#include <Arduino.h>

class ConstantsStricker  
{
	

	public:

		ConstantsStricker();
		static const int velocities = 110;
    	static const int velMin = 80;
    	static const int velMax = 150;
		static const int analogReadPin = A4;
		//static const int trigPin = 36; para ultrasónico
		//static const int echoPin = 38;
	
		enum stateMachine{
			ballDetected,
			line,
			searchBall,
			scoreGoal,
			nothing,
		};
		enum sides{
			yellow=0,
			blue=1,
		};
	};
#endif
