//Variables and Constants

//"new..." varaibles used to store the most recent sensor readings
Time newtime = rtc.time(); //Stores the time from the RTC on each sensor read
unsigned long newuptime; //millis
byte newservo; //servo position
float newscale; //scale in grams
int newMMAaccx; //MMA8451 X count
int newMMAaccy; //MMA8451 Y count
int newMMAaccz; //MMA8451 Z count
float newMMAx; //MMA8451 X acceleration
float newMMAy; //MMA8451 Y acceleration
float newMMAz; //MMA8451 Z acceleration
byte neworient; //MMA8451 orientation
bool newswitch1; //SABOT switch 1
bool newswitch2; //SABOT switch 2
bool newswitch3; //SAbot switch 3
int newlight; //ADC value of light sensor
int newNTC; //NTC thermistor
double newalt; //MS5607 altitude
double newtemp; //MS5607 temperature
double newpressure; //MS5607 pressure
float newSHTtemp; //SHTC3 temperature
float newSHThumid; //SHTC3 humidity
int newmagx; //LIS3MDL raw count X
int newmagy; // ...y
int newmagz; // ...z
float newteslax; //LIS3MDL uTesa x
float newteslay; // ...y
float newteslaz; // ...z
float newLSMaccx; //LSM6DSL acceleration X
float newLSMaccy; // ...y
float newLSMaccz; // ...z
float newLSMgyrox; //LSM6DSL gyro x
float newLSMgyroy; // ...y
float newLSMgyroz; // ...z
bool newUSBdetect;
bool newSDdetect;
float newlogvolt;
float newlogmv;
float newlogcurrent;
float newservovolt;
float newservomv;
float newservocurrent;
float newpassvolt;
float newpassmv;
float newpasscurrent;
unsigned int newlogtime; //How long it took to log the data

unsigned int logcount; //stores the number of times dat has been logged

byte goodcount;
byte badcount;
String statuslog; //Stores - or | to show if objects are initialized properly or not

unsigned long timestore; //Stores time for calculating how long things took to complete.

//Data Logging and Dumping:
unsigned long address; //Stores the current position in the flash memory;
bool datatowrite; //Keeps track of if there is valid data to print still

//Scrub:
byte scrubreason; //Stores an error code associated with what caused a scrub.
bool scrubbing; //1 if a scrub condition has been detected, to accelerate re-checks
bool scrubbed; //1 if a scrub is locked in.
byte oldscrubreason; //Stores the last error code for a scrub
byte scrubcounter; //Increments when a scrub is detected
byte unscrubcount; //Counts how many times a nominal check has occured

//Pre-Flight:
bool launched = 0; //Turns to 1 once launch is detected
unsigned long logtime; //Used to determine when to take another measurement
unsigned long scrubtime; //Determine when to check for scrub next
unsigned long groundtime; //Time when to update the ground altitude
unsigned long radiotime; //Time when to send another radio message
bool groundupdate; //Stores a value to show if it is time to apply an old ground altitude update;
float groundlevel; //Stores the measured ground level for detecting liftoff
float newgroundlevel; //Stores a new ground level to account for drift over time on the pad
unsigned long liftofftime; //Stores when liftoff is detected.

//Ascent:
unsigned long nextmeasure; //Stores the time when the next measurement should be taken. 
bool atapogee; //1 once apogee has been achieved
float lastalt; //Stores the last altitude measurement. If the new one is lower than that, we passed apogee.
unsigned long alttime; //Stores the time of when apogee should next be checked.
byte apogeechecks; //Stores how many of the apogee flags have been triggered

//Descent
bool direction; //Tracks which direction to move the airbrakes
byte movecount; //Tracks how many measurement cycles have passed, and if it is time to move the airbrakes. 
bool finalapproach; //Determines if we are close to the ground.
bool landed; //Determines if we have landed or not yet.
unsigned long landcheck; //Stores the time when the landing is next checked.

//Landing
unsigned long nextbuzzer; //Tracks when the buzzer is next toggled
unsigned long nextLED; //Tracks when the LED is next toggled