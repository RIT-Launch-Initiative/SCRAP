//Functions:

void readAll(){
  //Updates all sensor values
  Serial.println(F("Reading Sensors..."));
  newuptime = millis();
  newtime = rtc.time();
  newservo = servo.read();
  newscale = scale.get_units(ScaleCount);
  mma.read();
  newMMAaccx = mma.x;
  newMMAaccy = mma.y;
  newMMAaccz = mma.z;
  sensors_event_t mmaevent; 
  mma.getEvent(&mmaevent);
  newMMAx = mmaevent.acceleration.x;
  newMMAy = mmaevent.acceleration.y;
  newMMAz = mmaevent.acceleration.z;
  neworient = mma.getOrientation();
  newswitch1 = digitalRead(Switch1);
  newswitch2 = digitalRead(Switch2);
  newswitch3 = digitalRead(Switch4);
  newlight = analogRead(Light);
  newNTC = analogRead(NTC_Temp);
  barometer.readDigitalValue();
  newalt = barometer.getAltitude();
  newtemp = barometer.getTemperature();
  newpressure = barometer.getPressure();
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);
  newSHTtemp = temp.temperature;
  newSHThumid = humidity.relative_humidity;
  lis3mdl.read();
  newmagx = lis3mdl.x;
  newmagy = lis3mdl.y;
  newmagz = lis3mdl.z;
  sensors_event_t event; 
  lis3mdl.getEvent(&event);
  newteslax = event.magnetic.x;
  newteslay = event.magnetic.y;
  newteslaz = event.magnetic.z;
  IMU.update();
  IMU.getAccel(&accelData);
  newLSMaccx = accelData.accelX;
  newLSMaccy = accelData.accelY;
  newLSMaccz = accelData.accelZ;
  IMU.getGyro(&gyroData);
  newLSMgyrox = gyroData.gyroX;
  newLSMgyroy = gyroData.gyroY;
  newLSMgyroz = gyroData.gyroZ;
  newUSBdetect = digitalRead(USB_Detect); 
  newSDdetect = digitalRead(SD_Detect);
  newlogvolt = currentLog.getBusVoltage_V();
  newlogmv = currentLog.getShuntVoltage_mV();
  newlogcurrent = currentLog.getCurrent_mA();
  newservovolt = currentServo.getBusVoltage_V();
  newservomv = currentLog.getShuntVoltage_mV();
  newservocurrent = currentServo.getCurrent_mA();
  newpassvolt = currentPass.getBusVoltage_V();
  newpassmv = currentPass.getShuntVoltage_mV();
  newpasscurrent = currentPass.getCurrent_mA();
  logcount = logcount + 1;
  newlogtime = millis() - newuptime;
  Serial.print(F("Sensors Read In: ")); Serial.print(newlogtime); Serial.println(F(" milliseconds."));
}

