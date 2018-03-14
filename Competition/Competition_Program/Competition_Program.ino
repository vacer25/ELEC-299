// --------------------- LIBS ---------------------

#include <Servo.h>
#include "QSerial.h"

// --------------------- PINS ---------------------

// Main motors
#define L_MOTOR_DIR_PIN       4
#define L_MOTOR_SPD_PIN       5
#define R_MOTOR_DIR_PIN       7
#define R_MOTOR_SPD_PIN       6

// Arm servo motors
#define ARM_UD_SERVO_PIN      9
#define ARM_LR_SERVO_PIN      10
#define ARM_GRIP_SERVO_PIN    11

// IR Sensor
#define IR_SENSOR_PIN         8

// Distance Sensor
#define DISTANCE_SENSOR_PIN   A0

// Light Sensors
#define L_LIGHT_SENSOR_PIN    A3
#define C_LIGHT_SENSOR_PIN    A5
#define R_LIGHT_SENSOR_PIN    A4

// --------------------- CONSTANT DATA ---------------------

// Directions
#define RIGHT     1
#define LEFT      0
#define FORWARDS  1
#define BACKWARDS 0

// Arm positions
#define ARM_LEFT_PAN 0
#define ARM_CENTER_PAN 1

#define ARM_RAISED_TILT                  0
#define ARM_IR_SENSE_TILT                1
#define ARM_LOWERED_TILT                 2

// Speeds
#define DRIVE_SPEED                       255
#define SLOW_DRIVE_SPEED                  128 // Need to TEST
#define TURN_SPEED                        255 // Need to TEST

// Timings
#define _90_DEGREE_TURN_TIME              1000 // Need to TEST
#define SHORT_DRIVE_TO_CENTER_TIME        1000 // Need to TEST
#define DRIVE_TO_HALF_CENTER_TIME         500 // Need to TEST
#define DRIVE_IGNORING_LINE_FOLLOW_TIME   500 // Need to TEST

// Arm Timings
#define ARM_RAISE_WAIT_TIME               100 // Need to TEST
#define ARM_IR_SENSE_WAIT_TIME            100 // Need to TEST
#define ARM_LOWER_WAIT_TIME               100 // Need to TEST
#define GRIP_OPEN_WAIT_TIME               50  // Need to TEST
#define GRIP_CLOSE_WAIT_TIME              50  // Need to TEST

// IR Sensor timings
#define IR_SENSOR_SCAN_TIMEOUT            200 // Need to TEST
#define IR_SENSOR_ARM_MOVE_DWEL_TIME      410 // Need to TEST

// Angles
#define DIAGONAL_TURN_ANGLE               45 // Need to TEST

// Arm Angles
#define GRIP_OPEN_ANGLE                   40
#define GRIP_CLOSE_ANGLE                  110 // Need to TEST
#define ARM_RAISED_ANGLE                  155
#define ARM_LOWERED_ANGLE                 91
#define ARM_IR_SENSE_ANGLE                100 // Need to TEST

// Distances
#define SLOW_DOWN_DISTANCE_READING        530
#define STOPPING_DISTANCE_READING         660

// Light threshold
#define LINE_SENSOR_THRESHOLD             900

// --------------------- STATE DATA ---------------------

int state = 0; // 0 = Find Ball, 1 = Collect Ball, 2 = Deposit Ball
int ballLoc = -1; // 0, 1, or 2
int armPos = 0; // 0 = Left, 1 = Right

int currentIRValue; // -1, -2 = Error / no signal, 48, 49, 50 == Valid lacc location data

// --------------------- SERVO OBJECTS ---------------------

Servo LRServo, UDServo, gripServo;

// --------------------- IR SERIAL OBJECT ---------------------

QSerial IRSerial;

// -------------------- SERIAL / DEBUGGING --------------------

#define SERIAL_BAUD_RATE 115200

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

  pinMode(L_MOTOR_DIR_PIN, OUTPUT);
  pinMode(L_MOTOR_SPD_PIN, OUTPUT);
  pinMode(R_MOTOR_DIR_PIN, OUTPUT);
  pinMode(R_MOTOR_SPD_PIN, OUTPUT);

  //pinMode(R_BUMPER_PIN, INPUT);
  //pinMode(L_BUMPER_PIN, INPUT);

  pinMode(IR_SENSOR_PIN, INPUT);
  
  pinMode(DISTANCE_SENSOR_PIN, INPUT);

  pinMode(L_LIGHT_SENSOR_PIN, INPUT);
  pinMode(C_LIGHT_SENSOR_PIN, INPUT);
  pinMode(R_LIGHT_SENSOR_PIN, INPUT);

  // --------------------- IR SENSOR ---------------------

  IRSerial.attach(IR_SENSOR_PIN, -1);    
  
  // --------------------- SERVOS ---------------------

  LRServo.attach(ARM_LR_SERVO_PIN);
  UDServo.attach(ARM_UD_SERVO_PIN);
  gripServo.attach(ARM_GRIP_SERVO_PIN);

  // --------------------- STOP MOTORS ---------------------

  stopMotors();

  // ----------------------SMOOTHING-----------------------

  setFilteredDistance(analogRead(DISTANCE_SENSOR_PIN));

}

void loop() {

  // ---------------------- FIND BALL -----------------------

  if (state == 0) { // Find Ball
    // Assumes the the robot is facing forward (ball location 1),
    // the robot arm is lowered in the forward direction
    runFindBallLogic();
  }

  // ---------------------- COLLECT BALL -----------------------

  else if (state == 1) { // Collect Ball
    // Assumes that the robot has found the ball with the ball location indicated by the ballLoc variable,
    // the robot arm is lowered in the forward direction
    runCollectBallLogic();
  }

  // ---------------------- DEPOSIT BALL -----------------------

  else if (state == 2) { // Deposit Ball
    // Assumes that the robot has the ball in the gripper and is at the ball location indicated by the ballLoc variable,
    // the robot arm is raised in the forward direction
    runDepositBallLogic();
  }

}

// --------------------- BUTTON ---------------------

/*
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
*/
