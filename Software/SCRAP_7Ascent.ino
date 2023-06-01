void ascent(){
  //Liftoff has been detected, this code runs on ascent. 
  Serial.println(F("Running Ascent Code..."));

  nextmeasure = millis();
  radiotime = millis();
  alttime = millis();
  lastalt = groundlevel;

  //Stay in a loop until apogee is detected;
  while(!atapogee){

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
    //Check if it is time to start looking for apogee;
    if(millis() >= (liftofftime + AscentTime)){
      //It is past the lockout, check for apogee. 
      apogeeCheck();
    }
    //Send a radio transmission:
    if((RadioOn) && (millis() >= radiotime)){
      //It is time to send another radio message.
      radiotime = millis() + FlightRadioTime;
      radioPing();
    }
  }
  //Now that apogee is detected...
  if(RadioOn){
    String tempstring;
    tempstring += "APOGEE Alt: ";
    tempstring += lastalt;
    tempstring += " m.";
    radio.transmit(tempstring);
  }
  //Now go on to descent...
}