void printAll(){
  //Prints all current sensor values over Serial0
  unsigned long currentprinttime = millis();
  Serial.print(F("Uptime: ")); Serial.print(newuptime); Serial.println(F(" milliseconds"));
  Serial.print(F("Year: ")); Serial.println(newtime.yr);
  Serial.print(F("Month: ")); Serial.println(newtime.mon);
  Serial.print(F("Day: ")); Serial.println(newtime.date);
  Serial.print(F("Hour: ")); Serial.println(newtime.hr);
  Serial.print(F("Minute: ")); Serial.println(newtime.min);
  Serial.print(F("Second: ")); Serial.println(newtime.sec);
  Serial.print(F("Servo Position: ")); Serial.print(newservo); Serial.println(F(" Degrees"));
  Serial.print(F("Scale Value: ")); Serial.print(newscale); Serial.println(F(" grams"));
  Serial.print(F("MMA8451 Raw Count X: ")); Serial.println(newMMAaccx);
  Serial.print(F("MMA8451 Raw Count Y: ")); Serial.println(newMMAaccy);
  Serial.print(F("MMA8451 Raw Count Z: ")); Serial.println(newMMAaccz);
  Serial.print(F("MMA8451 Acceleration X: ")); Serial.print(newMMAx); Serial.println(F(" m/s^2"));
  Serial.print(F("MMA8451 Acceleration Y: ")); Serial.print(newMMAy); Serial.println(F(" m/s^2"));
  Serial.print(F("MMA8451 Acceleration Z: ")); Serial.print(newMMAz); Serial.println(F(" m/s^2"));
  Serial.print(F("MMA8451 Orientation: ")); Serial.print(neworient); 
  switch (neworient){
    case 0: Serial.println(F(", Portrait Up Front"));
    case 1: Serial.println(F(", Portrait Up Back"));
    case 2: Serial.println(F(", Portrait Down Front"));
    case 3: Serial.println(F(", Portrait Down Back"));
    case 4: Serial.println(F(", Landscape Right Front"));
    case 5: Serial.println(F(", Landscape Right Back"));
    case 6: Serial.println(F(", Landscape Left Front"));
    case 7: Serial.println(F(", Landscape Left Back"));
  }
  Serial.print(F("SABOT Switch 1: ")); Serial.println(newswitch1);
  Serial.print(F("SABOT Switch 2: ")); Serial.println(newswitch2);
  Serial.print(F("SABOT Switch 3: ")); Serial.println(newswitch3);
  Serial.print(F("Phototranistor Output: ")); Serial.println(newlight);
  Serial.print(F("NTC Thermistor Output: ")); Serial.println(newNTC);
  Serial.print(F("MS5607 Altitude: ")); Serial.print(newalt); Serial.println(F(" Meters"));
  Serial.print(F("MS5607 Temperature: ")); Serial.print(newtemp); Serial.println(F(" Degrees Celsius"));
  Serial.print(F("MS5607 Pressure: ")); Serial.print(newpressure); Serial.println(F(" mBar"));
  Serial.print(F("SHTC3 Temperature: ")); Serial.print(newSHTtemp); Serial.println(F(" Degrees Celsius"));
  Serial.print(F("SHTC3 Humidity: ")); Serial.print(newSHThumid); Serial.println(F(" %RH"));
  Serial.print(F("LIS3MDL Raw Count X: ")); Serial.println(newmagx);
  Serial.print(F("LIS3MDL Raw Count Y: ")); Serial.println(newmagy);
  Serial.print(F("LIS3MDL Raw Count Z: ")); Serial.println(newmagz);
  Serial.print(F("LIS3MDL Field X: ")); Serial.print(newteslax); Serial.println(F(" uTesla"));
  Serial.print(F("LIS3MDL Field Y: ")); Serial.print(newteslay); Serial.println(F(" uTesla"));
  Serial.print(F("LIS3MDL Field Z: ")); Serial.print(newteslaz); Serial.println(F(" uTesla"));
  Serial.print(F("LSM6DSL Acceleration X: ")); Serial.print(newLSMaccx); Serial.println(F(" g"));
  Serial.print(F("LSM6DSL Acceleration Y: ")); Serial.print(newLSMaccy); Serial.println(F(" g"));
  Serial.print(F("LSM6DSL Acceleratoin Z: ")); Serial.print(newLSMaccz); Serial.println(F(" g"));
  Serial.print(F("LSM6DSL Gyro X: ")); Serial.print(newLSMgyrox); Serial.println(F(" dps"));
  Serial.print(F("LSM6DSL Gyro Y: ")); Serial.print(newLSMgyroy); Serial.println(F(" dps"));
  Serial.print(F("LSM6DSL Gyro Z: ")); Serial.print(newLSMgyroz); Serial.println(F(" dps"));
  Serial.print(F("USB Detect: ")); Serial.println(newUSBdetect);
  Serial.print(F("SD Card Detect: ")); Serial.println(newSDdetect);
  Serial.print(F("Logical Battery Voltage: ")); Serial.print(newlogvolt); Serial.println(F(" V"));
  Serial.print(F("Logical Battery Shunt: ")); Serial.print(newlogmv); Serial.println(F(" mV"));
  Serial.print(F("Logical Battery Current: ")); Serial.print(newlogcurrent); Serial.println(F(" mA"));
  Serial.print(F("Servo Battery Voltage: ")); Serial.print(newservovolt); Serial.println(F(" V"));
  Serial.print(F("Servo Battery Shunt: ")); Serial.print(newservomv); Serial.println(F(" mV"));
  Serial.print(F("Servo Battery Current: ")); Serial.print(newservocurrent); Serial.println(F(" mA"));
  Serial.print(F("COTS Battery Voltage: ")); Serial.print(newpassvolt); Serial.println(F(" V"));
  Serial.print(F("COTS Battery Shunt: ")); Serial.print(newpassmv); Serial.println(F(" mV"));
  Serial.print(F("COTS Battery Current: ")); Serial.print(newpasscurrent); Serial.println(F(" mA"));
  Serial.print(F("Log Count: ")); Serial.println(logcount);
  Serial.print(F("Log Time: ")); Serial.print(newlogtime); Serial.println(F(" milliseconds"));
  currentprinttime = millis() - currentprinttime;
  Serial.print(F("Data Printed In: ")); Serial.print(currentprinttime); Serial.println(F(" milliseconds"));
}

