#include "QSerial.h"
QSerial myIRserial;

#define BUZZER_PIN 11
#define IR_IN_PIN 10

int val;

void setup() {
  pinMode(IR_IN_PIN, INPUT);
  //pinMode(BUZZER_PIN, OUTPUT);
  myIRserial.attach(IR_IN_PIN, -1);
  Serial.begin(115200);

  /*
     tone(BUZZER_PIN, 200, 50);
     delay(1000);
     tone(BUZZER_PIN, 700, 50);
     delay(1000);
     tone(BUZZER_PIN, 1500, 50);
     delay(1000);
     tone(BUZZER_PIN, 2500, 200);
  */
}

void loop() {

  val = myIRserial.receive(200);
  /*
    if (val == 1) {
    tone(BUZZER_PIN, 200, 50);
    }
    else if (val == 2) {
    tone(BUZZER_PIN, 700, 50);
    }
    else if (val == 3) {
    tone(BUZZER_PIN, 1500, 50);
    }
    else if (val > 3) {
    tone(BUZZER_PIN, 2500, 200);
    }
  */
  if (val != 0) {
    Serial.println((char)val);
  }
  //delay(100);
}
