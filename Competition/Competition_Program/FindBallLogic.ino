void FindBallLogic{
//Servo LRServo;
//Servo UDServo;

//Note:U/D servo pin 9
//Note:L/R servo pin 10
#define byte ANG1=0;
#define byte ANG2=1;
bool ang1Result=False;
bool ang2Result=False;
byte loc=ANG1;
int val;
unsigned waitMillis;
int delayMillis=410;
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

while(state=0){
if (loc=ANG1){
 pivotSearchArm(0,10);
//Look in range of 0-10
//Look in range of 99-106
loc=ANG2;
}
if (loc=ANG2)
pivotSearchArm(99,104);
loc=ANG1;
}
}
void pivotSearchArm(int start,int end){
  for(start;start<end;start++){
    waitMillis=millis()+delayMillis;
    while(millis()<delayMillis){
    LRServo.write(start);
    IRcheck();
    }
    }
}
void IRcheck(){
val = myIRserial.receive(200);
  if (val>=48&&val<=50) {
    ballLoc=(char)val;
    state=1;
  }
  }
