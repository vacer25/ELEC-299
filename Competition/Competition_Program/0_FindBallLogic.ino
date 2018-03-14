void runFindBallLogic() {

  // Set arm tilt to look at IR sensor
  tiltArm(ARM_IR_SENSE_TILT);

  // While the ball is not found
  while (state == 0) {

    // Look in range of 0-10
    if (armPos == ARM_LEFT_PAN) {
      pivotSearchArm(0, 10);
      armPos = ARM_CENTER_PAN;
    }

    // Look in range of 99-106
    else if (armPos == ARM_CENTER_PAN) {
      pivotSearchArm(99, 104);
      armPos = ARM_LEFT_PAN;
    }

  }

}

void pivotSearchArm(int startPos, int endPos) {

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
