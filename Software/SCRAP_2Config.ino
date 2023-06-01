//SCRAP Configuration

//General:
  //General settings, also Used to debug and test SCRAP
  #define Verbose 1 //(Currently Does Nothing) Should: If 1, sends serial messages as code is executing for insight.
  #define RedBright 150 //Red LED Brightness, 0 is full, 255 is off
  #define GreenBright 150 //Green LED Brightness, 0 is full, 255 is off
  #define BlueBright 150 //Blue LED Brightness, 0 is full, 255 is off
  #define OFF 255 //Value to turn LEDs to when "off". 255 default. 
  #define loadDemo 100 //A delay between load cell values when printed over USB in demo mode
  #define servoDemo 500 //How long the servo stays at each position to demonstrate function
  #define Version "1.1.1" //The version of the software

//Radio Settings:
  //Used to configure radio
  #define RadioOn 1 //Turns on/off radio
  #define PadRadio 1 //Enables/disables the radio while waiting on the pad
  #define LandingRadio 1 //Enables/disables the radio after landing
  #define PadRadioTime 10000 //Time between radio messages on the pad, in millis
  #define FlightRadioTime 2000 //Time between radio messages in flight, in millis
  #define LandRadioTime 60000 //Time between radio messages after landing, in millis
  #define RadioMinVolt 3.5 //Below this voltage, the radio will not be turned on.

//Pad Checks:
  //Sets go/no-go on the pad checked on the initial power-on
  #define ServoRetry 10 //The number of times the servo is attempted to re-initialize before giving up.
  #define PadLogic 4.0 //Minimum voltage when on the pad for the logical battery
  #define PadServo 8.0 //Minimum voltage when on the pad for the servo battery
  #define PadPass 4.0 //Minimum voltage when on the pad for the COTS battery
  #define PadAccOreZ 7.8 //Minimum Z axis acceleration allowed to determine orientation, in m/s^2
  #define PadAccOreXY 2.0 //Maximum XY axis accleration allowed to determine orientation, in m/s^2
  #define PadAccMax 11.8 //Maximum acceleration measured in any axis, in m/2^2.
  #define PadAltMax 1500 //Maximum altitude of the launch pad, ASL in meters. 
  #define PadAltDelta 2 //Maximum change in altitude over time allowed, in meters
  #define PadAltTime 10000 //Time that the pad altitude is checked over, in milliseconds
  #define PadMaxTemp 70.0 //Maximum temperature, in Deg C, can detect on startup

//Pre-Flight Checks:
  //Sets scrub conditions on the pad between initial power-on and liftoff.
  #define ScrubLogic 3.7 //Minimum voltage of logical battery
  #define ScrubServo 7.4 //Minimum voltage of servo battery
  #define ScrubPass 3.8 //Minimum voltage of COTS battery
  #define ScrubTemp 75.0 //Maximum temperature, in Deg C
  #define ScrubUSB 1 //Triggers scrub if USB is re-connected
  #define ScrubSD 1 //Triggers scrub if SD card is inserted
  #define ScrubSwitches 1 //If 1, a scrub is triggered if the SABOT switches toggle on the pad
  #define ScrubLock 1 //If 1, a scrub sets the system into a low-power safety mode. 0 keeps normal operation. Disables scrub reversing
  #define ScrubAlarm 1 //If 1, a buzzer is sounded when a scrub occurs
  #define ScrubRate 5000 //How often to check for a scrub, in milliseconds
  #define ScrubReRate 1000 //How often to check successive scubs, after a first fail condition is found
  #define ScrubCount 3 //How many successive scrubs need to be detected from the same source before officially calling it
  #define ScrubReverse 1 //If 1, scrubs can be revered if values return to normal
  #define ScrubReverseCount 10 //If ScrubReverse is 1, this is how many successive polls need to pass to "un-scrub"

//Liftoff Thresholds: 
  //Sets the acceleration and change in altitude thresholds to detect liftoff;
  //Both need to be satisfied
  #define GroundUpdate 10000 //How often the ground level is updated, in millis
  #define LiftoffAlt 120 //in meters above ground
  #define LiftoffAcc 18 //in m/s^2 

//Landing Thresholds:
  //Used to determine when landing has occured, altitude cannot change more than an amount over time;
  #define LandingAlt 2.0 //in meters
  #define LandingTime 5000 //in milliseconds

//Apogee Detection:
  //Determines what sensors, and at what intensity, are used to detect apogee/release;
  #define ApogeeVote 3 //How many of the apogee checks need to pass to be considered a success.
  #define AscentTime 40000 //The time it is estimated to take to get to apogee. All operations locked out until after this time. In millis.
  #define ApogeeTolerance 1.5 //How much the altitude needs to be dropping over time to count as post-apogee
  #define ApogeeTime 2000 //How frequently to check altitude to see if we are post-apogee
  #define SabotSwitches 1 //1 uses the switches for the Sabot detection
  #define SwitchAll 1 //If 0, the majority of switches need to detect SABOT opening. If 1, all must detect.
  #define SabotLight 1 //1 uses the light sensor to see if out of sabot
  #define LightIn 100 //At or below this value means the SABOT is covering the light senspr
  #define LightOut 200 //At or above this value means the SABOT is not covering the light sensor

//Logging Settings:
  //Configures what data is stored, how often, and in what format;
  #define LoggingRate 50 //in millis, time between logging of data in flight
  #define PadLog 1 //1 logs data on the pad pre-flight
  #define PadRate 10000 //in millis, time between logging of data on the pad pre-flight
  #define LandingLog 1 //1 logs data after landing
  #define LandingRate 10000 //in millis, time between logging of data on the ground post-flight
  #define MaxLog 15999860 //the maximum address for logging. Once this is hit, and after landing, the system will stop logging.

//Landing Settings:
  //Determines operation post-landing
  #define BuzzerOn 1 //(Currently Does Nothing) Should: 1 turns on the buzzer for power-up and post-landing operation.
  #define LandingBuzzer 10000 //milliseconds between buzzes on the ground
  #define LandingBuzzerOn 200 //milliseconds the buzzer is on for
  #define LEDOn 0 //1 sets the LED to blink after landing, same interval/time as buzzer
  #define LandingLED 10000 //milliseconds between flashes on the ground
  #define LandingLEDOn 50 //milliseocnds the LED is on for
  #define LandingBright 0 //the brightness of the LED on landing, 0 is max, 255 is off.
  #define LandingVolt 3.5 //If powered on at or below this voltage, assume there was a brownout and you are actually post-flight landed

//Airbrake Settings:
  //Configures the operation of the servo and airbrakes;
  #define ServoMin 0 //The starting position of the servo, i.e. leaves fully closed
  #define ServoMax 170 //The maximum position of the servo, i.e. leaves fully open
  #define ServoCurrent 600 //The maximum current, in mA, the servo can draw. Beyond this is considered a stall/stop
  #define IdleCount 10 //How many measurement cycles to stay in the same position while executing the experiment.
  #define BrakeMinAlt 1600 //Altitude, in meters ASL, where the airbrakes are closed and locked for landing. Also where landing checks start.

//Calibration Settings:
  //Used to calibrate multiple sensors, such as the load cells
  #define ScaleCount 10 //How many samples are taken by the load cell and averages together
  #define LoadOffset 1 //Offset from 0 grams of the load cell
  #define LoadScale 1 //Scaling factor of load cell results
  