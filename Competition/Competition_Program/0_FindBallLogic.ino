void runFindBallLogic() {

  // While the ball is not found
  while (state == 0) {

    // Look in range of 0-10
    if (armPos == ARM_POS_1) {
      pivotSearchArm(0, 10);
      armPos = ARM_POS_2;
    }

    // Look in range of 99-106
    else if (armPos == ARM_POS_2) {
      pivotSearchArm(99, 104);
      armPos = ARM_POS_1;
    }

  }

}

void pivotSearchArm(int start, int end) {

  unsigned long currentMillis = millis();
  unsigned long waitMillis;

  for (int currentLoc = start; currentLoc < end; currentLoc++) {

    LRServo.write(currentLoc);

    waitMillis = currentMillis + IR_SENSOR_ARM_MOVE_DWEL_TIME;

    while (currentMillis < waitMillis) {
      checkIRSignal();
      currentMillis = millis();
    }

  }

}

void checkIRSignal() {

  currentIRValue = myIRserial.receive(IR_SENSOR_SCAN_TIMEOUT);

  if (currentIRValue >= 48 && currentIRValue <= 50) {
    ballLoc = currentIRValue - 48;
    state = 1;
  }

}
