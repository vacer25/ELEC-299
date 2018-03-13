// --------------------- LIGHT SENSORS ---------------------

boolean isOverCenterLine() {

  int leftSensorValue = analogRead(leftSensorPin);
  int centerSensorValue = analogRead(centerSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  return leftSensorValue > LINE_SENSOR_THRESHOLD && centerSensorValue > LINE_SENSOR_THRESHOLD && rightSensorValue > LINE_SENSOR_THRESHOLD;
  
}

// --------------------- IR DISTANCE ---------------------

boolean needToSlowDownByDistance() {
  return getFilteredDistance() <= SLOW_DOWN_DISTANCE_READING;
}

boolean needToStopByDistance() {
  return getFilteredDistance() <= STOPPING_DISTANCE_READING;
}
