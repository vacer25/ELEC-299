int pushButton1 = 11; //right
int pushButton2 = 12; //left
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  pinMode(pushButton1, INPUT);
  WaitButton();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("HIHIHIHII");
}

void WaitButton() {
  bool butStat = digitalRead(pushButton1);
  while (butStat == 1) {
    delay(10);
    butStat = digitalRead(pushButton1);

  }
  while (!butStat) {
    butStat = digitalRead(pushButton1);
    delay(10);
  }

}
