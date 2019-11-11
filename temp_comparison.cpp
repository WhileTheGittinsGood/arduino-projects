/*
	This program compares the analog output of a thermistor voltage divider and a DHT11
	The program was written to verify accurate temperature readings by taking more
*/

//include DHT library
#include "DHT.h"
//connect signal pin on DHT11 to D2 on the arduino
#define DHTPIN 2
//connect Vout of thermistor voltage divider to A0 (10k reistor to 5v, thermistor to GND)
#define THERMISTORPIN A0
//approximate resistance at nominal temperature in degrees C
#define THERMISTORNOMINAL 10000
//temperature for nominal resistance
#define TEMPERTURENOMINAL 25
//number of samples taken to average
#define NUMSAMPLES 5
//beta coefficient of thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
//sets value of R2 in series with thermistor
#define SERIESRESISTOR 10000
//type of DHT sensor used is DHT11
#define DHTTYPE DHT11

//initializes the DHT11
DHT dht(DHTPIN, DHTTYPE);

//initializes floats used in resistance to temperature equation and DHT11 temp variables
float steinhart, average, thermResist, celcius, fahrenheit, c, f;

//placeholder for our analog sample counter
uint8_t i;
uint16_t samples[NUMSAMPLES];

	void setup()
	{
		//begins serial communication
		Serial.begin(9600);
		Serial.println("Analog thermistor vs DHT11 comparison");
		//begeins DHT11 readings
		dht.begin();

		delay(3000);
	}

void loop()
{
	//takes samples as defined by NUMSAMPLES from THERMISTORPIN
	for(i = 0; i < NUMSAMPLES; i++)
	{
		samples[i] = analogRead (THERMISTORPIN);
		delay(10);
	}
	//averages the results of the samples
	
	average = 0;
	for(i = 0; i < NUMSAMPLES; i++)
	{
		average += samples[i];
	}
	average /= NUMSAMPLES;
	
	//converts average analog reading from thermistor to resistance
	thermResist = 1023 / average - 1;
	thermResist = SERIESRESISTOR / thermResist;
	
	//converts resistance of thermistor to degress celcius using Steinhart-Hart equation
	steinhart = thermResist / THERMISTORNOMINAL;
	steinhart = log(steinhart);
	steinhart /= BCOEFFICIENT;
	steinhart += 1.0 / (TEMPERTURENOMINAL  + 273);
	steinhart = 1.0/ steinhart;
	steinhart -= 273.15;
	
	//sets degrees celcius and fahrenheit for thermistor readout
	celcius = steinhart;
	fahrenheit = (celcius * 9) / 5 + 32;
	
	//sets degrees celcius and fahrenheit for DHT11 readout
	c = dht.readTemperature();
	f = dht.readTemperature(true);
	
	//prints results of both readouts to the serial monitor
	Serial.print("Thermistor (C/F): ");
	Serial.print(celcius);
	Serial.print("/");
	Serial.println(fahrenheit);
	Serial.print("DHT11:            ");
	Serial.print(c);
	Serial.print("/");
	Serial.println(f);
	Serial.println(" ");

	delay(1000);
}