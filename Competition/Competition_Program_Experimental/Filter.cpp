#include "Arduino.h"
#include "Filter.h"

Filter::Filter() {}

void Filter::measurementUpdate(float value) {

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = value;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

}

float Filter::setFilteredDistance(float value) {

  total = 0;
  readIndex = 0;
  average = value;
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = value;
    total += value;
  }
  
}

float Filter::getFilteredDistance() {
  return average;
}

float Filter::updateFilteredDistance(float value) {
  measurementUpdate(value);
  return average;
}

/*
Filter::Filter() {
  P = 1.0f;
  X = 0.0f;
  K = 0.0f;
}

void Filter::measurementUpdate() {
	K = (P + Q) / (P + Q + R);
	P = R * (P + Q) / (R + P + Q);
}

float Filter::setFilteredDistance(float value) {
	X = value;
}

float Filter::getFilteredDistance() {
	return X;
}

float Filter::updateFilteredDistance(float value) {

	measurementUpdate();
	float result = X + (value - X) * K;
	X = result;
	
	return result;

}
*/


