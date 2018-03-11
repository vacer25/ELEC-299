#include <Servo.h>
Servo GRIP;
#define GSEN A1
#define GTHRESH 500
#define LED 13
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  GRIP.attach(11);
  GRIP.write(30);
  delay(1000);
  int i = 40;
  while (i < 180) {
    i++;
    GRIP.write(i);
    delay(20);
    if (analogRead(GSEN) >= GTHRESH) {
     digitalWrite(LED,HIGH);
      break;
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
