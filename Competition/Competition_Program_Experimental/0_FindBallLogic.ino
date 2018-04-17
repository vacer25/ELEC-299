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

      if (isFirstScan) {
        // Scan for ball in center
        if (scanforBall(99, 104)) {
          break;
        }
        isFirstScan = false;
      }

      // Scan for ball on right
      if (scanforBall(175, 180)) {
        break;
      }

      // Scan for ball on left
      if (scanforBall(0, 5)) {
        break;
      }

      if (!isFirstScan) {
        // Scan for ball in center
        if (scanforBall(99, 104)) {
          break;
        }
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

  // Prepare the arm
  setArmToCollectBallState();

  //delay(1000);
  DebugPrint("Done Find Ball Logic, ballLoc = ");
  DebugPrintln(ballLoc);
  state = 1;

}

boolean scanforBall(int startPos, int endPos) {
  // Pivot the arm across the scanning range
  pivotArm(startPos, endPos);
  // Return whether the ball was found
  return (ballLoc != -1);
}

void pivotArm(int startPos, int endPos) {

  unsigned long currentMillis = millis();
  unsigned long waitMillis;

  // Loop through all the angles in the current scan range
  for (int currentLoc = startPos; currentLoc < endPos; currentLoc++) {

    // Set the current arm pivot position
    LRServo.write(currentLoc);

    waitMillis = currentMillis + IR_SENSOR_ARM_MOVE_DWEL_TIME;

    // Wait for some time at this arm location
    while (currentMillis < waitMillis) {

      // Scan the current location for an IR signal
      checkIRSignal();

      // If the ball was found, stop looking for it by breaking out of the loop
      if (ballLoc != -1) {
        break;
      }

      currentMillis = millis();
    }

  }

}

boolean checkIRSignal() {

  // Read the IR signal
  currentIRValue = IRSerial.receive(IR_SENSOR_SCAN_TIMEOUT);

  // If a valid IR signal was found
  if (currentIRValue >= 48 && currentIRValue <= 50) {

    DebugPrint("Detected ball, IR value = ");
    DebugPrintln(currentIRValue);

    // Convert it to the numeric value
    ballLoc = currentIRValue - '0';

    // Indicate that the ball was detected
    return true;
  }

  // Indicate that the ball was NOT detected
  return false;

}
