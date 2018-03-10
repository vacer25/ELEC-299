#define LENC 3
#define LED 12
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LENC, INPUT);
}

void loop() {
  if (digitalRead(LENC)) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  // put your main code here, to run repeatedly:

}
