// I wrote this program to conceptualize a way to control any
// type of RGB LED using potentiometers to adjust individual
// RGB values.
//
//

// initializes three potentiometers on analog pins
// to control RGB levels
int redPot = A0;
int greenPot = A1;
int bluePot = A2;

// initializes three RGB LED pins on digital PWM pins
int redLight = 9;
int greenLight = 10;
int blueLight = 11;

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
  Serial.print('RGB LED controller');
}

void loop() {
  // reads the values of the color potentiometers and
  // sets it as the value of the corresponding placeholder
  redValue = analogRead(redPot);
  greenValue = analogRead(greenPot);
  blueValue = analogRead(bluePot);

  // maps the analog read value to 0-255
  redValue = map(redValue, 0, 800, 0, 255);
  greenValue = map(greenValue, 0, 800, 0, 255);
  blueValue = map(blueValue, 0, 800, 0, 255);

  // writes the color values (0-255) to PWM pins
  analogWrite(redLight, redValue);
  analogWrite(greenLight, greenValue);
  analogWrite(blueLight, blueValue);

  // prints color values to serial
  Serial.println('r');
  Serial.print(redValue);
  Serial.println('g');
  Serial.print(greenValue);
  Serial.println('b');
  Serial.print(blueValue);
}
