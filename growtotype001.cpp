#include <DHT.h>			// Temp and humidity sensor library
#include <Wire.h>			// RTC library
#include <LiquidCrystal.h>	// LCD library
#include <SD.h>				// SD card library
#include <SPI.h>			// SPI Communication library

#define DHTPIN			// STILL NEED TO ADD PIN NUMBER
#define DHTTYPE DHT11	// Sets the DHT sensor type
#define LIGHTRELAY		// STILL NEED TO ADD PIN NUMBER
#define PUMPRELAY		// STILL NEED TO ADD PIN NUMBER

const int rs=4,en=5,d4=7,d5=8,d6=9,d7=10;	// DOUBLE CHECK THESE CONNECTIONS
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);		// Initializes LCD screen
DHT dht (DHTPIN, DHTTYPE);					// Initializes DHT sensor

	void setup()
	{
		pinMode(DHTPIN, INPUT);
		Serial.begin(9600);
		Wire.begin();
		lcd.begin(16,2);
		lcd.clear();
	}

void loop()
{
	
}