void logAll(){
  //Stores all sensor data to both memory
  Serial.println(F("Logging Data..."));
  timestore = millis();  
  flash1.writeULong(address, newuptime);
  flash2.writeULong(address, newuptime);
  address += 4;
  flash1.writeWord(address, newtime.yr);
  flash2.writeWord(address, newtime.yr);
  address += 2;
  flash1.writeByte(address, newtime.mon);
  flash2.writeByte(address, newtime.mon);
  address += 1;
  flash1.writeByte(address, newtime.date);
  flash2.writeByte(address, newtime.date);
  address += 1;
  flash1.writeByte(address, newtime.hr);
  flash2.writeByte(address, newtime.hr);
  address += 1;
  flash1.writeByte(address, newtime.min);
  flash2.writeByte(address, newtime.min);
  address += 1;
  flash1.writeByte(address, newtime.sec);
  flash2.writeByte(address, newtime.sec);
  address += 1;
  flash1.writeByte(address, newservo);
  flash2.writeByte(address, newservo);
  address += 1;
  flash1.writeFloat(address, newscale);
  flash2.writeFloat(address, newscale);
  address += 4;
  flash1.writeShort(address, newMMAaccx);
  flash2.writeShort(address, newMMAaccx);
  address += 2;
  flash1.writeShort(address, newMMAaccy);
  flash2.writeShort(address, newMMAaccy);
  address += 2;
  flash1.writeShort(address, newMMAaccz);
  flash2.writeShort(address, newMMAaccz);
  address += 2;
  flash1.writeFloat(address, newMMAx);
  flash2.writeFloat(address, newMMAx);
  address += 4;
  flash1.writeFloat(address, newMMAy);
  flash2.writeFloat(address, newMMAy);
  address += 4;
  flash1.writeFloat(address, newMMAz);
  flash2.writeFloat(address, newMMAz);
  address += 4;
  flash1.writeByte(address, neworient);
  flash2.writeByte(address, neworient);
  address += 1;
  flash1.writeByte(address, newswitch1);
  flash2.writeByte(address, newswitch1);
  address += 1;
  flash1.writeByte(address, newswitch2);
  flash2.writeByte(address, newswitch2);
  address += 1;
  flash1.writeByte(address, newswitch3);
  flash2.writeByte(address, newswitch3);
  address += 1;
  flash1.writeShort(address, newlight);
  flash2.writeShort(address, newlight);
  address += 2;
  flash1.writeShort(address, newNTC);
  flash2.writeShort(address, newNTC);
  address += 2;
  flash1.writeFloat(address, newalt);
  flash2.writeFloat(address, newalt);
  address += 4;
  flash1.writeFloat(address, newtemp);
  flash2.writeFloat(address, newtemp);
  address += 4;
  flash1.writeFloat(address, newpressure);
  flash2.writeFloat(address, newpressure);
  address += 4;
  flash1.writeFloat(address, newSHTtemp);
  flash2.writeFloat(address, newSHTtemp);
  address += 4;
  flash1.writeFloat(address, newSHThumid);
  flash2.writeFloat(address, newSHThumid);
  address += 4;
  flash1.writeShort(address, newmagx);
  flash2.writeShort(address, newmagx);
  address += 2;
  flash1.writeShort(address, newmagy);
  flash2.writeShort(address, newmagy);
  address += 2;
  flash1.writeShort(address, newmagz);
  flash1.writeShort(address, newmagz);
  address += 2;
  flash1.writeFloat(address, newteslax);
  flash2.writeFloat(address, newteslax);
  address += 4;
  flash1.writeFloat(address, newteslay);
  flash2.writeFloat(address, newteslay);
  address += 4;
  flash1.writeFloat(address, newteslaz);
  flash2.writeFloat(address, newteslaz);
  address += 4;
  flash1.writeFloat(address, newLSMaccx);
  flash2.writeFloat(address, newLSMaccx);
  address += 4;
  flash1.writeFloat(address, newLSMaccy);
  flash2.writeFloat(address, newLSMaccy);
  address += 4;
  flash1.writeFloat(address, newLSMaccz);
  flash2.writeFloat(address, newLSMaccz);
  address += 4;
  flash1.writeFloat(address, newLSMgyrox);
  flash2.writeFloat(address, newLSMgyrox);
  address += 4;
  flash1.writeFloat(address, newLSMgyroy);
  flash2.writeFloat(address, newLSMgyroy);
  address += 4;
  flash1.writeFloat(address, newLSMgyroz);
  flash2.writeFloat(address, newLSMgyroz);
  address += 4;
  flash1.writeByte(address, newUSBdetect);
  flash2.writeByte(address, newUSBdetect);
  address += 1;
  flash1.writeByte(address, newSDdetect);
  flash2.writeByte(address, newSDdetect);
  address += 1;
  flash1.writeFloat(address, newlogvolt);
  flash2.writeFloat(address, newlogvolt);
  address += 4;
  flash1.writeFloat(address, newlogmv);
  flash2.writeFloat(address, newlogmv);
  address += 4;
  flash1.writeFloat(address, newlogcurrent);
  flash2.writeFloat(address, newlogcurrent);
  address += 4;
  flash1.writeFloat(address, newservovolt);
  flash2.writeFloat(address, newservovolt);
  address += 4;
  flash1.writeFloat(address, newservomv);
  flash2.writeFloat(address, newservomv);
  address += 4;
  flash1.writeFloat(address, newservocurrent);
  flash2.writeFloat(address, newservocurrent);
  address += 4;
  flash1.writeFloat(address, newpassvolt);
  flash2.writeFloat(address, newpassvolt);
  address += 4;
  flash1.writeFloat(address, newpassmv);
  flash2.writeFloat(address, newpassmv);
  address += 4;
  flash1.writeFloat(address, newpasscurrent);
  flash2.writeFloat(address, newpasscurrent);
  address += 4;
  flash1.writeWord(address, logcount);
  flash2.writeWord(address, logcount);
  address += 2;
  flash1.writeWord(address, newlogtime);
  flash2.writeWord(address, newlogtime);
  address += 2;   
  timestore = millis() - timestore;
  Serial.print(F("Logging Complete. Data Cycle: ")); Serial.println(logcount);
  Serial.print(F("Data Logged In: ")); Serial.print(timestore); Serial.println(F(" milliseconds."));
}

