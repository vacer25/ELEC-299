void runFindBallLogic() {

  DebugPrintln("Finding ball...");

  if (simulatedBallLocation != -1) {
    ballLoc = simulatedBallLocation;
#ifdef SIMULATED_BALL_LOCATION_INCREMENT
    simulatedBallLocation++;
    if (simulatedBallLocation > 2) {
      simulatedBallLocation = 0;
    }
#endif
    DebugPrint("Simulated ball location was: ");  DebugPrintln(ballLoc);
  }
  else {

    // Set arm tilt to look at IR sensor
    tiltArm(ARM_IR_SENSE_TILT);

    // Keep scanning for the ball while it is not found
    do {

      // Scan for ball in center
      if (scanforBall(99, 104)) {
        break;
      }

      // Scan for ball on left
      if (scanforBall(0, 5)) {
        break;
      }

      // Scan for ball on right
      if (scanforBall(175, 180)) {
        break;
      }

    } while (ballLoc == -1);

    // If the ball it not forward or left, it it right
    //if (ballLoc == -1) {
    //  ballLoc = 0;
    //}

  }
  // At this point the ball has been found

  // Set the LED indicators to display the current ball location
  digitalWrite(INDICATOR_LED_1_PIN, (ballLoc == 0) || (ballLoc == 2));
  digitalWrite(INDICATOR_LED_2_PIN, (ballLoc == 1) || (ballLoc == 2));

  //delay(1000);
  DebugPrintln("Moving arm forward...");
  pivotArm(101);

  //delay(1000);
  DebugPrintln("Opening ball gripper...");
  // Open the ball gripper
  gripBall(false);

  //delay(1000);
  DebugPrintln("Raising arm...");
  tiltArm(ARM_RAISED_TILT);

  //delay(1000);
  DebugPrint("Done Find Ball Logic, ballLoc = ");
  DebugPrintln(ballLoc);
  state = 1;

}

boolean scanforBall(int startPos, int endPos) {
  pivotArm(startPos, endPos);
  return (ballLoc != -1);
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

    DebugPrint("Detected ball, IR value = ");
    DebugPrintln(currentIRValue);

    ballLoc = currentIRValue - '0';
  }

}
