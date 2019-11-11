/*

	ARDUINO ENVIRONMENTAL COMFORT MONITOR

	By: Scott Kosinski

	May 2018

	This is a basic thermomter written for arduino that uses a 10k
	thermistor and a 10k resistor in series, reads the analog
	voltage in between the resistors and converts the resistance to
	temperature using the Steinhart-Hart equation.

	The user defines the optimal temperature range at setup.
	
	If the measured temperature is inside of the optimal temperature
	range as defined at setup, a green LED will light and the fan
	will be set to off state.

	If the measured temperature is outside of the optimal range
	as defined at setup, a corresponding LED will light and the fan
	will be set to on state.

	The thermometer takes the ten samples per second,
	averages the samples, and prints the results to the serial
	monitor.
*/

//defines which pin thermistor is connected to
#define THERMISTORPIN A0
//resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
//temp. for nominal resistance
#define TEMPERATURENOMINAL 25
//number of temperature samples to average
#define NUMSAMPLES 10
//beta coefficient of thermistor usually (3000-4000)
#define BCOEFFICIENT 3950
//set value of resistor in series with thermistor
#define SERIESRESISTOR 10000

float steinhart;
float fahrenheit;
float currentTemp;
float highTemp;
float lowTemp;
float tempRange;
float average;
float optimalTempMax;
float optimalTempMin;

const int bluePin = 9;
const int greenPin = 10;
const int redPin = 11;
const int fanPin = 3;

uint8_t i;
uint16_t samples[NUMSAMPLES];

	void setup()
	{
		pinMode(bluePin, OUTPUT);
		pinMode(greenPin, OUTPUT);
		pinMode(redPin, OUTPUT);
		pinMode(fanPin, OUTPUT);
		Serial.begin(9600);

		//Ask for user input for optimalTempMax
		Serial.print("Set MAX optimal temp: ");
		//wait for user input
		while (Serial.available() == 0) {}
		optimalTempMax = Serial.parseFloat();

		Serial.println(optimalTempMax);

		//Ask for user input for optimalTempMin
		Serial.print("Set MIN optimal temp: ");
		//wait for user input
		while (Serial.available() == 0) {}
		optimalTempMin = Serial.parseFloat();
		
		Serial.println(optimalTempMin);
		Serial.println(" ");

		//use external reference voltage of 3.3v
		analogReference(EXTERNAL);
		analogRead(0);

		//take number of samples
		for (i = 0; i < NUMSAMPLES; i++)
		{
			samples[i] = analogRead(THERMISTORPIN);
			delay(10);
		}

		//average out samples
		average = 0;
		for (i = 0; i < NUMSAMPLES; i++)
		{
			average += samples[i];
		}
		average /= NUMSAMPLES;

		//convert average analog read to resistance
		average = 1023 / average - 1;
		average = SERIESRESISTOR / average;

		//Steinhart-Hart equation
		//1/T = A+Bln(R)+C(ln(R))^3
		steinhart = average / THERMISTORNOMINAL;			// (R/Ro)
		steinhart = log(steinhart);							// 1n(R/Ro)
		steinhart /= BCOEFFICIENT;							// 1/B * 1n(R/Ro)
		steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);	// + (1/To)
		steinhart = 1.0 / steinhart;						// invert
		steinhart -= 273.15;								// convert to Celcius

		fahrenheit = (steinhart  * 9) / 5 + 32;
		currentTemp = fahrenheit;

		lowTemp = currentTemp;
		highTemp = currentTemp;
	}

void loop()
{
	//take number of samples
	for (i = 0; i < NUMSAMPLES; i++)
	{
		samples[i] = analogRead(THERMISTORPIN);
		delay(10);
	}

	//average out samples
	average = 0;
	for (i = 0; i < NUMSAMPLES; i++)
	{
		average += samples[i];
	}
	average /= NUMSAMPLES;

	//convert average analog read to resistance
	average = 1023 / average - 1;
	average = SERIESRESISTOR / average;

	//Steinhart-Hart equation
	//1/T = A+Bln(R)+C(ln(R))^3
	steinhart = average / THERMISTORNOMINAL;			// (R/Ro)
	steinhart = log(steinhart);							// 1n(R/Ro)
	steinhart /= BCOEFFICIENT;							// 1/B * 1n(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);	// + (1/To)
	steinhart = 1.0 / steinhart;						// invert
	steinhart -= 273.15;								// convert to Celcius

	fahrenheit = (steinhart  * 9) / 5 + 32;
	currentTemp = fahrenheit;

	//Temp is optimal
	if (currentTemp > optimalTempMin && currentTemp < optimalTempMax)
	{
		digitalWrite(bluePin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(redPin, LOW);
		digitalWrite(fanPin, LOW);
	}
	//Temp is cold
	else if (currentTemp < optimalTempMin)
	{
		digitalWrite(bluePin, HIGH);
		digitalWrite(greenPin, LOW);
		digitalWrite(redPin, LOW);
		digitalWrite(fanPin, HIGH);
	}
	//Temp is hot
	else if (currentTemp > optimalTempMax)
	{
		digitalWrite(bluePin, LOW);
		digitalWrite(greenPin, LOW);
		digitalWrite(redPin, HIGH);
		digitalWrite(fanPin, HIGH);
	}
	//Temp is not defined
	else
	{
		digitalWrite(bluePin, HIGH);
		digitalWrite(greenPin, HIGH);
		digitalWrite(redPin, HIGH);
		digitalWrite(fanPin, LOW);
	}

	//Sets tempRange
	if (highTemp < currentTemp)
	{
		highTemp = currentTemp;
	}
	else if (lowTemp > currentTemp)
	{
		lowTemp = currentTemp;
	}
	else
	{
		currentTemp;
	}

	tempRange = highTemp - lowTemp;

	Serial.print("Temperature: ");
	//Serial.print(steinhart);
	//Serial.print(" *C ");
	Serial.print(currentTemp);
	Serial.println(" *F");

	Serial.print("Optimal Temp Range: ");
	Serial.print(optimalTempMin);
	Serial.print(" - ");
	Serial.print(optimalTempMax);
	Serial.println(" *F");

	Serial.print("Measured Temp Range: ");
	Serial.print(lowTemp);
	Serial.print(" - ");
	Serial.print(highTemp);
	Serial.println(" *F");
				
	Serial.print("Range: ");
	Serial.print(tempRange);
	Serial.println(" *F");

	Serial.println(" ");

	delay(900);
}

