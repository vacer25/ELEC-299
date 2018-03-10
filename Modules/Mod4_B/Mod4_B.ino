//#define RENC 2
#define LENC 3
#define LED 12
bool PSTATE = false;
bool LSTATE = false;
bool SPIN = false;
int counter = 0;


#define LDIR 4
#define LSPD 5
#define RDIR 7
#define RSPD 6
#define SPEED 128
void setup() {

  pinMode(LED, OUTPUT);
  pinMode(LENC, INPUT);


  pinMode(LDIR, OUTPUT);
  pinMode(LSPD, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPD, OUTPUT);

  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPD, SPEED);
  analogWrite(RSPD, SPEED);

}

void loop() {
  count();
  if (counter == 63) {
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);
  } else if (counter == 105) {
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, HIGH);
    SPIN = true;
  }
  if (SPIN) {
    delay(1000);
    analogWrite(LSPD, 0);
    analogWrite(RSPD, 0);

    while (1) {
      ;
    }
  }
}
void count() {
  bool STATE = digitalRead(LENC);

  if (STATE != PSTATE)
  {
    ++counter;
    if (counter % 21 == 0) {
      LSTATE = !LSTATE;
      digitalWrite(LED, LSTATE);
    }
  }
  PSTATE = STATE;
}
