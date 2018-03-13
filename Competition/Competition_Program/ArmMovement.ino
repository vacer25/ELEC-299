// --------------------- ARM MOVEMENT ---------------------

void gripBall(boolean grip) {

  if (gripBall) {
    gripServo.write(GRIP_CLOSE_ANGLE);
  }
  else {
    gripServo.write(GRIP_OPEN_ANGLE);
  }

}
