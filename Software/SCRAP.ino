/*

S.C.R.A.P. - System for Controlling and Recording Airbrake Performance

SCRAP is a custom control board developed for the 2023 RIT Launch Initiative payload, ANNE. It performs a number
of important tasks, most notably running the airbrake experiment. It also performs a number of secondary tasks
related to data logging, live telemetry, and recovery assistance.

SCRAP and this code was developed by Jim Heaney.

This version of the code, V1.1.1, is developed for hardware version 1.1.

Directory:
* 1LibsPinsObjs: Lists all libraries, the pin definitions, and creates all objects
* 2Config: Contains a number of #defines used to set the operating mode of SCRAP
* 3ConstVars: All of the global constant and variables are defined here
* 4Functions: General-use functions
* 5Main: Contains the setup (initialization) and loop (unused) functions
* 6PreFlight: Function that runs until liftoff is detected
* 7Flight: Function that runs during flight
* 8PostFlight: Function that runs after landing is detected

*/

/*

TODO: 
* Check the polarity of:
  * USB Servo Toggle, Battery Servo Toggle
  * SABOT Switches
  * USB Detect, SD Detect
* Get baselines on the SCRAP light sensor, figure out which way it goes as it gets brighter.
* Add radio messages for critical events.
* Go through and append together radio messages to send all at once.

*/