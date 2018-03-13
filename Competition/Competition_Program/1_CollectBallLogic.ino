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

  // TODO: lowers arm to the height of the ball

  // TODO: grabs the ball, and checks whether it has grip of it

  // TODO: raises the arm with the ball in its grasps

  // Set state to 2 so robot can start deposit ball code.
  state = 2;
}

void driveForwardToBall() {

  // Drive forward initially
  drive(FORWARDS, DRIVE_SPEED);

  // Keep driving unitil reaching slow down distance
  while (!needToSlowDownByDistance()) { }

  // Set the robot to srive at at slower speed
  drive(BACKWARDS, SLOW_DRIVE_SPEED);

  // Keep driving, EXCEPT SLOWER!!!!
  while (!needToStopByDistance()) { }

  // Stop the robot under the assumption its right in front of the ball.
  stopMotors();

}


