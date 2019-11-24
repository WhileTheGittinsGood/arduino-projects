// I wrote this program to conceptualize a way to control a
// 3 pin RGB LED using potentiometers to adjust individual
// RGB values.
//
//

// initializes three potentiometers on analog pins
// to control RGB levels
int redPot = A0;
int greenPot = A3;
int bluePot = A6;

// initializes three RGB LED pins on digital PWM pins
int redLight = 9;
int greenLight = 6;
int blueLight = 3;

// creates some placeholders for to store color values
int redValue;
int greenValue;
int blueValue;

void setup() {
  
  // sets RGB LED pins as OUTPUT on digital PWM pins
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(blueLight, OUTPUT);

  // initialize serial @ 9600baud
  Serial.begin(9600);
  Serial.print("RGB LED controller");

  // delay before stream of RGB values
  delay(1000);
}

void loop() {
  
  // reads the values of the color potentiometers and
  // sets it as the value of the corresponding placeholder
  redValue = analogRead(redPot);
  greenValue = analogRead(greenPot);
  blueValue = analogRead(bluePot);

  // maps analog read values to 0-255
  redValue = map(redValue, 0, 690, 0, 255);
  greenValue = map(greenValue, 0, 690, 0, 255);
  blueValue = map(blueValue, 0, 690, 0, 255);

  // writes the color values (0-255) to PWM pins
  analogWrite(redLight, redValue);
  analogWrite(greenLight, greenValue);
  analogWrite(blueLight, blueValue);

  // prints color values to serial
  Serial.print(redValue);
  Serial.print("r ");
  Serial.print(greenValue);
  Serial.print("g ");
  Serial.print(blueValue);
  Serial.println("b ");
}
