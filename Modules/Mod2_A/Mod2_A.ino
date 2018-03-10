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
}

void loop() {
  analogWrite(LSPD, 100);
  digitalWrite(LDIR, HIGH);
   analogWrite(RSPD, 100);
  digitalWrite(RDIR, LOW);
  // put your main code here, to run repeatedly:

}
