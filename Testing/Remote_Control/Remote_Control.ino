// --------------------- LIBS ---------------------

#include <Servo.h>
#include <IrReceiverSampler.h>
#include <MultiDecoder.h>

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

// --------------------- SERVO OBJECTS ---------------------

Servo LRServo, UDServo, gripServo;

// --------------------- CONSTANT DATA ---------------------

// Directions
#define RIGHT                 1
#define LEFT                  0
#define FORWARDS              1
#define BACKWARDS             0

// Speeds
#define SPEED                 255
#define TURN_SPEED            255

// Arm positions
#define ARM_LEFT_PAN          0
#define ARM_CENTER_PAN        1
#define ARM_RIGHT_PAN         2

#define ARM_RAISED_TILT       0
#define ARM_IR_SENSE_TILT     1
#define ARM_LOWERED_TILT      2

// Timings
#define _90_DEGREE_TURN_TIME  1000

// Angles
#define SMALL_TURN_ANGLE      5

// Arm Angles
#define GRIP_OPEN_ANGLE       50
#define GRIP_CLOSE_ANGLE      250 // Need to TEST
#define ARM_RAISED_ANGLE      155
#define ARM_LOWERED_ANGLE     91
#define ARM_IR_SENSE_ANGLE    110 // Need to TEST

// --------------------- STATE DATA ---------------------

boolean isGrippingBall = false;

// -------------------- IR DATA --------------------

IrReceiver *receiver;

#define RECEIVE_PIN 8U
#define BUFFERSIZE 200U
#define BAUD 115200

// -------------------- SERIAL DATA --------------------

#define SERIAL_BAUD_RATE 115200
#define SERIAL_TIMEOUT 10

#define SERIAL_DATA_LENGTH_BYTES 32

volatile uint8_t ser_buf[SERIAL_DATA_LENGTH_BYTES];

/*

  PS1 Controller data:
  IUDLRTCSXabrcdlsXXXYYYxxxyyySSSE } 32 bytes

  I:        Constatnt start byte
  U/D/L/R:  up/down/left/right
  T/C/S/X:  triangle/circle/square/x
  a/b:      Right bumper(a)/trigger(b)
  r:        Right stick click
  c/d:      Left bumper(c)/trigger(d)
  l:        Left stick click
  s:        Select
  XXX/YYY:  Right stick x/y (0-255)
  xxx/yyy:  Left stick x/y (0-255)
  SSS:      Scroll position (0-255)
  E:        Constatnt end byte

*/

// --------------------- DEBUGGING ---------------------

//#define SERIAL_DEBUG_ENABLED

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
  Serial.setTimeout(SERIAL_TIMEOUT);

  // -------------------- INIT IR --------------------

  receiver = IrReceiverSampler::newIrReceiverSampler(BUFFERSIZE, RECEIVE_PIN);
  receiver->setBeginningTimeout(100);

  // --------------------- PIN MODES ---------------------

  pinMode(L_MOTOR_DIR_PIN, OUTPUT);
  pinMode(L_MOTOR_SPD_PIN, OUTPUT);
  pinMode(R_MOTOR_DIR_PIN, OUTPUT);
  pinMode(R_MOTOR_SPD_PIN, OUTPUT);

  // --------------------- SERVOS ---------------------

  LRServo.attach(ARM_LR_SERVO_PIN);
  UDServo.attach(ARM_UD_SERVO_PIN);
  gripServo.attach(ARM_GRIP_SERVO_PIN);

  gripBall(false);
  pivotArm(101);
  tiltArm(ARM_LOWERED_TILT);

  // --------------------- STOP MOTORS ---------------------

  stopMotors();

  // -------------------- INIT DATA BUFFER --------------------

  for (byte i = 0; i < SERIAL_DATA_LENGTH_BYTES; i++) {
    ser_buf[i] = 0;
  }


}

void loop() {

  // -------------------- READ DATA--------------------

  /*
    while (Serial.peek() != 'I') {
      Serial.read();
    }
    byte dataIn = Serial.readBytes((uint8_t *)ser_buf, SERIAL_DATA_LENGTH_BYTES);
  */

  receiver->receive();

  // -------------------- CHECK DATA--------------------

  //if (dataIn == SERIAL_DATA_LENGTH_BYTES) {

  if (!receiver->isEmpty()) {
    MultiDecoder decoder(*receiver);
    if (decoder.isValid()) {

      char* decodedSignal;
      decodedSignal = decoder.getDecode();

      if (decodedSignal[5] == 'd') return;

      /*
        boolean forward   = ser_buf[1] != '0'; // U = Up
        boolean backwards = ser_buf[2] != '0'; // D = Down
        boolean left      = ser_buf[3] != '0'; // L = Left
        boolean right     = ser_buf[4] != '0'; // R = Right
      */


      // -------------------- DECODE DATA--------------------

      boolean forward   = decodedSignal[7] == '6' && decodedSignal[8] == '9';  // U = Up
      boolean backwards = decodedSignal[7] == '7' && decodedSignal[8] == '0';  // D = Down
      boolean left      = decodedSignal[7] == '7' && decodedSignal[8] == '1';  // L = Left
      boolean right     = decodedSignal[7] == '7' && decodedSignal[8] == '2';  // R = Right
      boolean freeze    = decodedSignal[7] == '1' && decodedSignal[8] == '0';  // Freeze = Stop Motors
      boolean armUp     = decodedSignal[7] == '0' && decodedSignal[8] == NULL; // Ch+ = Arm Up
      boolean armDown   = decodedSignal[7] == '1' && decodedSignal[8] == NULL; // Ch- = Arm Down
      boolean armLeft   = decodedSignal[7] == '2' && decodedSignal[8] == NULL; // Vol+ = Arm Left
      boolean armRight  = decodedSignal[7] == '3' && decodedSignal[8] == NULL; // Vol- = Arm Right
      boolean grip      = (decodedSignal[7] == '2' && decodedSignal[8] == '5') ||
                          (decodedSignal[7] == '6' && decodedSignal[8] == '8');// OK = Grip Ball
      boolean ungrip    = decodedSignal[7] == '8' && decodedSignal[8] == NULL; // Power = Un-Grip Ball

      // -------------------- DRIVING--------------------

      if (forward) {
        drive(FORWARDS);
        delay(50);
      }
      else if (backwards) {
        drive(BACKWARDS);
        delay(50);
      }

      // -------------------- PIVOTING--------------------

      if (left) {
        pivot(LEFT, SMALL_TURN_ANGLE);
      }
      else if (right) {
        pivot(RIGHT, SMALL_TURN_ANGLE);
      }


      // -------------------- ARM MOVEMET--------------------

      if (grip) {
        //gripBall(!isGrippingBall);
        //isGrippingBall = !isGrippingBall;
        //delay(500);
        gripBall(true);
      }
      else if(ungrip) {
        gripBall(false);
      }

      if (armUp) {
        tiltArm(ARM_RAISED_TILT);
      }
      else if (armDown) {
        tiltArm(ARM_LOWERED_TILT);
      }

      if (armLeft) {

      }
      else if (armRight) {

      }

      // -------------------- STOPPING--------------------

      if (freeze || (!forward && !backwards && !left && !right)) {
        stopMotors();
      }

    }
  }
  else {
    stopMotors();
  }

}

// --------------------- BUTTON ---------------------

/*
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
*/