void printSaved(){ 
  //Prints all saved data over serial
  //This will take a long time to implement, and it is also going to be very slow. 
  //So I decided not to implement it. Juse use an SD card.
  Serial.println(F("This is a really dumb idea, and will take hours. Just use an SD card."));
  Serial.println(F("Aborting..."));
}

void dumpSD(){
  //Dumps all flash memory to the connected SD card. Makes one file for each flash memory.
  if(SD.begin(SD_CS)){
    Serial.println(F("SD Card Initialized!"));
  } else{
    Serial.println(F("SD Card Error! Aborting..."));
    return;
  }
  File csv = SD.open("SCRAP_Flash1.csv", FILE_WRITE);
  Serial.println(F("Dumping Flash 1..."));
  if(1){
    //Print a header for the first file
    csv.println("SCRAP Flight Records from Flash Memory 1");
    csv.print("Uptime,Year,Month,Day,Hour,Minute,Second,Servo Position (deg),");
    csv.print("Scale Value (grams),MMA8451 Raw Count X,MMA8451 Raw Count Y,MMA8451 Raw Count Z,");
    csv.print("MMA8451 Acceleration X (m/s^2),MMA8451 Acceleration Y (m/s^2),MMA8451 Acceleration Z (m/s^2),");
    csv.print("MMA8451 Orientation,SABOT Switch 1,SABOT Switch 2,SABOT Switch 3,");
    csv.print("Phototransistor,NTC Thermistor,MS5607 Altitude (meters),MS5607 Temperature (Deg C),");
    csv.print("MS5607 Pressure (mBar),SHTC3 Temperature (Deg C),SHTC3 Humidity (%RH),LIS3MDL Raw Count X,");
    csv.print("LIS3MDL Raw Count Y,LIS3MDL Raw Count Z,LIS3MDL Field X (uTesla),");
    csv.print("LIS3MDL Field Y (uTesla),LIS3MDL Field Z (uTesla),LSM6DSL Acceleration X (g),LSM6DSL Acceleration Y (g),");
    csv.print("LSM6DSL Acceleration Z (g),LSM6DSL Gyro X (dps),LSM6DSL Gyro Y (dps),LSM6DSL Gyro Z (dps),");
    csv.print("USB Detect,SD Card Detect,Logical Battery Voltage (V),Logical Battery Shunt (mV),");
    csv.print("Logical Battery Current (mA),Servo Battery Voltage (V),Servo Battery Shunt (mV),");
    csv.print("Servo Battery Current (mA),COTS Battery Voltage (V),COTS Battery Shunt (mV),");
    csv.println("COTS Battery Current (mA),Log Count,Log Time (ms)");
    csv.flush();
  }  
  datatowrite = 1;
  address = 0;
  while(datatowrite){
    //First check if there is valid data in the next section.
    //This can be verified by reading the uptime.
    //If it is 4,294,967,295, that means that all bits are 1, and that the memory has not been written to
    if(flash1.readULong(address) != 4294967295){
      //Since the firstULong is not max value, this is probably valid data
      csv.print(flash1.readULong(address)); //newuptime
      address += 4;
      csv.print(",");
      csv.print(flash1.readWord(address)); //newtime.yr
      address += 2;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newtime.mon
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newtime.date
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newtime.hr
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newtime.min
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newtime.sec
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newservo
      address += 1;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newscale
      address += 4;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newMMAaccx
      address += 2;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newMMAaccy
      address += 2;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newMMAaccz
      address += 2;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newMMAx
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newMMAy
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newMMAz
      address += 4;
      csv.print(",");
      csv.print(flash1.readByte(address)); //neworient
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newswitch1
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newswitch2
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newswitch3
      address += 1;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newlight
      address += 2;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newNTC
      address += 2;  
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newalt
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newtemp
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newpressure
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newSHTtemp
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newSHThumid
      address += 4;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newmagx
      address += 2;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newmagy
      address += 2;
      csv.print(",");
      csv.print(flash1.readShort(address)); //newmagz
      address += 2;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newteslax
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newteslay
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newteslaz
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMaccx
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMaccy
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMaccz
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMgyrox
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMgyroy
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newLSMgyroz
      address += 4;
      csv.print(flash1.readByte(address)); //newUSBdetect
      address += 1;
      csv.print(",");
      csv.print(flash1.readByte(address)); //newSDdetect
      address += 1;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newlogvolt
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newlogmv
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newlogcurrent
      address +=4 ;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newservovolt
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newservomv
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newservocurrent
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newpassvolt
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newpassmv
      address += 4;
      csv.print(",");
      csv.print(flash1.readFloat(address)); //newpasscurrent
      address += 4;
      csv.print(",");
      csv.print(flash1.readWord(address)); //logcount
      unsigned int tempcount = flash1.readWord(address);      
      address += 2;
      csv.print(",");
      csv.println(flash1.readWord(address)); //newlogtime
      address += 2;
      csv.flush();
      Serial.print(F("Flash 1 Entry Printed: ")); Serial.println(tempcount);
    } else{
      //This is not real data, we are now in empty space. Exit.
      Serial.println(F("Reached End of Flash 1."));
      datatowrite = 0;
      break;
    }
  }
  csv.close();
  File csv2 = SD.open("SCRAP_Flash2.csv", FILE_WRITE);
  Serial.println(F("Dumping Flash 2..."));
  if(1){
    //Print a header for the second file
    csv2.println("SCRAP Flight Records from Flash Memory 2");
    csv2.print("Uptime,Year,Month,Day,Hour,Minute,Second,Servo Position (deg),");
    csv2.print("Scale Value (grams),MMA8451 Raw Count X,MMA8451 Raw Count Y,MMA8451 Raw Count Z,");
    csv2.print("MMA8451 Acceleration X (m/s^2),MMA8451 Acceleration Y (m/s^2),MMA8451 Acceleration Z (m/s^2),");
    csv2.print("MMA8451 Orientation,SABOT Switch 1,SABOT Switch 2,SABOT Switch 3,");
    csv2.print("Phototransistor,NTC Thermistor,MS5607 Altitude (meters),MS5607 Temperature (Deg C),");
    csv2.print("MS5607 Pressure (mBar),SHTC3 Temperature (Deg C),SHTC3 Humidity (%RH),LIS3MDL Raw Count X,");
    csv2.print("LIS3MDL Raw Count Y,LIS3MDL Raw Count Z,LIS3MDL Field X (uTesla),");
    csv2.print("LIS3MDL Field Y (uTesla),LIS3MDL Field Z (uTesla),LSM6DSL Acceleration X (g),LSM6DSL Acceleration Y (g),");
    csv2.print("LSM6DSL Acceleration Z (g),LSM6DSL Gyro X (dps),LSM6DSL Gyro Y (dps),LSM6DSL Gyro Z (dps),");
    csv2.print("USB Detect,SD Card Detect,Logical Battery Voltage (V),Logical Battery Shunt (mV),");
    csv2.print("Logical Battery Current (mA),Servo Battery Voltage (V),Servo Battery Shunt (mV),");
    csv2.print("Servo Battery Current (mA),COTS Battery Voltage (V),COTS Battery Shunt (mV),");
    csv2.println("COTS Battery Current (mA),Log Count,Log Time (ms)");
    csv2.flush();
  }  
  datatowrite = 1;
  address = 0;
  while(datatowrite){
    //First check if there is valid data in the next section.
    //This can be verified by reading the uptime.
    //If it is 4,294,967,295, that means that all bits are 1, and that the memory has not been written to
    if(flash2.readULong(address) != 4294967295){
      //Since the firstULong is not max value, this is probably valid data
      csv2.print(flash2.readULong(address)); //newuptime
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readWord(address)); //newtime.yr
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newtime.mon
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newtime.date
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newtime.hr
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newtime.min
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newtime.sec
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newservo
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newscale
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newMMAaccx
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newMMAaccy
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newMMAaccz
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newMMAx
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newMMAy
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newMMAz
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //neworient
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newswitch1
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newswitch2
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newswitch3
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newlight
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newNTC
      address += 2;  
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newalt
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newtemp
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newpressure
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newSHTtemp
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newSHThumid
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newmagx
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newmagy
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readShort(address)); //newmagz
      address += 2;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newteslax
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newteslay
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newteslaz
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMaccx
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMaccy
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMaccz
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMgyrox
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMgyroy
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newLSMgyroz
      address += 4;
      csv2.print(flash2.readByte(address)); //newUSBdetect
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readByte(address)); //newSDdetect
      address += 1;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newlogvolt
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newlogmv
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newlogcurrent
      address +=4 ;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newservovolt
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newservomv
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newservocurrent
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newpassvolt
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newpassmv
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readFloat(address)); //newpasscurrent
      address += 4;
      csv2.print(",");
      csv2.print(flash2.readWord(address)); //logcount
      unsigned int tempcount = flash1.readWord(address);      
      address += 2;
      csv2.print(",");
      csv2.println(flash2.readWord(address)); //newlogtime
      address += 2;
      csv2.flush();
      Serial.print(F("Flash 2 Entry Printed: ")); Serial.println(tempcount);
    } else{
      //This is not real data, we are now in empty space. Exit.
      Serial.println(F("Reached End of Flash 2."));
      datatowrite = 0;
      break;
    }
  }
  csv2.close();    
}

