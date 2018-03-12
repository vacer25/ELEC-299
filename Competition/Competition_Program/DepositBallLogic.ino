void goToCenter() {

  // Drive backwards at full speed
  drive(BACKWARDS, DRIVE_SPEED);

  while(!isOverCenterLine) { // Keep driving }

  // Stop once all the light sensors are over the center line
  stopMotors();

  // Drive forwards to position the robots's center in the playfield center
  drive(FORWARDS, DRIVE_SPEED);

  // Delay for enough time to get the robots's center in the playfield center
  delay(SHORT_DRIVE_TO_CENTER_TIME);

  // Once the robots's center in the playfield center, stop
  stopMotors();
  
}

