// --------------------- PINS ---------------------

#define L_MOTOR_DIR_PIN       4
#define L_MOTOR_SPD_PIN       5
#define R_MOTOR_SPD_PIN       6
#define R_MOTOR_DIR_PIN       7

#define ARM_UD_SERVO_PIN      9
#define ARM_LR_SERVO_PIN      10
#define ARM_GRIP_SERVO_PIN    11

#define IR_SENSOR_PIN         8

#define DISTANCE_SENSOR_PIN   A0

#define L_LIGHT_SENSOR_PIN    A3
#define C_LIGHT_SENSOR_PIN    A5
#define R_LIGHT_SENSOR_PIN    A4

// --------------------- CONSTANT DATA ---------------------

#define DRIVE_SPEED       255
#define SLOW_DRIVE_SPEED  128 // Need to TEST
#define TURN_SPEED        255 // Need to TEST

#define _90_DEGREE_TURN_TIME              1000 // Need to TEST
#define SHORT_DRIVE_TO_CENTER_TIME        1000 // Need to TEST
#define DRIVE_TO_HALF_CENTER_TIME         1000 // Need to TEST
#define DRIVE_IGNORING_LINE_FOLLOW_TIME   1000 // Need to TEST

#define DIAGONAL_TURN_ANGLE 45 // Need to TEST

#define RIGHT 1
#define LEFT  0

#define FORWARDS  1
#define BACKWARDS 0

#define SLOW_DOWN_DISTANCE_READING  530
#define STOPPING_DISTANCE_READING   660

#define LINE_SENSOR_THRESHOLD 900

// --------------------- STATE DATA ---------------------

int state = 0; // 0 = Find Ball, 1 = Collect Ball, 2 = Deposit Ball

int ballLoc = -1; // 0, 1, or 2

int armPos = 90; // From 0 (left?) to 180 (right?)

//------------------------SMOOTHING-----------------------------------

const int numReadings = 30;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// -------------------- SERIAL DATA --------------------

#define SERIAL_BAUD_RATE 115200

// --------------------- DEBUGGING ---------------------

#define SERIAL_DEBUG_ENABLED

#ifdef SERIAL_DEBUG_ENABLED
#define DebugPrint(...) Serial.print(__VA_ARGS__)
#define DebugPrintln(...) Serial.println(__VA_ARGS__)
#else
#define DebugPrint(...)
#define DebugPrintln(...)
#endif

void setup() {

  // -------------------- INIT SERIAL --------------------

  Serial.begin(SERIAL_BAUD_RATE);

  // --------------------- PIN MODES ---------------------

  pinMode(LDIR, OUTPUT);
  pinMode(LSPD, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPD, OUTPUT);

  pinMode(R_BUMPER_PIN, INPUT);
  pinMode(L_BUMPER_PIN, INPUT);

  pinMode(DISTANCE_SENSOR_PIN, INPUT);

  pinMode(L_LIGHT_SENSOR_PIN, INPUT);
  pinMode(C_LIGHT_SENSOR_PIN, INPUT);
  pinMode(R_LIGHT_SENSOR_PIN, INPUT);

  // --------------------- STOP MOTORS ---------------------

  stopMotors();

  // ----------------------SMOOTHING-----------------------

  setFilteredDistance(analogRead(DISTANCE_SENSOR_PIN));

}

void loop() {

  updateFilteredDistance(analogRead(DISTANCE_SENSOR_PIN));

  // ---------------------- FIND BALL-----------------------

  if (state == 0) { // Find Ball
    // Assumes the the robot is facing forward (ball location 1),
    // the robot arm is lowered in the forward direction



  }

  // ---------------------- COLLECT BALL-----------------------

  else if (state == 1) { // Collect Ball
    // Assumes that the robot has found the ball with the ball location indicated by the ballLoc variable,
    // the robot arm is lowered in the forward direction



  }

  // ---------------------- DEPOSIT BALL-----------------------

  else if (state == 2) { // Deposit Ball
    // Assumes that the robot has the ball in the gripper and is at the ball location indicated by the ballLoc variable,
    // the robot arm is raised in the forward direction

    // New version
    runDepositBallLogic();

    /*
      // Old, unfinished implementation
      // Drive backwards from the ball collect location
      goToCenter();

      // Turn the robot towards the deposit point
      if (ballLoc == 0) { // Ball was on the right of the deposit point
      pivot(RIGHT, 90);
      }
      else if (ballLoc == 1) { // Ball was on the ahead of the deposit point
      pivot(RIGHT, 180);
      }
      else if (ballLoc == 2) { // Ball was on the left of the deposit point
      pivot(LEFT, 90);
      }
    */

  }

}

