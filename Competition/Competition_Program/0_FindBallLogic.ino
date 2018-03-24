void runFindBallLogic() {

  DebugPrintln("Finding ball...");

  if (SIMULATED_BALL_LOCATION != 0) {
    ballLoc = SIMULATED_BALL_LOCATION;
    state = 1;
    DebugPrint("Simulated ball location was: ");  DebugPrintln(ballLoc);
  }
  else {

    // Set arm tilt to look at IR sensor
    tiltArm(ARM_IR_SENSE_TILT);

    // While the ball is not found
    //while (state == 0) {

    // Look in range of 99-106
    //if (armPos == ARM_CENTER_PAN) {
    pivotArm(99, 104);
    //armPos = ARM_LEFT_PAN;
    //}

    // Look in range of 0-10
    //else if (armPos == ARM_LEFT_PAN) {
    if (state == 0) {
      pivotArm(0, 10);
    }
    //armPos = ARM_RIGHT_PAN;
    //}

    // If the ball it not forward or left, it it right
    if (state == 0) {
      ballLoc = 0;
      state = 1;
    }

    /*
      // Look in range of 99-106
      else if (armPos == ARM_RIGHT_PAN) {
      pivotSearchArm(175, 180);
      armPos = ARM_CENTER_PAN;
      }
    */

  }

  delay(1000);
  DebugPrintln("Moving arm forward...");
  pivotArm(101);

  delay(1000);
  DebugPrintln("Opening ball gripper...");
  // Open the ball gripper
  gripBall(false);

  delay(1000);
  DebugPrintln("Raising arm...");
  tiltArm(ARM_RAISED_TILT);

}

void pivotArm(int pos) {
  LRServo.write(pos);
}

void pivotArm(int startPos, int endPos) {

  unsigned long currentMillis = millis();
  unsigned long waitMillis;

  for (int currentLoc = startPos; currentLoc < endPos; currentLoc++) {

    LRServo.write(currentLoc);

    waitMillis = currentMillis + IR_SENSOR_ARM_MOVE_DWEL_TIME;

    while (currentMillis < waitMillis) {
      checkIRSignal();
      currentMillis = millis();
    }

  }

}

void checkIRSignal() {

  currentIRValue = IRSerial.receive(IR_SENSOR_SCAN_TIMEOUT);

  if (currentIRValue >= 48 && currentIRValue <= 50) {
    ballLoc = currentIRValue - 48;
    state = 1;
  }

}
