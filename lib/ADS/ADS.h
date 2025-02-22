
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
	int umbralLinea=3683;
	int umbralCampo=4159;

	public:
	ADS();
	ADS( Adafruit_ADS1115 _Right, Adafruit_ADS1115 _Left, Adafruit_ADS1115 _Back);

	//Inicializa los sensores de IR
	bool initializeAdafruit();
	//Promedio de los valores
	double getAverageRight();
	double getAverageLeft();
	double getAverageBack();
	//Obtener el valor de los sensores
	int16_t getIndividualValueRight(int channel);
	int16_t getIndividualValueLeft(int channel);
	int16_t getIndividualValueBack(int channel);
	//Detectar linea
	bool detectLineRight();
	bool detectLineLeft();
	bool detectLineBack();
	//Ajustar movimiento
	void moveComplementary( bool moveRight, bool moveLeft, bool moveBack);

};
#endif

