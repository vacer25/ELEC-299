#define LENC 3
#define LED 12
bool PSTATE = false;
bool LSTATE = false;
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LENC, INPUT);
}

void loop() {

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
  // put your main code here, to run repeatedly:

}
