#include <Servo.h>
Servo GRIP;
void setup() {
  // put your setup code here, to run once:
GRIP.attach(11);
GRIP.write(40);
delay(1000);
GRIP.write(120);
delay(1000);
GRIP.write(180);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