bool servoOpen(){
  //Moves the servo to the open (max) position, while monitoring the servo current
  //Returns 1 if successful, 0 if failed
  Serial.println(F("Attempting to Open Servo..."));
  for(int i = servo.read(); i < ServoMax; i++){
    servo.write(i);
    if(currentServo.getCurrent_mA() > ServoCurrent){
      servo.write(i-1);
      Serial.println(F("Servo Failure!"));
      return 0;
    }
  }
  Serial.println(F("Servo Success!"));
  return 1;
}

bool servoClose(){
  //Moves the servo to the closed (min) position, while monitoring the servo current
  //Returns 1 if successful, 0 if failed
  Serial.println(F("Attempting to Close Servo..."));
  for(int i = servo.read(); i > ServoMin; i--){
    servo.write(i);
    if(currentServo.getCurrent_mA() > ServoCurrent){
      servo.write(i+1);
      Serial.println(F("Servo Failure!"));
      return 0;
    }
  }
  Serial.println(F("Servo Success!"));
  return 1;
}

void transmitVoltage(){
  //Transmits the voltage of the batteries
  if(RadioOn){
    String transmitvolt;
    transmitvolt = currentLog.getBusVoltage_V();
    transmitvolt += ", ";
    transmitvolt += currentServo.getBusVoltage_V();
    transmitvolt += ", ";
    transmitvolt += currentPass.getBusVoltage_V();
    radio.transmit(transmitvolt);
  }
}

