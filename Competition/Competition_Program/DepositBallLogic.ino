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
    followLine()
  } while(!isFullyOverLine());

  // At this point the robot has reached the deposit code, so stop it
  stopMotors();
  
  // TODO: make the ball drop and the robot return to center

}



/*

  // This is an old idea that will probably remain unused
  void goToCenter() {

  // Drive backwards at full speed
  drive(BACKWARDS, DRIVE_SPEED);

  while(!isFullyOverLine()) {
    // Keep driving
  }

  // Stop once all the light sensors are over the center line
  stopMotors();

  // Drive forwards to position the robots's center in the playfield center
  drive(FORWARDS, DRIVE_SPEED);

  // Delay for enough time to get the robots's center in the playfield center
  delay(SHORT_DRIVE_TO_CENTER_TIME);

  // Once the robots's center in the playfield center, stop
  stopMotors();

  }

*/
