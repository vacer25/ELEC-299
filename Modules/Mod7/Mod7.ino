//------------------------SMOOTHING-----------------------------------
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A3;


// --------------------- PINS ---------------------

int LDIR = 4;
int LSPD = 5;
int RDIR = 7;
int RSPD = 6;

int RIGHT_BUMPER_PIN = A2;
int LEFT_BUMPER_PIN = A1;

// --------------------- DATA ---------------------

bool PSTATE = false;
bool LSTATE = false;

int SPEED = 153;
int _90_DEGREE_TURN_TIME = 1000;

int RIGHT = 1;
int LEFT = 0;

bool RUNAWAY = false;
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

  analogWrite(LSPD, SPEED);
  analogWrite(RSPD, SPEED);
  // ----------------------SMOOTHING-----------------------
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
  void loop() {


    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    // calculate the average:
    average = total / numReadings;

    driveForward();
    delay(50);
    if (average > 300) {
      for (int i = SPEED - 1; i > 0; i -= 20) {
        analogWrite(LSPD, i);
        analogWrite(RSPD, i);
        delay(50);
      }
      backup();
      delay(1000);
      RUNAWAY = true;
    }
    if (RUNAWAY) {
      analogWrite(LSPD, SPEED);
      analogWrite(RSPD, SPEED);
      pivot(RIGHT, 90);
      average = 0;
      readIndex = 0;
      //total=0;
      RUNAWAY = false;
    }
    //reactBumpers();
    //delay(100);

  }

  // --------------------- DRIVING ---------------------

  void driveForward() {

    DebugPrintln("Driving FORWARD...");

    digitalWrite(LDIR, HIGH);
    digitalWrite(RDIR, HIGH);
    analogWrite(LSPD, SPEED);
    analogWrite(RSPD, SPEED);

  }

  void backup() {

    DebugPrintln("Backing up...");

    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);

    delay(2000);

  }

  void pivot(boolean rightDir, int angle) {

    DebugPrint("Pivoting ");
    if (rightDir) {
      DebugPrint("right ");
    }
    else {
      DebugPrint("left ");
    }
    DebugPrint("by ");
    DebugPrint(angle);
    DebugPrintln(" degrees");

    digitalWrite(LDIR, rightDir ? HIGH : LOW);
    digitalWrite(RDIR, rightDir ? LOW : HIGH);

    delay(_90_DEGREE_TURN_TIME * (angle / 90.0));
    //delay(_90_DEGREE_TURN_TIME);

  }


  void reactBumpers() {

    boolean rightBumperStatus = !digitalRead(RIGHT_BUMPER_PIN);
    boolean leftBumperStatus = !digitalRead(LEFT_BUMPER_PIN);

    if (rightBumperStatus && leftBumperStatus) { // Both

      DebugPrintln("BOTH bumpers hit!");

      backup();
      pivot(RIGHT, 180);

      delay(500);

    } else if (!rightBumperStatus && leftBumperStatus) { // Only left

      DebugPrintln("LEFT bumper hit!");

      backup();
      pivot(RIGHT, 45);

      delay(500);

    } else if (rightBumperStatus && !leftBumperStatus) { // Only right

      DebugPrintln("RIGHT bumper hit!");

      backup();
      pivot(LEFT, 45);

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