void serialClear(){
  //Clears the serial buffer
  while(Serial.available() != 0){
    Serial.read();
    delay(10);
  }
}

void USBMenu(){
  //The USB menu, entered from the setup. Will stay in this until forced out or disconnect of USB

  analogWrite(Blue, BlueBright);

  Serial.println(F("Entering USB Menu..."));
  helpMenu();

  while(digitalRead(USB_Detect)){
    //Check if there is new serial data:
    if(Serial.available() > 0){

      //c: report current measurements
      if(Serial.peek() == 99){
        serialClear();
        readAll();
        printAll();
      }

      //d: Dump all stored data over serial
      else if(Serial.peek() == 100){
        serialClear();
        printSaved();
      }

      //e: exit the USB menu
      else if(Serial.peek() == 101){
        serialClear();
        Serial.println(F("Menu can only be re-entered by power cycling SCRAP"));
        Serial.println(F("Exiting USB Menu..."));
        goto exitUSB;
      }
      
      //f: erase the flash memory
      else if(Serial.peek() == 102){
        serialClear();
        Serial.println(F("Are you sure? Press y to confirm."));
        while(Serial.available() == 0){};//Wait until something is in serial
        if(Serial.peek() == 121){
          Serial.println(F("Confirmed. Erasing..."));
          flashErase();
          Serial.println(F("Erase Complete"));
        } else{
          Serial.println(F("Erase Aborted!"));                    
        }
        serialClear();
      }

      //h: print help info
      else if(Serial.peek() == 104){
        serialClear();
        helpMenu();        
      }

      //i: print informatioln about SCRAP
      else if(Serial.peek() == 105){
        serialClear();
        credits();        
      }

      //l: print load cell data continuously
      else if(Serial.peek() == 108){
        serialClear();
        Serial.println(F("Printing Load Cell Data. Press Any Key to Exit"));
        while(Serial.available() == 0){
          //Loop until something enters the serial monitor
          delay(loadDemo);
          Serial.println(scale.get_units(10));
        }
        serialClear();
        Serial.println(F("Load Cell Demo Exited"));
      }

      //s: demonstrate the servo continuously
      else if(Serial.peek() == 115){
        serialClear();
        Serial.println(F("Servo Demo. Press Any Key to Exit"));
        while(Serial.available() == 0){
          //Loop until something enters the serial monitor
          delay(servoDemo);
          if(servoClose()){
            Serial.println(F("Airbrake Closed Successfully"));
          } else{
            Serial.println(F("Airbrake Error While Closing!"));
          }
          delay(servoDemo);
          if(servoOpen()){
            Serial.println(F("Airbrake Opened Successfully"));
          } else{
            Serial.println(F("Airbrake Error While Opening!"));
          }
        }
        serialClear();
      }

      //t: returns the current time from the RTC
      else if(Serial.peek() == 116){
        Time t = rtc.time();
        // Format the time and date and insert into the temporary buffer.
        char buf[50];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
          t.yr, t.mon, t.date,
          t.hr, t.min, t.sec);
      }

      //u: Set the time
      else if(Serial.peek() == 117){
        serialClear();
        Serial.println(F("Updating RTC. Change will take effect when all info entered."));
        Serial.println(F("Enter each of the following exactly as shown;"));
        Serial.println(F("Year: XXXX"));
        while(Serial.available() == 1){
          delay(1);
        }
        String incoming = Serial.readString();
        incoming.trim();
        int newYear = incoming.toInt();
        Serial.println(F("Month: XX"));
        while(Serial.available() == 1){
          delay(1);
        }
        incoming = Serial.readString();
        incoming.trim();
        int newMonth = incoming.toInt();
        Serial.println(F("Day: XX"));
        while(Serial.available() == 1){
          delay(1);
        }
        incoming = Serial.readString();
        incoming.trim();
        int newDay = incoming.toInt();
        Serial.println(F("Hour (24hrs): XX"));
        while(Serial.available() == 1){
          delay(1);
        }
        incoming = Serial.readString();
        incoming.trim();
        int newHour = incoming.toInt();
        Serial.println(F("Minute: XX"));
        while(Serial.available() == 1){
          delay(1);
        }
        incoming = Serial.readString();
        incoming.trim();
        int newMinute = incoming.toInt();
        Serial.println(F("Second: XX"));
        while(Serial.available() == 1){
          delay(1);
        }
        incoming = Serial.readString();
        incoming.trim();
        int newSecond = incoming.toInt();
        Serial.println(F("Confirmed. Updating..."));
        Time t(newYear, newMonth, newDay, newHour, newMinute, newSecond, Time::kSunday);
        //The day of the week doesn't matter, always set to Sunday
        rtc.time(t);
        Serial.println(F("RTC Updated."));
        Serial.println(F("RTC time is now..."));
        t = rtc.time();
        // Format the time and date and insert into the temporary buffer.
        char buf[50];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
          t.yr, t.mon, t.date,
          t.hr, t.min, t.sec);
      }

      else{
        serialClear();
        Serial.println(F("Unknown Command!"));
        helpMenu();
      }
    }
  }
  exitUSB:
  analogWrite(Blue, 255);

}

