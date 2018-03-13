runCollectBallLogic() {
  
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
  
  //lowers arm to the height of the ball
  UDServo.attach(9);           //attach USDervo to UD Arm pin

  //Real Jank solution to issue, will look into later  
  int i = 0;
  while(i < 120) { 
    UDServo.write(10);
  }

 
  //This code grabs the ball, and checks whether it has grip of it 
  
  //raises the arm with the ball in its grasps 
  
  //set state to 2 so robot can start deposit ball code. 
  state = 2;
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


