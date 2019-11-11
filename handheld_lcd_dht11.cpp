/*
  This program is intended for use with my handheld prototype
  circuit board, build for arduino nano to be used with a 16 x 2
  lcd and a DHT11 temperature and humidity sensor.
*/

//include LiquidCrystal library
#include "LiquidCrystal.h"
//include DHT library
#include "DHT.h"
//connect signal pin on DHT11 to D13 on the arduino
#define DHTPIN 13
#define DHTTYPE DHT11
//piezo buzzer on D12
#define BUZZER 12

const int rs = 4, en = 5, d4 =7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int numNotes = 8;
int frequencies[] = {  262, 294, 330, 349, 392, 440, 494, 523};

//initializes the DHT11
DHT dht(DHTPIN, DHTTYPE);

  void setup()
  {
    pinMode(DHTPIN, INPUT);
    pinMode(BUZZER, OUTPUT);
    //begins serial communication
    Serial.begin(9600);
    //begins LCD communication
    lcd.begin(16,2);
    lcd.clear();
    Serial.println("DHT11 Startup");
    lcd.setCursor(0,0);
    lcd.print("What the fuck's");
    lcd.setCursor(0,1);
    lcd.print("the temperature?");
    //begeins DHT11 readings
    dht.begin();
    delay(1000);

    int i;
    
    for (i = 0; i < numNotes; i++)
    {
      tone(BUZZER, frequencies[i], 100);
      delay(100);
    }

    delay(3000);
    lcd.clear();
  }

void loop()
{
  //sets degrees celcius and fahrenheit for DHT11 readout
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);
  float h = dht.readHumidity();
  
  //prints results to the serial monitor
  Serial.print("Temp: ");
  Serial.print(c);
  Serial.print("/");
  Serial.println(f);
  Serial.print("Humid: ");
  Serial.println(h);
  Serial.println(" ");

  //prints results to LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Temp: ");
  //lcd.print(c);
  lcd.print(f);
  lcd.print(char(223));
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print(" Humid: ");
  lcd.print(h);
  lcd.print("%");

  delay(1000);
}