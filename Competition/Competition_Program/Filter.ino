float Q = 0.000001;
float R = 0.0001;
float P = 1, X = 0, K;

//public KalmanFilter() {
//P = 1.0f;
//X = 0.0f;
//K = 0.0f;
//}

void measurementUpdate() {
  K = (P + Q) / (P + Q + R);
  P = R * (P + Q) / (R + P + Q);
}

float setFilteredDistance(float value) {
  X = value;
}

float getFilteredDistance() {
  return X;
}

float updateFilteredDistance(float value) {

  measurementUpdate();
  float result = X + (value - X) * K;
  X = result;

  return result;

}


