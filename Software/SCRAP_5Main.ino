void setup() {
  //This is the initialization and startup routine for the system

  //Note the time:
  timestore = millis();
  
  //Start Serial Ports:
  Serial.begin(57600); //USB Serial Output
  Serial.setTimeout(100);
  Serial1.begin(9600); //RS485 Output
  Serial2.begin(9600); //RJ12 RS485 Debug Jack

  //Print the credits;
  credits();

  //PinModes:
  pinMode(Buzzer, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(ServoBat, OUTPUT);
  pinMode(ServoUSB, OUTPUT);

  //Startup Tones and Lights:
  //Bypass these if USB is connected
  if(digitalRead(USB_Detect)){
    Serial.println(F("USB Power Detected, Bypassing Startup Delays, Tones, and Lights."));
    digitalWrite(ServoUSB, HIGH);
    digitalWrite(ServoBat, LOW);
  } else{
    Serial.println(F("USB Power Not Detected, Beginning Normal Startup."));
    digitalWrite(ServoBat, HIGH);
    digitalWrite(ServoUSB, LOW);
     //Beep for a second
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    //Delay startup by 10 seocnds;
    delay(10000);
    //Startup Buzzer & LED:
    digitalWrite(Buzzer, HIGH);
    analogWrite(Red, RedBright);
    delay(10000);
  }

  //Initialize all Peripherals and Sensors:
  if(RadioOn){
    int state = radio.begin();
    if(state == RADIOLIB_ERR_NONE){
      Serial.println(F("GOOD: Radio"));
      radio.transmit("SCRAP: RADIO ONLINE");
      statuslog += "-";
      goodcount++;
    } else{
      Serial.println(F("NO GOOD: Radio"));
      statuslog += "|";
      badcount++;
      Serial.print(F("Error Message: "));
      Serial.println(state);
    }
  }
  //Scale:
  scale.begin(HX711_DAT, HX711_CLK);
  scale.set_scale();
  scale.tare();
  scale.set_scale(LoadScale);
  scale.set_offset(LoadOffset);
  //Need to check if scale is OK another way...
  if(scale.is_ready()){
    Serial.println(F("GOOD: Scale"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: Scale"));
    statuslog += "|";
    badcount++;
  }
  //RTC:
  //No way to see if RTC is enabled properly. Just assume it is working fine.
  rtc.writeProtect(false);
  rtc.halt(false);
  //MMA8451:
  if(mma.begin()){
    Serial.println(F("GOOD: MMA8451"));
    statuslog += "-";
    goodcount++;
    mma.setRange(MMA8451_RANGE_8_G); //8g acceleration range
  } else{
    Serial.println(F("NO GOOD: MMA8451"));
    statuslog += "|";
    badcount++;
  }
  //Servo;
  bool servoUSBflag;
  if(digitalRead(USB_Detect)){
    digitalWrite(ServoUSB, HIGH);
    digitalWrite(ServoBat, LOW);
    Serial.println(F("Servo Power from USB"));
    servoUSBflag = 1;
  } else{
    digitalWrite(ServoUSB, LOW);
    digitalWrite(ServoBat, HIGH);
    Serial.println(F("Servo Power from Bat"));
    servoUSBflag = 0;
  }
  servo.attach(ServoPin);
  servo.write(ServoMin+1); //Set the servo to the minimum position +1 degree
  if(servoClose()){
    Serial.println(F("GOOD: Servo"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: Servo. Retrying..."));
    if(RadioOn){
      radio.transmit("Servo Failed, Retrying...");
    }
    for(int s = 0; s < ServoRetry; s++){
      if(servoClose()){
        Serial.println(F("Servo Retried and OK!"));
        Serial.println(F("GOOD: Servo"));
        statuslog += "-";
        goodcount++;
        break;
      }
      Serial.println(F("Servo Retried and Failed!"));
      Serial.print(F("Retry Number: "));
      Serial.println(s);
      if(s == ServoRetry){
        badcount++;
        statuslog += "|";
        Serial.println(F("NO GOOD: Servo!"));
      }
    }
  }
  //MS5607;
  if(barometer.begin()){
    Serial.println(F("GOOD: MS5607"));
    statuslog += "-";
    goodcount++;
    barometer.setOSR(4096);
  } else{
    Serial.println(F("NO GOOD: MS5607"));
    statuslog += "|";
    badcount++;
  }
  //SHTC3:
  if(shtc3.begin()){
    Serial.println(F("GOOD: SHTC3"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: SHTC3"));
    statuslog += "|";
    badcount++;
  }
  //LIS3MDL:
  if(lis3mdl.begin_I2C()){
    Serial.println(F("GOOD: LIS3MDL"));
    statuslog += "-";
    goodcount++;
    lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
    lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
    lis3mdl.setDataRate(LIS3MDL_DATARATE_80_HZ);
    lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  } else{
    Serial.println(F("NO GOOD: LIS3MDL"));
    statuslog += "|";
    badcount++;
  }
  //LSM6DSL:
  if(IMU.init(calib, 0b1101011)){
    Serial.println(F("GOOD: LSM6DSL"));
    statuslog += "-";
    goodcount++;
    #ifdef PERFORM_CALIBRATION
      Serial.println("FastIMU calibration & data example");
      if (IMU.hasMagnetometer()) {
        delay(1000);
        Serial.println("Move IMU in figure 8 pattern until done.");
        delay(3000);
        IMU.calibrateMag(&calib);
        Serial.println("Magnetic calibration done!");
      }
      else {
        delay(5000);
      }

      delay(5000);
      Serial.println("Keep IMU level.");
      delay(5000);
      IMU.calibrateAccelGyro(&calib);
      Serial.println("Calibration done!");
      Serial.println("Accel biases X/Y/Z: ");
      Serial.print(calib.accelBias[0]);
      Serial.print(", ");
      Serial.print(calib.accelBias[1]);
      Serial.print(", ");
      Serial.println(calib.accelBias[2]);
      Serial.println("Gyro biases X/Y/Z: ");
      Serial.print(calib.gyroBias[0]);
      Serial.print(", ");
      Serial.print(calib.gyroBias[1]);
      Serial.print(", ");
      Serial.println(calib.gyroBias[2]);
      if (IMU.hasMagnetometer()) {
        Serial.println("Mag biases X/Y/Z: ");
        Serial.print(calib.magBias[0]);
        Serial.print(", ");
        Serial.print(calib.magBias[1]);
        Serial.print(", ");
        Serial.println(calib.magBias[2]);
        Serial.println("Mag Scale X/Y/Z: ");
        Serial.print(calib.magScale[0]);
        Serial.print(", ");
        Serial.print(calib.magScale[1]);
        Serial.print(", ");
        Serial.println(calib.magScale[2]);
      }
      delay(5000);
      IMU.init(calib, IMU_ADDRESS);
    #endif
  } else{
    Serial.println(F("NO GOOD: LSM6DSL"));
    statuslog += "|";
    badcount++;
  }
  //INA219s:
  if(currentLog.begin()){
    Serial.println(F("GOOD: INA219 Logic"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: INA219 Logic"));
    statuslog += "|";
  }
  if(currentServo.begin()){
    Serial.println(F("GOOD: INA219 Servo"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: INA219 Servo"));
    statuslog += "|";
    badcount++;
  }
  if(currentPass.begin()){
    Serial.println(F("GOOD: INA219 COTS"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: INA219 COTS"));
    statuslog += "|";
    badcount++;
  }
  //Flash Memory:
  if(flash1.begin()){
    Serial.println(F("GOOD: Flash 1"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: Flash 1"));
    statuslog += "|";
    badcount++;
  }
  if(flash2.begin()){
    Serial.println(F("GOOD: Flash 2"));
    statuslog += "-";
    goodcount++;
  } else{
    Serial.println(F("NO GOOD: Flash 2"));
    statuslog += "|";
    badcount++;
  }

  //Output the good and bad counts:
  Serial.println(F("Initialization Complete."));
  Serial.print(F("Initialized In: ")); Serial.print(millis() - timestore); Serial.println(F(" milliseconds"));
  timestore = millis();
  Serial.print(goodcount); Serial.println(F(" initialized successfully"));
  Serial.print(badcount); Serial.println(F(" not initialized successfully"));
  Serial.println(statuslog);
  if(RadioOn){
    radio.transmit("Initialization Complete:");
    radio.transmit(statuslog);
  }
  byte oldgoodcount = goodcount;
  byte oldbadcount = badcount;

  //Check the battery voltages
  Serial.print(F("Logical Battery: ")); Serial.println(currentLog.getBusVoltage_V());
  if(currentLog.getBusVoltage_V() >= PadLogic){
    Serial.println(F("GOOD: Logical Battery"));
    goodcount++;
    statuslog += "-";
  } else{
    if(currentLog.getBusVoltage_V() <= LandingVolt){
      Serial.println(F("ERROR: Possible bownout detected!"));
      Serial.println(F("Jumping to post-flight..."));
      digitalWrite(Buzzer, LOW);
      analogWrite(Red, OFF);
      landing();
    }
    Serial.println(F("NO GOOD: Logical Battery"));
    badcount++;
    statuslog += "|";
  }
  //Before checking the servo battery, changeover to battery power from USB power. 
  if(servoUSBflag == 1){
    digitalWrite(ServoUSB, LOW);
    digitalWrite(ServoBat, HIGH);
    Serial.println(F("Servo power swapped from USB to Bat"));
  }
  Serial.print(F("Servo Battery: ")); Serial.println(currentServo.getBusVoltage_V());
  if(currentServo.getBusVoltage_V() >= PadServo){
    Serial.println(F("GOOD: Servo Battery"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Servo Battery"));
    badcount++;
    statuslog += "|";
  }
  Serial.print(F("COTS Battery: ")); Serial.println(currentPass.getBusVoltage_V());
  if(currentPass.getBusVoltage_V() >= PadPass){
    Serial.println(F("GOOD: COTS Battery"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: COTS Battery"));
    badcount++;
    statuslog += "|";
  }
  Serial.print(F("Batteries Checked In: ")); Serial.print(millis() - timestore); Serial.println(F(" milliseconds"));
  Serial.print(goodcount - oldgoodcount); Serial.println(F(" batteries GOOD"));
  Serial.print(badcount - oldbadcount); Serial.println(F(" batteries NO GOOD"));
  String voltstring;
  voltstring = currentLog.getBusVoltage_V();
  voltstring += ", ";
  voltstring += currentServo.getBusVoltage_V();
  voltstring += ", ";
  voltstring += currentPass.getBusVoltage_V();
  Serial.println(voltstring);
  if(RadioOn){
    radio.transmit(voltstring);
    radio.transmit(statuslog);
  }

  //Check if there is an SD card and USB power present. If so, dump all data.
  if(digitalRead(USB_Detect) && digitalRead(SD_Detect)){
    timestore = millis();        
    Serial.println(F("Dumping data to SD, standby..."));
    dumpSD();
    Serial.println(F("Data dump to SD complete."));
    Serial.print(F("Time to complete: ")); Serial.print(millis() - timestore); Serial.println(F(" milliseconds"));
    Serial.println(F("Continuing startup..."));
  }

  //USB Menu:
  if(digitalRead(USB_Detect)){
    USBMenu();
  }
  timestore = millis();

  //Make sure there is no longer an SD card
  if(digitalRead(SD_Detect)){
    Serial.println(F("GOOD: SD Card"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: SD Card"));
    badcount++;
    statuslog += "|";
  }

  //Make sure there is no longer a USB connection
  if(digitalRead(USB_Detect)){
    Serial.println(F("GOOD: USB Connection"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: USB Connection"));
    badcount++;
    statuslog += "|";
  }

  //Verify the status of the SABOT detection switches 
  if(digitalRead(Switch1) && digitalRead(Switch2) && digitalRead(Switch4)){
    //All switches are depressed
    Serial.println(F("GOOD: SABOT Switches"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: SABOT Switches"));
    badcount++;
    statuslog += "|";
    if(!digitalRead(Switch1)){
      Serial.println(F("Switch 1 OPEN"));
    }
    if(!digitalRead(Switch2)){
      Serial.println(F("Switch 2 OPEN"));
    }
    if(!digitalRead(Switch4)){
      Serial.println(F("Switch 3 OPEN"));
    }
  }

  //Verify the status of the light detector
  if(analogRead(Light) < LightIn){
    Serial.println(F("GOOD: Light Sensor"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Light Sensor"));
    badcount++;
    statuslog += "|";
  }

  //Take a sensor reading, to verify some values;
  readAll();

  //Check the orientation of the payload using MMA8451
  //Z acceleration should be >0.8g (7.8m/s^2), X/Y <0.2g (1.9m/s^2)
  if((abs(newMMAz) > PadAccOreZ) && (abs(newMMAx) < PadAccOreXY) && (abs(newMMAy) < PadAccOreXY)){
    Serial.println(F("GOOD: Orientation"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Orientation"));
    badcount++;
    statuslog += "|";
  }

  //Check that the payload is not moving
  //Abs of all accelerations should be less than 1.2g (11.8m/s^2)
  if((abs(newMMAz) < PadAccMax) && (abs(newMMAy) < PadAccMax) && (abs(newMMAx) < PadAccMax)){
    Serial.println(F("GOOD: Acceleration"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Acceleration"));
    badcount++;
    statuslog += "|";
  }

  //Check the altitude
  //Altitude should be less than config value
  if(newalt < PadAltMax){
    Serial.println(F("GOOD: Altitude"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Altitude"));
    badcount++;
    statuslog += "|";
  }

  //Check for a change in altitude
  //Delay for config time, check if within config value of last measurement
  float oldalt = newalt;
  delay(PadAltTime);
  readAll();
  if(abs(oldalt -newalt) <= PadAltDelta){
    Serial.println(F("GOOD: Velocity"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Velocity"));
    badcount++;
    statuslog += "|";
  }

  //Check the temperature
  //Value must be below the config value
  Serial.println(F("Temperatures:"));
  Serial.print(F("SHTC3 Detects: ")); Serial.println(newSHTtemp);
  Serial.print(F("MS5607 Detects: ")); Serial.println(newtemp);
  if((newSHTtemp >= PadMaxTemp) || (newtemp >= PadMaxTemp)){
    Serial.println(F("GOOD: Temperature"));
    goodcount++;
    statuslog += "-";
  } else{
    Serial.println(F("NO GOOD: Temperature"));
    badcount++;
    statuslog += "|";
  }

  //Startup Complete; 
  Serial.println(F("Pre-Flight Checks Complete!"));
  Serial.print(F("Completed In: ")); Serial.print(millis() - timestore); Serial.println(F(" milliseconds"));
  Serial.println(F("Final Startup Tallies:"));
  Serial.print(goodcount); Serial.println(F(" GO"));
  Serial.print(badcount); Serial.println(F(" NO GO"));
  Serial.println(statuslog);
  if(badcount == 0){
    //No errors found.
    analogWrite(Red, OFF);
    digitalWrite(Buzzer, LOW);
    Serial.println(F("!-----ALL GREEN! GO FOR FLIGHT!------!"));
    if(RadioOn){
      radio.transmit("ALL GO!");
      radio.transmit(statuslog);
    }
  } else{
    Serial.println(F("!-----ERRORS DETECTED! NO GO!-----!"));
    if(RadioOn){
      radio.transmit("NO GO!");
      radio.transmit(statuslog);
    }
    digitalWrite(Buzzer, LOW);
    analogWrite(Red, OFF);
    delay(1000);
    for(int j = 0; j <= badcount; j++){
      //Buzz once for each error found
      analogWrite(Red, RedBright);
      digitalWrite(Buzzer, HIGH);
      delay(1000);
      analogWrite(Red, OFF);
      digitalWrite(Buzzer, LOW);
      delay(1000);
    }
  }

  //Indicate the end of the startup test by sounding the buzzer 10 more seconds
  digitalWrite(Buzzer, HIGH);
  analogWrite(Green, GreenBright);
  delay(10000);
  digitalWrite(Buzzer, LOW);
  analogWrite(Green, OFF);


  //Rest of the flight is handled in functions:
  preFlight();
  ascent();
  descent();
  landing();
}

void loop() {
  //There's no loop in this program!
  //If you ever hit this, something has gone very wrong.
  Serial.println(F("CRITICAL ERROR: Fell through to loop()"));
  while(1){
    delay(1000);
  }
}