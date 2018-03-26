// --------------------- LIBS ---------------------

#include <Servo.h>
#include "QSerial.h"
//#include "Filter.h"

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

// Bumper
#define BUMPER_PIN            A0

// Light Sensors
#define L_LIGHT_SENSOR_PIN    A3
#define C_LIGHT_SENSOR_PIN    A5
#define R_LIGHT_SENSOR_PIN    A4

// LED Indicators
#define INDICATOR_LED_1_PIN   A1
#define INDICATOR_LED_2_PIN   12

// --------------------- CONSTANT DATA ---------------------

// Directions
#define RIGHT                 1
#define LEFT                  0
#define FORWARDS              1
#define BACKWARDS             0

// Turning
#define _45_DEGREES           0
#define _90_DEGREES           1
#define _180_DEGREES          2

// Arm positions
#define ARM_LEFT_PAN          0
#define ARM_CENTER_PAN        1
#define ARM_RIGHT_PAN         2

#define ARM_RAISED_TILT       0
#define ARM_IR_SENSE_TILT     1
#define ARM_LOWERED_TILT      2

// Speeds
#define DRIVE_SPEED                       255
#define LINE_FOLLOW_SPEED                 255 // Need to TEST
#define SLOW_DRIVE_SPEED                  175 // Need to TEST
#define TURN_SPEED                        110 // Need to TEST

// Timings
#define _90_DEGREE_TURN_TIME              750 // Need to TEST

#define DRIVE_TO_CENTER_ADJUST_TIME       200 // Need to TEST
#define BACKUP_FROM_DEPOSIT_TIME          200 // Need to TEST
#define BACKUP_FROM_WALL_TIME             180 // Need to TEST
#define _90_TURN_IGNORE_LINE_FOLLOW_TIME  400 // Need to TEST
#define _180_TURN_IGNORE_LINE_FOLLOW_TIME 300 // Need to TEST
#define SIDE_IGNORE_LINE_FOLLOW_TIME      200 // Need to TEST
#define CENTER_IGNORE_DROP_BALL_TIME      100 // Need to TEST

// Arm Timings
#define ARM_RAISE_WAIT_TIME               400 // Need to TEST
#define ARM_IR_SENSE_WAIT_TIME            1   // Need to TEST
#define ARM_LOWER_WAIT_TIME               400 // Need to TEST
#define GRIP_OPEN_WAIT_TIME               400 // Need to TEST
#define GRIP_CLOSE_WAIT_TIME              400 // Need to TEST

// IR Sensor timings
#define IR_SENSOR_SCAN_TIMEOUT            200 // Need to TEST
#define IR_SENSOR_ARM_MOVE_DWEL_TIME      200 // Need to TEST

// Angles
#define DIAGONAL_1_TURN_ANGLE             50 // Need to TEST//65-55
#define DIAGONAL_2_TURN_ANGLE             45 // Need to TEST//35-45

// Arm Angles
#define GRIP_OPEN_ANGLE                   50
#define GRIP_CLOSE_ANGLE                  250 // Need to TEST
#define ARM_RAISED_ANGLE                  155
#define ARM_LOWERED_ANGLE                 91
#define ARM_IR_SENSE_ANGLE                110 // Need to TEST

// Distances
//#define SLOW_DOWN_DISTANCE_READING        300
//#define STOPPING_DISTANCE_READING         350

// Light threshold
#define LINE_SENSOR_THRESHOLD             900

// --------------------- STATE DATA ---------------------

// -1 = Don't use simulated ball location, 0 = Right, 1 = Center, or 2 = Left
int simulatedBallLocation  = -1;

// If this is defined (not commented), the simulated ball locaton will cycle as 0-> 1 -> 2 ->0...
#define SIMULATED_BALL_LOCATION_INCREMENT

// 0 = Find Ball, 1 = Collect Ball, 2 = Deposit Ball
int state = 0; 

// -1 = None, 0 = Right, 1 = Center, or 2 = Left
int ballLoc = -1; 

// 0 = Left, 1 = Right
int armPos = ARM_CENTER_PAN; 

// -1, -2 = Error / no signal, 48, 49, 50 == Valid ball location data
int currentIRValue;

// --------------------- SERVO OBJECTS ---------------------

Servo LRServo, UDServo, gripServo;

// --------------------- IR SERIAL OBJECT ---------------------

QSerial IRSerial;

//------------------------SMOOTHING-----------------------------------

//Filter distanceFilter;

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
  pinMode(BUMPER_PIN, INPUT);

  pinMode(IR_SENSOR_PIN, INPUT);

  //pinMode(DISTANCE_SENSOR_PIN, INPUT);

  pinMode(L_LIGHT_SENSOR_PIN, INPUT);
  pinMode(C_LIGHT_SENSOR_PIN, INPUT);
  pinMode(R_LIGHT_SENSOR_PIN, INPUT);

  pinMode(INDICATOR_LED_1_PIN, OUTPUT);
  pinMode(INDICATOR_LED_2_PIN, OUTPUT);

  
  // Set the LED indicators to display no ball location
  digitalWrite(INDICATOR_LED_1_PIN, LOW);
  digitalWrite(INDICATOR_LED_2_PIN, LOW);
  
  // --------------------- IR SENSOR ---------------------

  IRSerial.attach(IR_SENSOR_PIN, -1);
  
  // ---------------------- DISTANCE SMOOTHING -----------------------

  //distanceFilter.setFilteredDistance((float)analogRead(DISTANCE_SENSOR_PIN));
  
  // --------------------- SERVOS ---------------------

  LRServo.attach(ARM_LR_SERVO_PIN);
  UDServo.attach(ARM_UD_SERVO_PIN);
  gripServo.attach(ARM_GRIP_SERVO_PIN);

  // --------------------- STOP MOTORS ---------------------

  stopMotors();

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
