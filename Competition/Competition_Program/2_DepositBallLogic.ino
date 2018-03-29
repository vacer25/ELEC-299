void runDepositBallLogic() {

  // If the ball was not straigh ahead, need to do some turning
  if (ballLoc != 1) {

    // Back up from the wall
    drive(BACKWARDS, SLOW_DRIVE_SPEED);
    // Wait for the robot to back up
    delay(BACKUP_FROM_WALL_TIME);
    // Stop the motors once backed up
    stopMotors();

    DebugPrintln("Turning towards deposit point...");
    // Turn diagonally towards the deposit point
    if (ballLoc == 0) { // Ball was on the right of the deposit point
      pivot(RIGHT, 90 + DIAGONAL_1_TURN_ANGLE);
    }
    else if (ballLoc == 2) { // Ball was on the left of the deposit point
      pivot(LEFT, 90 + DIAGONAL_1_TURN_ANGLE);
    }

    DebugPrintln("Driving towards deposit point while ignoring line following...");
    // Drive forwards towards the deposit point
    drive(FORWARDS, DRIVE_SPEED);

    // Delay for enough time to for the robot to get past the right or left line so it does not try to follow them
    delay(SIDE_IGNORE_LINE_FOLLOW_TIME);

    // Keep driving forward while the robot did not reach the middle line
    while (!needToFollowLine()) {
      /* Keep driving */
    }

  }
  // If ball was straight ahead, need to do a 180
  else {

    DebugPrintln("Turning towards center...");
    // Turn towards the center
    pivot(RIGHT);
    while (centerIsOverLine()) {
      /* Wait for center to move off of the line */
    }
    delay(_180_TURN_IGNORE_LINE_FOLLOW_TIME);
    while (!centerIsOverLine()) {
      /* Wait for center to move on to the line */
    }
    stopMotors();

    // If the ball was in the center location, the robot just crossed the center cross and needs to drive over it before following the line
    // Keep following the line while the robot is not over the center cross
    do {
      followLine(LINE_FOLLOW_SPEED);
    } while (!isFullyOverLine());

    // Wait a little for the robot to drive past the center point
    delay(CENTER_IGNORE_DROP_BALL_TIME);

  }

  if (ballLoc == 0) {
    DebugPrintln("Pivoting 45 degrees left...");
    // Pivot left towards deposit point
    pivot(LEFT, DIAGONAL_2_TURN_ANGLE);
  }
  else if (ballLoc == 2) {
    DebugPrintln("Pivoting 45 degrees right...");
    // Pivot right towards deposit point
    pivot(RIGHT, DIAGONAL_2_TURN_ANGLE);
  }

  DebugPrintln("Reached line, following it towards deposit point...");
  // Start following the middle line until all 3 light sensors are over the deposit line
  do {
    followLine(LINE_FOLLOW_SPEED, true);
  } while (!isFullyOverLine());

  DebugPrintln("Reached deposit point...");
  // At this point the robot has reached the deposit point, so stop it
  stopMotors();

  DebugPrintln("Dropping the ball...");
  // Drop the ball
  gripBall(false);

  DebugPrintln("Backing up from deposit point...");
  drive(BACKWARDS, DRIVE_SPEED);

  // Wait for the robot to back up
  delay(BACKUP_FROM_DEPOSIT_TIME);

  // Stop the motors once backed up
  stopMotors();

  DebugPrintln("Turning towards center...");
  // Turn towards the center
  pivot(RIGHT);
  delay(_180_TURN_IGNORE_LINE_FOLLOW_TIME);
  while (!centerIsOverLine()) {
    /* Wait for center to move on to the line */
  }
  stopMotors();

  DebugPrintln("Lowering arm...");
  // Lower the arm so that the IR scanning works when the robot returns to center
  tiltArm(ARM_IR_SENSE_ANGLE);

  //delay(1000);
  DebugPrintln("Folloing line to center...");
  // Start following the middle line until all 3 light sensors are over the center line
  do {
    followLine(LINE_FOLLOW_SPEED);
  } while (!isFullyOverLine());

  DebugPrintln("Light sensors are over center, adjusting...");
  // At this point the light sensorsa are over the center
  stopMotors();

  // Drive a little more forward so the center of the robot is over the center of the playfield
  drive(FORWARDS, DRIVE_SPEED);

  // Wait for the robot to be over the center of the playfield
  delay(DRIVE_TO_CENTER_ADJUST_TIME);

  //delay(1000);
  DebugPrintln("Reached center, stopping...");
  // At this point the robot has reached the center, so stop it
  stopMotors();

  // Reset the ball position
  ballLoc = -1;

  // Set the LED indicators to display no ball location
  digitalWrite(INDICATOR_LED_1_PIN, LOW);
  digitalWrite(INDICATOR_LED_2_PIN, LOW);

  //delay(1000);
  DebugPrintln("Done Deposit Ball Logic!");
  // Set state to 0 so robot can start the find ball code
  state = 0;

}
