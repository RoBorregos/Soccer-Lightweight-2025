
#ifndef ARDUINO_CONSTANTS_STRIKER_H
#define ARDUINO_CONSTANTS_STRIKER_H
#include <Arduino.h>


class Constants_striker  
{
	private:

	public:

		Constants_striker();
		static constexpr float kVelocityCorrectionLine = 0.7;
		static constexpr float kVelocitySearchBall= 0.56;
		static constexpr float kVelocityAtack= 0.5;
		const uint32_t kCommunicationMode = SPI_MODE0; 
		const float kBallFollowOffsetBack = 1.12;
		const float kBallFollowOffsetSide = 1.09;
		const float kBallFollowOffsetFront = 0.97;
		const int kLineCorrectionTime = 200;
		const int kTargetSignature = 1;
		const int kThresholdWidth = 30;
		enum stateMachine{
			line,
			searchBall,
			hasBall,
			scoreGoal,
			exit,
			nothing
		};


};
#endif
