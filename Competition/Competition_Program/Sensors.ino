// --------------------- LIGHT SENSORS ---------------------

boolean needToFollowLine() {

  // Get the sensor readings
  int leftSensorValue = analogRead(L_LIGHT_SENSOR_PIN);
  int rightSensorValue = analogRead(R_LIGHT_SENSOR_PIN);

  // If the ball was at location 0, the robot is approaching the middle line from the left so the right sensor will detect the line first
  if (ballLoc == 0 && rightSensorValue > LINE_SENSOR_THRESHOLD) return true;

  // If the ball was at location 1, the robot is approaching the middle line from center, so it it goes off track, any sensor may detect the line first
  if (ballLoc == 1 && (leftSensorValue > LINE_SENSOR_THRESHOLD || rightSensorValue > LINE_SENSOR_THRESHOLD)) return true;

  // If the ball was at location 2, the robot is approaching the middle line from the right so the left sensor will detect the line first
  if (ballLoc == 2 && leftSensorValue > LINE_SENSOR_THRESHOLD) return true;

  //By default, return false
  return false;

}

// Return true when all 3 light sensors are over a line
boolean isFullyOverLine() {

  // Get the sensor readings
  int leftSensorValue = analogRead(L_LIGHT_SENSOR_PIN);
  int centerSensorValue = analogRead(C_LIGHT_SENSOR_PIN);
  int rightSensorValue = analogRead(R_LIGHT_SENSOR_PIN);

  // Return true when  all 3 light sensors reading are >= the threshold
  return leftSensorValue >= LINE_SENSOR_THRESHOLD && centerSensorValue >= LINE_SENSOR_THRESHOLD && rightSensorValue >= LINE_SENSOR_THRESHOLD;

}

// Return true when the center light sensors is over a line
boolean centerIsOverLine() {

  // Get the sensor readings
  int centerSensorValue = analogRead(C_LIGHT_SENSOR_PIN);

  // Return true when  all 3 light sensors reading are >= the threshold
  return centerSensorValue >= LINE_SENSOR_THRESHOLD;

}

// --------------------- IR DISTANCE ---------------------

/*
// Returns true when the robot is close enough to the wall to slow down to approach the ball
boolean needToSlowDownByDistance() {
  // Update the distance filter
  distanceFilter.updateFilteredDistance(analogRead(DISTANCE_SENSOR_PIN));

  //DebugPrint("Distance reading (slow): ");
  //DebugPrintln(distanceFilter.getFilteredDistance());

  return distanceFilter.getFilteredDistance() >= SLOW_DOWN_DISTANCE_READING;
}

// Returns true when the robot is close enough to the wall to stop and grip the ball
boolean needToStopByDistance() {
  // Update the distance filter
  distanceFilter.updateFilteredDistance(analogRead(DISTANCE_SENSOR_PIN));

  //DebugPrint("Distance reading (stop): ");
  //DebugPrintln(distanceFilter.getFilteredDistance());

  return distanceFilter.getFilteredDistance() >= STOPPING_DISTANCE_READING;
}
*/
