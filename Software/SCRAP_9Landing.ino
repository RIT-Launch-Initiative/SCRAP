void landing(){
  //Code runs after landing is detected
  Serial.println(F("Running Post-Landing Code..."));

  nextmeasure = millis();
  radiotime = millis();
  nextbuzzer = millis();
  nextLED = millis();

  //Power down the servo, to preserve battery
  digitalWrite(ServoBat, LOW);
  digitalWrite(ServoUSB, LOW);
  servo.detach();

  //Go into a loop forever;
  while(1){
    //Check if it is time to take a measurement and there is still space;
    if((millis() >= nextmeasure) && (address <= MaxLog)){
      nextmeasure = millis() + LandingRate;
      readAll();
      logAll();
    }
    //See if it is time to toggle on the buzzer or LED:
    if(millis() >= nextbuzzer){
      digitalWrite(Buzzer, HIGH);
      delay(LandingBuzzerOn);
      digitalWrite(Buzzer, LOW);
      nextbuzzer = millis() + LandingBuzzer;
    }
    if((millis() >= nextLED) && (LEDOn)){
      analogWrite(Red, LandingBright);
      delay(LandingLEDOn);
      analogWrite(Red, OFF);
      nextLED = millis() + LandingLED;
    }
    //Check if it is time to send a radio message
    if((RadioOn) && (RadioMinVolt <= currentLog.getBusVoltage_V()) && (millis() >= radiotime)){
      radiotime = millis() + LandRadioTime;
      radioPing();
    }
  }
}