#define LTHRESH 880  //you need to find a good value for  level xxx
#define CTHRESH 880  //you need to find a good value for  level xxx#define CTHRESH
#define RTHRESH 880

#define LSEN A0
#define CSEN A2
#define RSEN A1

#define LDIR 4
#define LSPD 5
#define RDIR 7
#define RSPD 6
#define SPEED 80
void setup() {
  // put your setup code here, to run once:
  pinMode(LDIR, OUTPUT);
  pinMode(LSPD, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPD, OUTPUT);
  analogWrite(LSPD, SPEED);
  digitalWrite(LDIR, HIGH);
  analogWrite(RSPD, SPEED);
  digitalWrite(RDIR, HIGH);
  Serial.begin(115200);
}

void loop() {
  int left = analogRead(LSEN);
  int right = analogRead(RSEN);
  int center = analogRead(CSEN);

  Serial.print("Left: ");
  Serial.print(left);
  Serial.print("  Cent: ");
  Serial.print(center);
  Serial.print("  Right: ");
  Serial.println(right);

  if (center >= CTHRESH && left < LTHRESH && right < RTHRESH) { //forward
    analogWrite(RSPD, SPEED);
    analogWrite(LSPD, SPEED);
    Serial.println("F");
  }
  else if (left < LTHRESH && right >= RTHRESH) {
    analogWrite(RSPD, 0);
    analogWrite(LSPD, SPEED);
    Serial.println("R");
  }//turn right
  else if (left >= LTHRESH && right < RTHRESH) {
    analogWrite(RSPD, SPEED);
    analogWrite(LSPD, 0);
    Serial.println("L");
  }//turn left
  else if (center < CTHRESH && left < LTHRESH && right < RTHRESH) {
    Serial.println("S");
    spin();
    while (1) {
      ;
    }
  }
}

void spin() {
  while (analogRead(CSEN) < CTHRESH) {
    analogWrite(LSPD, SPEED);
    digitalWrite(LDIR, HIGH);
    analogWrite(RSPD, SPEED);
    digitalWrite(RDIR, LOW);
  }
  analogWrite(LSPD, 0);
  analogWrite(RSPD, 0);

}
