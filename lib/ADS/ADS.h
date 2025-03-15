
#ifndef ARDUINO_ADS_H
#define ARDUINO_ADS_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

class ADS  {
	private:
	Adafruit_ADS1115 right;
	Adafruit_ADS1115 left;
	Adafruit_ADS1115 back;
	int threshold_line=3683;
	int threshold_field=4159;

	public:
	ADS();
	ADS( Adafruit_ADS1115 _Right, Adafruit_ADS1115 _Left, Adafruit_ADS1115 _Back);

	//Inicializa los sensores de IR
	bool InitializeAdafruit();
	//Promedio de los valores
	double GetAverageRight();
	double GetAverageLeft();
	double GetAverageBack();
	//Obtener el valor de los sensores
	const int16_t GetIndividualValueRight(int channel);
	const int16_t GetIndividualValueLeft(int channel);
	const int16_t GetIndividualValueBack(int channel);
	//Detectar linea
	bool DetectLineRight();
	bool DetectLineLeft();
	bool DetectLineBack();
};
#endif

