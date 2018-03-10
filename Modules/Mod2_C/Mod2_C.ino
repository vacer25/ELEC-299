#define LTHRESH 920  //you need to find a good value for  level xxx
#define CTHRESH 920  //you need to find a good value for  level xxx#define CTHRESH
#define RTHRESH 920

#define LDIR 4
#define LSPD 5
#define RDIR 7
#define RSPD 6
void setup() {
  // put your setup code here, to run once:
  pinMode(LDIR, OUTPUT);
  pinMode(LSPD, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPD, OUTPUT);

while(analogRead(A2)<CTHRESH){
   analogWrite(LSPD, 100);
  digitalWrite(LDIR, HIGH);
   analogWrite(RSPD, 100);
  digitalWrite(RDIR, LOW);
  }
analogWrite(LSPD, 0);
analogWrite(RSPD, 0);
}

void loop() {
}
