void descent(){
  //Code runs after apogee has been detected
  Serial.println(F("Running Descent Code..."));

  nextmeasure = millis();
  radiotime = millis();
  landcheck = millis();
  direction = 1; //1 means to open the airbrakes
  movecount = 0;
  finalapproach = 0;
  lastalt = 0;

  //Enter into a loop until landing is detected: 
  while(!landed){

    //Delay until it is time for the next measurement cycle.
    while(millis() <= nextmeasure){
      delay(1);
    }
    //It is now time to take another measurement.
    //Update the nextmeasure time.
    nextmeasure = millis() + LoggingRate;
    //Update and log all the sensors;
    readAll();
    logAll();
    movecount++;
    //Check if we are on final approach;
    if(newalt <= BrakeMinAlt){
      finalapproach = 1;
      servoClose();
    }
    //Check if it is time to move the servo;
    if((movecount >= IdleCount) && (!finalapproach)){
      movecount = 0;
      direction = !direction;
      if(direction){
        servoOpen();
      } else{
        servoClose();
      }
    }
    //Check if it is time to send a radio message;
    if(millis() >= radiotime){
      radiotime = millis() + FlightRadioTime;
      radioPing();
    }
    //If on final approach, start checking for landing;
    if(finalapproach){
      landCheck();
    }
  }
}