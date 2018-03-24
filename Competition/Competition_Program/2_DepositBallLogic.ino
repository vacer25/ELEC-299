void runDepositBallLogic() {

  // Turn towards the center
  pivot(RIGHT, 180);

  // Drive forwards towards the center point
  drive(FORWARDS, DRIVE_SPEED);

  // If the ball was not straigh ahead, need to do some turning
  if (ballLoc != 1) {

    // Delay for enough time to for the robot to get 1/2 way towards the center
    delay(DRIVE_TO_HALF_CENTER_TIME);

    // Turn diagonally towards the deposit point
    if (ballLoc == 0) { // Ball was on the right of the deposit point
      pivot(LEFT, DIAGONAL_TURN_ANGLE);
    }
    else if (ballLoc == 2) { // Ball was on the left of the deposit point
      pivot(RIGHT, DIAGONAL_TURN_ANGLE);
    }

    // Drive forwards towards the deposit point
    drive(FORWARDS, DRIVE_SPEED);

    // Delay for enough time to for the robot to get past the right or left line so it does not try to follow them
    delay(DRIVE_IGNORING_LINE_FOLLOW_TIME);

  }

  // Drive forwards towards the deposit point
  drive(FORWARDS, DRIVE_SPEED);

  // Keep driving forward while the robot did not reach the middle line
  while (!needToFollowLine()) {
    /* Keep driving */
  }

  // Start following the middle line until all 3 light sensors are over the deposit line
  do {
    followLine(LINE_FOLLOW_SPEED);
  } while (!isFullyOverLine());

  // At this point the robot has reached the deposit point, so stop it
  stopMotors();

  // Drop the ball
  gripBall(false);

  // Turn towards the center
  pivot(RIGHT, 180);

  // Lower the arm so that the IR scanning works when the robot returns to center
  tiltArm(ARM_LOWERED_TILT);

  // Start following the middle line until all 3 light sensors are over the center line
  do {
    followLine(LINE_FOLLOW_SPEED);
  } while (!isFullyOverLine());

  // At this point the robot has reached the center, so stop it
  stopMotors();

  // Set state to 0 so robot can start the find ball code
  state = 0;

}
