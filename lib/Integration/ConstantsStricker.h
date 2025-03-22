#ifndef ARDUINO_CONSTANTSSTRICKER_H
#define ARDUINO_CONSTANTSSTRICKER_H
#include <Arduino.h>

class ConstantsStricker  
{
	

	public:

		ConstantsStricker();
		static const int velocityCorrectionLine = 255;
    	static const int velocitySearchBall = 150;
    	static const int velocityAtack=150;
		static const int analogReadPin = A4;
		//static const int trigPin = 36; para ultrasónico
		//static const int echoPin = 38;
	
		enum stateMachine{
			/*ballDetected,*/ //por el momento no es necesario 
			line,
			searchBall,
			scoreGoal,
			nothing
		};
		enum sides{ //son necesarias?? 
			yellow=0,
			blue=1,
		};
	};
#endif
