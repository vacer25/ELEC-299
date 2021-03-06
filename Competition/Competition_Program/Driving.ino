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

void followLine(int currentSpeed) {
  followLine(currentSpeed, false);
}

void followLine(int currentSpeed, boolean aggressive) {

  // Get the sensor readings
  int leftSensorValue = analogRead(L_LIGHT_SENSOR_PIN);
  int centerSensorValue = analogRead(C_LIGHT_SENSOR_PIN);
  int rightSensorValue = analogRead(R_LIGHT_SENSOR_PIN);

  // If only the middle sensor is over the line, drive forward
  if (centerSensorValue >= LINE_SENSOR_THRESHOLD && leftSensorValue < LINE_SENSOR_THRESHOLD && rightSensorValue < LINE_SENSOR_THRESHOLD) { //forward
    drive(FORWARDS, currentSpeed);
    //DebugPrintln("F");
  }

  // If the right sensor is over the line, turn right
  if (leftSensorValue < LINE_SENSOR_THRESHOLD && rightSensorValue >= LINE_SENSOR_THRESHOLD) {
    turn(RIGHT, currentSpeed, aggressive);
    //DebugPrintln("R");
  }

  // If the left sensor is over the line, turn left
  else if (leftSensorValue >= LINE_SENSOR_THRESHOLD && rightSensorValue < LINE_SENSOR_THRESHOLD) {
    turn(LEFT, currentSpeed, aggressive);
    //DebugPrintln("L");
  }

}

// --------------------- TURNING ---------------------

// Turn by stopping 1 motor
// rightDir: true to pivot right, false to pivot left
void turn(boolean rightDir, int currentSpeed, boolean aggressive) {

  // Set the motors to go forward
  digitalWrite(L_MOTOR_DIR_PIN, HIGH);
  digitalWrite(R_MOTOR_DIR_PIN, HIGH);

  // If turning right, turn the left motor on and right motor off
  if (rightDir) {
    analogWrite(R_MOTOR_SPD_PIN, aggressive ? (currentSpeed / 4) : (currentSpeed / 2));
    analogWrite(L_MOTOR_SPD_PIN, currentSpeed);
  }

  // If turning left, turn the left motor off and right motor on
  else {
    analogWrite(R_MOTOR_SPD_PIN, currentSpeed);
    analogWrite(L_MOTOR_SPD_PIN, aggressive ? (currentSpeed / 4) : (currentSpeed / 2));
  }

}

// --------------------- PIVOTING ---------------------

// Rotates the robot by driving wheels motors in opposite directions
// Does NOT stop at the end of the pivot
// rightDir: true to pivot right, false to pivot left
void pivot(boolean rightDir) {
  // Print debugging info if debugging is globally defined
  DebugPrint("Pivoting ");
  if (rightDir) {
    DebugPrint("right ");
  }
  else {
    DebugPrint("left ");
  }
  //DebugPrint("by: ");
  //DebugPrint(angle);
  //DebugPrint(" degrees. Waiting for: ");
  //DebugPrint(_90_DEGREE_TURN_TIME * (angle / 90.0));
  //DebugPrint(" ms");
  DebugPrintln();

  // Set the left and right motor directions depending on pivot direction
  digitalWrite(L_MOTOR_DIR_PIN, rightDir ? HIGH : LOW);
  digitalWrite(R_MOTOR_DIR_PIN, rightDir ? LOW : HIGH);

  // Start the motors
  analogWrite(L_MOTOR_SPD_PIN, TURN_SPEED);
  analogWrite(R_MOTOR_SPD_PIN, TURN_SPEED);

}

// Rotates the robot by driving wheels motors in opposite directions
// DOES stop at the end of the pivot
// rightDir: true to pivot right, false to pivot left
// angle: angle to pivot by, in degrees
void pivot(boolean rightDir, float angle) {

  pivot(rightDir);

  DebugPrint("Waiting for: ");
  DebugPrint(_90_DEGREE_TURN_TIME * (angle / 90.0));
  DebugPrintln(" ms");
  // Delay for the needed amount of time (relative to 90° turn time)
  delay(_90_DEGREE_TURN_TIME * (angle / 90.0));

  // Stop the motors
  analogWrite(L_MOTOR_SPD_PIN, 0);
  analogWrite(R_MOTOR_SPD_PIN, 0);

}
