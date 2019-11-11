#include<LiquidCrystal.h>
const int rs = 7, e = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd (rs, e, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("  Analog Input");
  lcd.setCursor(0,1);
  lcd.print("      Test");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Version  1.0");
  lcd.setCursor(0,1);
  lcd.print("  04 May  2018");
  delay(2000);
  lcd.clear();
}

void loop()
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A0: ");
  lcd.print(analogRead(A0));
  lcd.setCursor(8,0);
  lcd.print("A1: ");
  lcd.print(analogRead(A1));
  lcd.setCursor(0,1);
  lcd.print("A2: ");
  lcd.print(analogRead(A2));
  lcd.setCursor(8,1);
  lcd.print("A3: ");
  lcd.print(analogRead(A3));
  delay(100); 
}
