#define LED_PIN 11
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  while (digitalRead(12)) {
    ;
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  while (!digitalRead(12)) {
    ;
  }
  while (true) {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    delay(1000);
  }
}
