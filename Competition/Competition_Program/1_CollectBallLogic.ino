void runCollectBallLogic() {

  if (ballLoc == 0) {
    // Pivot right 90 degreese towards ball
    pivot(RIGHT, 90);
  }
  else if (ballLoc == 2) {
    // Pivot left 90 degreese towards ball
    pivot(LEFT, 90);
  }

  // Drive forward until it reaches the ball
  driveForwardToBall();

  // Lower arm to the height of the ball
  lowerArm();

  // Grabs the ball,
  // TODO: Check whether it has grip of it
  gripBall(true);

  // Raise the arm with the ball in its grip
  raiseArm();

  // Set state to 2 so robot can start the deposit ball code
  state = 2;

}

void driveForwardToBall() {

  // Follow the line leading to the ball until reaching slow down distance
  while (!needToSlowDownByDistance()) {
    followLine(DRIVE_SPEED);
  }

  // Follow the line leading to the ball at at slower speed until reaching stopping distance
  while (!needToStopByDistance()) {
    followLine(SLOW_DRIVE_SPEED);
  }

  // Stop the robot under the assumption its right in front of the ball
  stopMotors();

}


