// --------------------- ARM MOVEMENT ---------------------

void gripBall(boolean grip) {

  if (gripBall) {
    gripServo.write(GRIP_CLOSE_ANGLE);
    delay(GRIP_CLOSE_WAIT_TIME);
  }
  else {
    gripServo.write(GRIP_OPEN_ANGLE);
    delay(GRIP_OPEN_WAIT_TIME);
  }

}

void raiseArm() {
  UDServo.write(ARM_RAISED_ANGLE);
  delay(ARM_RAISE_WAIT_TIME);
}

void lowerArm() {
  UDServo.write(ARM_LOWERED_ANGLE);
  delay(ARM_LOWER_WAIT_TIME);
}