void helpMenu(){
  //Prints a help menu over USB
  Serial.println(F("Accepted Commands (lowercase only):"));
  Serial.println(F("c: Report current measurements"));
  Serial.println(F("d: Dump the stored data over serial"));
  Serial.println(F("e: Exit the USB Menu"));
  Serial.println(F("f: Erase the flash memory"));
  Serial.println(F("h: Print this help menu"));
  Serial.println(F("i: Print infomration about this board"));
  Serial.println(F("l: Continuously report the load cell data"));
  Serial.println(F("s: Continuously demonstrate the servo movement"));
  Serial.println(F("t: Shows's the RTC time"));
  Serial.println(F("u: Sets the RTC's time"));
}

void credits(){
  //Prints credits and information about SCRAP
  Serial.println(F("//-----S.C.R.A.P.-----\\"));
  Serial.println(F("System for Controlling and Recording Airbrake Performance"));
  Serial.println(F("Hardware Version 1.1"));
  Serial.print(F("Software Version "));
  Serial.println(Version);
  Serial.println(F("Designed by Jim Heaney"));
  Serial.println(F("www.jim-heaney.com"));
  Serial.println(F("For the RIT Launch Initiative"));
  Serial.println(F("launch.rit.edu"));
}

void flashErase(){
  //Erases both flash chips
  flash1.eraseChip();
  flash2.eraseChip();
}

void radioPing(){ //TODO
  //Sends a small package of data over the radio, to show the state of the system

  transmitVoltage();
}

