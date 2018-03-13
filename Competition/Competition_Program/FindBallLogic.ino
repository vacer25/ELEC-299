

//Note:U/D servo pin 9
//Note:L/R servo pin 10
#define ANG1 0;
#define ANG2 1;
bool ang1Result=false;
bool ang2Result=false;
byte loc=ANG1;
<<<<<<< HEAD
int val;
unsigned waitMillis;
int delayMillis=410;

=======

void setup() {
>>>>>>> 8ebfd8bbf5cd4faae561e8cc87de4d437548e846
  pinMode(IR_IN_PIN, INPUT);
  //pinMode(BUZZER_PIN, OUTPUT);
  myIRserial.attach(IR_IN_PIN, -1);
  Serial.begin(115200);

<<<<<<< HEAD
while(state=0){
if (loc==ANG1){
 pivotSearchArm(0,10);
//Look in range of 0-10
//Look in range of 99-106
loc=ANG2;
}
if (loc==ANG2)
pivotSearchArm(99,104);
loc=ANG1;
}
}
void pivotSearchArm(int start, int end) {
  for (int currentLoc=start; currentLoc < end; currentLoc++) {
    waitMillis = millis() + delayMillis;
    while (millis() < delayMillis) {
      LRServo.write(currentLoc);
      IRcheck();
    }
  }
}
void IRcheck() {
  
  val = myIRserial.receive(200);
  if (val >= 48 && val <= 50) {
    ballLoc = val-48;
    state = 1;
=======
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
if (loc=ANG1){
//Look in range of 0-15

//Look in range of 99-106
}else if 
llLoc = myIRserial.receive(200);
ballLoc=(char)ballLoc;
  if (ballLoc>-1&&ballLoc<3) {
 
    state=1;
  }
}
void pivotArm(){
  
>>>>>>> 8ebfd8bbf5cd4faae561e8cc87de4d437548e846
  }
}
