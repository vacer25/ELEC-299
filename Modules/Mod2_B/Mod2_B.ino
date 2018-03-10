void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("A0: ");
  Serial.print(analogRead(A0));

  Serial.print("  A1: ");
  Serial.print(analogRead(A1));

  Serial.print("  A2: ");
  Serial.println(analogRead(A2));

  delay(50);

}