void scrubCheck(){
  //Runs a number of checks on the pad to determine if an abort is needed
  readAll();
  scrubreason = 0;
  //Scrub condition 1: Temperature too high
  if((newtemp >= ScrubTemp) || (newSHTtemp >= ScrubTemp)){
    scrubreason = 1;
    Serial.println(F("SCRUB WARN: High Temperature!"));
    Serial.print(F("MS5607: ")); Serial.print(newtemp); Serial.print(F(", SHTC3: ")); Serial.println(newSHTtemp);
  }
  //Scrub condition 2: Logical battery too low
  if(newlogvolt <= ScrubLogic){
    scrubreason = 2;
    Serial.println(F("SCRUB WARN: Logic Battery Low!"));
    Serial.print(F("Battery Voltage: ")); Serial.println(newlogvolt);
  }
  //Scrub condition 3: Servo battery too low
  if(newservovolt <= ScrubServo){
    scrubreason = 3;
    Serial.println(F("SCRUB WARN: Servo Battery Low!"));
    Serial.print(F("Battery Voltage: ")); Serial.println(newservovolt);
  }
  //Scrub condition 4: COTS battery too low
  if(newpassvolt <= ScrubPass){
    scrubreason = 4;
    Serial.println(F("SCRUB WARN: COTS Battery Low!"));
    Serial.print(F("Battery Voltage: ")); Serial.println(newpassvolt);    
  }
  //Scrub condition 5: Sabot switches triggered
  if(ScrubSwitches){
    if((!digitalRead(Switch1)) || (!digitalRead(Switch2)) || (!digitalRead(Switch4))){
      scrubreason = 5;
      Serial.println(F("SCRUB WARN: Sabot Switches!"));
      Serial.print(F("Switch Status: ")); Serial.print(digitalRead(Switch1)); Serial.print(F(", ")); Serial.print(digitalRead(Switch2)); Serial.print(F(", ")); Serial.println(digitalRead(Switch4));    
    }
  }
  //Scrub condition 6: USB Power Detected
  if(ScrubUSB && digitalRead(USB_Detect)){
    scrubreason = 6;
    Serial.println(F("SCRUB WARN: USB POWER!"));    
  }
  //Scrub condition 7: SD Card Detected
  if(ScrubSD && digitalRead(SD_Detect)){
    scrubreason = 7;
    Serial.println(F("SCRUB WARN: SD CARD!"));
  }
}

void launchCheck(){ 
  //Checks the altitude and acceleration to determine if liftoff has occured
  //First, update the accelerometer and the altimeter values. 
  sensors_event_t mmaevent; 
  mma.getEvent(&mmaevent);
  newMMAz = mmaevent.acceleration.z;
  barometer.readDigitalValue();
  newalt = barometer.getAltitude();
  //Next, compare them to the thresholds;
  Serial.print(F("Altitude Change: ")); Serial.print(newalt-groundlevel); Serial.println(F(" meters."));
  Serial.println(F("Acceleration: ")); Serial.print(abs(newMMAz)); Serial.println(F(" m/s"));
  if(((newalt-groundlevel) >= LiftoffAlt) && (abs(newMMAz) >= LiftoffAcc)){
    Serial.println(F("LIFTOFF DETECTED!"));
    launched = 1;    
  }  
}

void apogeeCheck(){
  //Checks to see if apogee has been achieved/past by monitoring a number of sensors.
  //Sensor data will just have been updated, so no need to poll that again.
  //First, see if it is time to check the altitude again.
  apogeechecks = 0; //Reset the apogee checks.
  if(millis() <= alttime){
    alttime = millis() + ApogeeTime;
    if((newalt < lastalt) && (abs(lastalt-newalt) > ApogeeTolerance)){
      //Apogee altitude possibly detected! 
      apogeechecks++;
    }
  }
  //Next, check the switches;
  if(SabotSwitches){
    byte switchcount = 0;
    switchcount += !digitalRead(Switch1);
    switchcount += !digitalRead(Switch2);
    switchcount += !digitalRead(Switch4);  
    if(switchcount == 3){
      //All switches triggered!
      apogeechecks++;
    } else if((!SwitchAll) && (switchcount == 2)){
      //The majority of switches triggered, and that's enough.  
      apogeechecks++;  
    }    
  }
  //Then, check the light sensor;
  if(SabotLight){
    if(analogRead(Light) >= LightOut){
      //Light detected! 
      apogeechecks++;
    }    
  }
  //See if we got enough to pass:
  if(apogeechecks >= ApogeeVote){
    Serial.println(F("APOGEE DETECTED!"));
    atapogee = 1;
  } else{
    Serial.println(F("Apogee Not Detected."));
    Serial.print(F("Apogee Flags: ")); Serial.println(apogeechecks);
  }
}

void landCheck(){
  //Checks if we have landed yet, and updates bool landed.
  //The sensor data should stil be fresh.
  //Check if it is time to update the sensor values;
  if(millis() >= landcheck){
    landcheck = millis() + LandingTime;
    if(abs(newalt - lastalt) <= LandingAlt){
      //Landing Detected.
      Serial.println(F("LANDING DETECTED!"));
      landed = 1;
    } else{
      lastalt = newalt;
      Serial.println(F("Landing Not Detected."));
    }
  }
}
