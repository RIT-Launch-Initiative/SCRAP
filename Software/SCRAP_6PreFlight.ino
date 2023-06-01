void preFlight(){
  //This code runs from after initialization until launch is detected
  Serial.println(F("Running PreFlight Code..."));

  logtime = millis();
  scrubtime = millis();
  groundtime = millis();
  radiotime = millis();
  barometer.readDigitalValue();
  newgroundlevel = barometer.getAltitude();
  groundlevel = barometer.getAltitude();
  scrubbed = 0;

  while(!launched){
      
    //Every X seconds, log data;
    if(logtime <= millis()){
      logtime = millis() + PadRate;
      readAll();
      logAll();
    }

    //Every X seconds, send a radio message;
    if(radiotime <= millis()){
      radiotime = millis() + PadRadioTime;
      radioPing();
    }

    //Every loop, check for liftoff;
    launchCheck();
    if(launched){
      //Bypass all the other checks
      return;
    }

    //Every X seconds, update the ground altitude;
    if(groundtime <= millis()){
      groundtime = millis() + (GroundUpdate/2);
      groundupdate = !groundupdate;
      if(groundupdate){
        //Grab the altitude
        barometer.readDigitalValue();
        newgroundlevel = barometer.getAltitude();
      } else{
        //Update the altitude if launch stil hasn't been detected
        groundlevel = newgroundlevel;
        Serial.print(F("New Ground Level Established: ")); Serial.print(groundlevel); Serial.println(F(" meters."));
      }
    }

    //Every X seconds, check for a scrub;
    if(scrubtime <= millis()){
      if(!scrubbed){
        //A scrub has not been detected, operate as normal.
        if(scrubbing){
          //If a scrub trigger is detected, poll faster
          scrubtime = millis() + ScrubReRate;
        } else{
          scrubtime = millis() + ScrubRate;
        }
        scrubCheck();
        if(scrubreason != 0){
          //Scrub anomaly detected
          if(scrubreason == oldscrubreason){
            scrubcounter++;
            scrubbing = 1;
            Serial.print(F("Scrub Count: ")); Serial.println(scrubcounter);
          } else{
            Serial.println(F("Switching Scrub Reason, Resetting..."));
            oldscrubreason = scrubreason;
            scrubcounter = 0;
          }
        } else{
          Serial.println(F("Scrub Checks OK!"));
          scrubcounter = 0;
          oldscrubreason = 0;
          scrubbing = 0;
        }
        if(scrubcounter >= ScrubCount){
          scrubbed = 1;
          Serial.println(F("SCRUB COUNT EXCEEDED! SCRUBBING!"));   
        }
        if(ScrubLock && scrubbed){
          Serial.println(F("Entering Scrub Lockdown."));
          analogWrite(Red, RedBright);
          while(1){
            digitalWrite(Buzzer, HIGH);
            delay(100);
            digitalWrite(Buzzer, LOW);
            delay(1000);
          }
        }
      }
      if(scrubbed){
        //A scrub has been detected in the past, and we now need to un-scrub
        digitalWrite(Buzzer, HIGH);
        scrubtime = millis() + ScrubReRate;
        scrubCheck();
        if(scrubreason == 0){
          unscrubcount++;
          Serial.print(F("UnScrub Counter: ")); Serial.println(unscrubcount);
        } else{
          unscrubcount = 0;
        }
        if(unscrubcount >= ScrubReverseCount){
          Serial.println(F("UNSCRUB THRESHOLD MET!"));
          scrubbed = 0;
          digitalWrite(Buzzer, LOW);
        }
      }
    }
  }
}
