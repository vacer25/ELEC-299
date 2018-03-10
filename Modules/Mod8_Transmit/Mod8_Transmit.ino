#include "QSerial.h"
QSerial myIRserial; 

void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT);
  myIRserial.attach(-1, 12);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  myIRserial.transmit(00001111);
  delay(100);
  digitalWrite(12,LOW);

}
