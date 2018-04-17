void runCollectBallLogic() {

  DebugPrintln("Collecting ball...");

  if (ballLoc == 0) {
    //delay(1000);
    DebugPrintln("Pivoting 90 degrees right...");
    // Pivot right 90 degreese towards ball
    pivot(RIGHT);
    while (centerIsOverLine()) {
      /* Wait for center to move off of the line */
    }
    delay(_90_TURN_IGNORE_LINE_FOLLOW_TIME);
    while (!centerIsOverLine()) {
      /* Wait for center to move on to the line */
    }
  }
  else if (ballLoc == 2) {
    //delay(1000);
    DebugPrintln("Pivoting 90 degrees left...");
    // Pivot left 90 degreece towards ball
    pivot(LEFT);
    while (centerIsOverLine()) {
      /* Wait for center to move off of the line */
    }
    delay(_90_TURN_IGNORE_LINE_FOLLOW_TIME);
    while (!centerIsOverLine()) {
      /* Wait for center to move on to the line */
    }
  }

  //delay(1000);
  DebugPrintln("Driving towards ball...");
  // Drive forward until it reaches the ball
  driveForwardToBall();

  //delay(1000);
  DebugPrintln("Lowering arm...");
  // Lower arm to the height of the ball
  tiltArm(ARM_LOWERED_TILT);

  //delay(1000);
  DebugPrintln("Gripping ball...");
  // Grabs the ball
  // TODO: Check whether it has grip of it
  gripBall(true);

  //delay(1000);
  DebugPrintln("Raising arm...");
  // Raise the arm with the ball in its grip
  tiltArm(ARM_RAISED_TILT);

  //delay(1000);
  DebugPrintln("Done Collect Ball Logic!");
  // Set state to 2 so robot can start the deposit ball code
  state = 2;

}

void driveForwardToBall() {

  // If the robot is fully not over the line, the line following will not work
  while (isFullyNotOverLine()) {
    // Drive forward until one if the sensors are over the line
    drive(FORWARDS, SLOW_DRIVE_SPEED);
  }
  stopMotors();

  // while the bumper switch is not hit
  while (digitalRead(BUMPER_PIN) != LOW) {
    // Keep following the line
    followLine(LINE_FOLLOW_SPEED);
  }

  // At this point the robot has hit the wall, stop the motors
  stopMotors();

  // Small delay for the robot to come to a complete stop
  delay(100);

  DebugPrintln("Backing up from wall...");
  drive(BACKWARDS, SLOW_DRIVE_SPEED);

  // Wait for the robot to back up
  delay(BACKUP_FROM_WALL_TIME);
  // Stop the motors once backed up
  stopMotors();

}


