#define LED_PIN 11
#define BUZZER  10
#define BUTTON  12
bool mode = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(BUTTON)) {
    mode = !mode;
  }
  if (!mode) {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    delay(1000);
  }
  else {
    tone(BUZZER, map(analogRead(A0),0,1023,440,880), 200);
    delay(1000);
  }
}
