void runCollectBallLogic() {

  DebugPrintln("Collecting ball...");

  if (ballLoc == 0) {
    delay(1000);
    DebugPrintln("Pivoting 90 degrees right...");
    // Pivot right 90 degreese towards ball
    pivot(RIGHT, 90);
  }
  else if (ballLoc == 2) {
    delay(1000);
    DebugPrintln("Pivoting 90 degrees left...");
    // Pivot left 90 degreese towards ball
    pivot(LEFT, 90);
  }

  delay(1000);
  DebugPrintln("Driving towards ball...");
  // Drive forward until it reaches the ball
  driveForwardToBall();

  delay(1000);
  DebugPrintln("Lowering arm...");
  // Lower arm to the height of the ball
  tiltArm(ARM_LOWERED_TILT);

  delay(1000);
  DebugPrintln("Gripping ball...");
  // Grabs the ball
  // TODO: Check whether it has grip of it
  gripBall(true);

  delay(1000);
  DebugPrintln("Raising arm...");
  // Raise the arm with the ball in its grip
  tiltArm(ARM_RAISED_TILT);

  // Set state to 2 so robot can start the deposit ball code
  state = 2;

}

void driveForwardToBall() {

  // Follow the line leading to the ball until reaching slow down distance
  while (!needToSlowDownByDistance()) {
    followLine(LINE_FOLLOW_SPEED);
  }
  
  delay(1000);
  DebugPrintln("Reached the slow driving threshold, will follow line slowly...");
  // Follow the line leading to the ball at at slower speed until reaching stopping distance
  while (!needToStopByDistance()) {
    followLine(SLOW_DRIVE_SPEED);
  }
  
  delay(1000);
  DebugPrintln("Reached the stop threshold, stopping motors...");
  // Stop the robot under the assumption its right in front of the ball
  stopMotors();

}


