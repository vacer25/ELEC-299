

//Note:U/D servo pin 9
//Note:L/R servo pin 10
#define byte ANG1=0;
#define byte ANG2=1;
bool ang1Result=False;
bool ang2Result=False;
byte loc=ANG1;

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
  
  }