// --------------------- DRIVING ---------------------

void stopMotors() {

  analogWrite(L_MOTOR_SPD_PIN, 0);
  analogWrite(R_MOTOR_SPD_PIN, 0);

}

void drive(boolean forwards, int currentSpeed) {

  digitalWrite(L_MOTOR_DIR_PIN, forwards ? HIGH : LOW);
  digitalWrite(R_MOTOR_DIR_PIN, forwards ? HIGH : LOW);

  analogWrite(L_MOTOR_SPD_PIN, currentSpeed);
  analogWrite(R_MOTOR_SPD_PIN, currentSpeed);

}

// --------------------- LINE FOLLOWING ---------------------

void followLine() {

  // Get the sensor readings
  int leftSensorValue = analogRead(leftSensorPin);
  int centerSensorValue = analogRead(centerSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  // If only the middle sensor is over the line, drive forward
  if (centerSensorValue >= LINE_SENSOR_THRESHOLD && leftSensorValue < LINE_SENSOR_THRESHOLD && rightSensorValue < LINE_SENSOR_THRESHOLD) { //forward
    drive(FORWARDS, DRIVE_SPEED);
    DebugPrintln.println("F");
  }

  // If the right sensor is over the line, turn right
  else if (leftSensorValue < LINE_SENSOR_THRESHOLD && rightSensorValue >= LINE_SENSOR_THRESHOLD) {
    turn(RIGHT);
    DebugPrintln.println("R");
  }

  // If the left sensor is over the line, turn left
  else if (leftSensorValue >= LINE_SENSOR_THRESHOLD && rightSensorValue < LINE_SENSOR_THRESHOLD) {
    turn(LEFT);
    DebugPrintln.println("L");
  }

}

// --------------------- TURNING ---------------------

// Turn by stopping 1 motor
// rightDir: true to pivot right, false to pivot left
void turn(boolean rightDir) {

  // Set the motors to go forward
  digitalWrite(L_MOTOR_DIR_PIN, HIGH);
  digitalWrite(R_MOTOR_DIR_PIN, HIGH);

  // If turning right, turn the left motor on and right motor off
  if (rightDir) {
    analogWrite(R_MOTOR_SPD_PIN, 0);
    analogWrite(L_MOTOR_SPD_PIN, SPEED);
  }

  // If turning left, turn the left motor off and right motor on
  else {
    analogWrite(R_MOTOR_SPD_PIN, SPEED);
    analogWrite(L_MOTOR_SPD_PIN, 0);
  }

}

// --------------------- PIVOTING ---------------------

// Rotates the robot by driving wheels motors in opposite directions
// Stops at the end of the pivot
// rightDir: true to pivot right, false to pivot left
// angle: angle to pivot by, in degrees
void pivot(boolean rightDir, float angle) {

  // Print debugging info if debugging is globally defined
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

  // Set the left and right motor directions depending on pivot direction
  digitalWrite(L_MOTOR_DIR_PIN, rightDir ? HIGH : LOW);
  digitalWrite(R_MOTOR_DIR_PIN, rightDir ? LOW : HIGH);

  // Start the motors
  analogWrite(L_MOTOR_SPD_PIN, TURN_SPEED);
  analogWrite(R_MOTOR_SPD_PIN, TURN_SPEED);

  // Delay for the needed amount of time (relative to 90° turn time)
  delay(_90_DEGREE_TURN_TIME * (angle / 90.0));

  // Stop the motors
  analogWrite(L_MOTOR_SPD_PIN, 0);
  analogWrite(R_MOTOR_SPD_PIN, 0);

}


// --------------------- BUTTON ---------------------

// Waits for the right bumper switch to be pressed and released
// Called at end of setup() to stall program execution after initialization
void waitForButton() {

  // Print debugging info if debugging is globally defined
  DebugPrintln("Waiting for button...");

  // Read the button status (Pressed == LOW, Released == HIGH)
  bool buttonPressed = !digitalRead(R_BUMPER_PIN);

  // Wait while the button is not pressed
  while (!buttonPressed) {
    // Delay for button debouncing
    delay(10);
    // Update the button status
    buttonPressed = !digitalRead(R_BUMPER_PIN);
  }

  // When this loop is reached, the button was pressed
  // Wait while the button is pressed
  while (buttonPressed) {
    // Delay for button debouncing
    delay(10);
    // Update the button status
    buttonPressed = !digitalRead(R_BUMPER_PIN);
  }

  // Print debugging info if debugging is globally defined
  DebugPrintln("Button waiting complete!");
}
