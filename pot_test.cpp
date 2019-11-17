#include<LiquidCrystal.h>

const int rs = 7, e = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2, relay0 = 12;

LiquidCrystal lcd (rs, e, d4, d5, d6, d7);

int menuSelector = A0;

void setup()
{
  // initalizes digitial i/o pins:
  pinMode(relay0, OUTPUT);
  // initializes serial communication @ 9600baud
  Serial.begin(9600);
  // prints setup data to LCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Greenhouse Beta");
  lcd.setCursor(0,1);
  lcd.print("Project  v1.0");
  delay(3000);
  lcd.clear();
  
  
}

void loop()
{
  int menuState = analogRead(menuSelector);
  menuState =   map(menuState, 0, 800, 1, 4);
 
  
  switch (menuState)
  {
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A1 (temp):");
      lcd.print(analogRead(A1));
      lcd.setCursor(0,1);
      lcd.print("Uptime: ");
      lcd.print(millis()/1000);
      delay(100);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A2 (moist):");
      lcd.print(analogRead(A2));
      lcd.setCursor(0,1);
      lcd.print("Uptime: ");
      lcd.print(millis()/1000);
      delay(100);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A3:");
      lcd.print(analogRead(A3));
      lcd.setCursor(0,1);
      lcd.print("Uptime: ");
      lcd.print(millis()/1000);
      delay(100);
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Thermistor: ");
      lcd.print(analogRead(A4));
      delay(100);
      break;
  }
  
  if(analogRead(A1)  > 511)
  {
    digitalWrite(relay0, HIGH);
  }
  else
  {
    digitalWrite(relay0, LOW);
  }
}