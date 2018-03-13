
if(ballLoc = 0) {
  //pivot right 90 degreese 
  pivot(true, 90);

  //drive forward until it reaches the ball 
  driveForwardToBall();   
}

else if (ballLoc = 1) {
  //drive forward until it reaches the ball      
  driveForwardToBall();      
}

else if(ballLoc = 2) {
  //pivot left 90 degreese
  pivot(false, 90);   
  
  //drive forward until it reaches the ball    
  driveForwardToBall();   

}

void driveForwardToBall() {
  //drive forward initially
  drive(true, DRIVE_SPEED);
  while(!needToSlowDownByDistance()) { } //Keep driving unitil reaching slow down distance

  //Set the robot to srive at at slower speed    
  drive(true, SLOW_DRIVE_SPEED); 
  while(!needToStopByDistance()){ } //Keep driving, EXCEPT SLOWER!!!! 

  //Stop the robot under the assumption its right in front of the ball.
  stopMotors();  
}


