boolean needToSlowDownByDistance() {
  return getFilteredDistance() <= SLOW_DOWN_DISTANCE_READING;
}

boolean needToStopByDistance() {
  return getFilteredDistance() <= STOPPING_DISTANCE_READING;
}
