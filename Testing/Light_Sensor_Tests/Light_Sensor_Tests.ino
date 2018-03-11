/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#define leftSensorPin   3
#define centerSensorPin 5
#define rightSensorPin  4

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  pinMode(leftSensorPin, INPUT);
  pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {

  int leftSensorValue = analogRead(leftSensorPin);
  int centerSensorValue = analogRead(centerSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  Serial.print(leftSensorValue);
  Serial.print("\t|\t");
  Serial.print(centerSensorValue);
  Serial.print("\t|\t");
  Serial.println(rightSensorValue);
  
  delay(10);        // delay in between reads for stability
}
