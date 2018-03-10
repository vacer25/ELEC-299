// --------------------- PINS ---------------------
#include <EEPROM.h>

#define DELTA 5
byte left_speed = 200;
byte right_speed = 200;
int LDIR = 4;
int LSPD = 5;
int RDIR = 7;
int RSPD = 6;

int RIGHT_BUMPER_PIN = A2;
int LEFT_BUMPER_PIN = A1;

// --------------------- DATA ---------------------

bool PSTATE = false;
bool LSTATE = false;

int SPEED = 128;
int _90_DEGREE_TURN_TIME = 1000;

int RIGHT = 1;
int LEFT = 0;

#define SERIAL_DEBUG_ENABLED

#ifdef SERIAL_DEBUG_ENABLED
/*
  #define DebugPrint(...)  \
  Serial.print(millis());     \
  Serial.print(": ");    \
  Serial.print(__PRETTY_FUNCTION__); \
  Serial.print(' ');      \
  Serial.print(__LINE__);     \
  Serial.print(' ');      \
  Serial.print(__VA_ARGS__)
  #define DebugPrintln(...)  \
  Serial.print(millis());     \
  Serial.print(": ");    \
  Serial.print(__PRETTY_FUNCTION__); \
  Serial.print(' ');      \
  Serial.print(__LINE__);     \
  Serial.print(' ');      \
  Serial.println(__VA_ARGS__)
*/
#define DebugPrint(...) Serial.print(__VA_ARGS__)
#define DebugPrintln(...) Serial.println(__VA_ARGS__)
#else
#define DebugPrint(...)
#define DebugPrintln(...)
#endif

void setup() {

  // --------------------- SERIAL ---------------------

#ifdef SERIAL_DEBUG_ENABLED
  Serial.begin(115200);
#endif
 left_speed = EEPROM.read(0);
 right_speed = EEPROM.read(1);
  DebugPrintln("At start of SETUP...");

  // --------------------- PIN MODES ---------------------

  pinMode(LDIR, OUTPUT);
  pinMode(LSPD, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPD, OUTPUT);

  pinMode(RIGHT_BUMPER_PIN, INPUT);
  pinMode(LEFT_BUMPER_PIN, INPUT);

  // --------------------- STOP MOTORS ---------------------

  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPD, 0);
  analogWrite(RSPD, 0);

  // --------------------- WAIT FOR BUTTON ---------------------

  DebugPrintln("About to wait for button...");

  waitForButton();
  delay(1000);

  // --------------------- START MOTORS ---------------------


}

void loop() {

  driveForward();
  adjustSpeeds();
  //delay(100);

}

// --------------------- DRIVING ---------------------

void driveForward() {

  DebugPrintln("Driving FORWARD...");

  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);

  DebugPrint("Left speed: ");
  DebugPrint(left_speed);
  DebugPrint(" Right speed: ");
  DebugPrintln(right_speed);

  analogWrite(LSPD, left_speed);
  analogWrite(RSPD, right_speed);
}

void adjustSpeeds() {

  boolean rightBumperStatus = !digitalRead(RIGHT_BUMPER_PIN);
  boolean leftBumperStatus = !digitalRead(LEFT_BUMPER_PIN);

  if (rightBumperStatus || leftBumperStatus) {
    delay(500);

    rightBumperStatus = !digitalRead(RIGHT_BUMPER_PIN);
    leftBumperStatus = !digitalRead(LEFT_BUMPER_PIN);
  }

  if (rightBumperStatus && leftBumperStatus) { // Both
    DebugPrintln("BOTH bumpers hit!");
    EEPROM.put(0, left_speed); 
    delay(100);
    EEPROM.put(1, right_speed);
delay(500);
    right_speed = left_speed = 0;

  

  } else if (!rightBumperStatus && leftBumperStatus) { // Only left

    DebugPrintln("LEFT bumper hit!");
    left_speed -= DELTA;
    right_speed += DELTA;
    delay(500);

  } else if (rightBumperStatus && !leftBumperStatus) { // Only right
    DebugPrintln("RIGHT bumper hit!");
    left_speed += DELTA;
    right_speed -= DELTA;

    delay(500);

  }

}

// --------------------- BUTTON ---------------------

///*
void waitForButton() {

  DebugPrintln("Waiting for button...");

  bool butStat = digitalRead(RIGHT_BUMPER_PIN);

  while (butStat) {
    delay(10);
    butStat = digitalRead(RIGHT_BUMPER_PIN);
  }
  while (!butStat) {
    butStat = digitalRead(RIGHT_BUMPER_PIN);
    delay(10);
  }

  DebugPrintln("Button waiting complete!");

}
//*/
