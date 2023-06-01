//Libraries
#include <Adafruit_ISM330DHCX.h>
#include <Adafruit_LSM6DS.h>
#include <Adafruit_LSM6DS3.h>
#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LSM6DS3TRC.h>
#include <Adafruit_LSM6DSL.h>
#include <Adafruit_LSM6DSO32.h>
#include <Adafruit_LSM6DSOX.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_SHTC3.h>
#include <SD.h>
#include <SPIMemory.h>
#include <Servo.h>
#include <Adafruit_INA219.h>
#include <Adafruit_MMA8451.h>
#include <Wire.h>
#include <MS5607.h>
#include <EEPROM.h>
#include <HX711.h>
#include <DS1302.h>
#include <RadioLib.h>
#include <FastIMU.h>
#include <Wire.h>
#include <RadioLib.h>

//SCRAP Pin Definitions

//Serial0 is debug/program
//Serial1 is RS485
//Serial2 is the RJ12 port

#define ServoPin PIN_PE3
#define HX711_CLK PIN_PE4
#define RFM_IRQ PIN_PE5
#define Red PIN_PL3
#define Green PIN_PL4
#define Blue PIN_PL5
#define RFM_RST PIN_PL6
#define RFM_CS PIN_PL7
#define SD_CS PIN_PD7
#define HX711_DAT PIN_PF0
#define RTC_CLK PIN_PF1
#define RTC_DAT PIN_PF2
#define RTC_CE PIN_PF3
#define ServoBat PIN_PF4 //Turns on Servo battery
#define ServoUSB PIN_PF5 //Connects USB to servo
#define Switch2 PIN_PF6
#define Switch1 PIN_PF7
#define Port_Mode PIN_PK0 //RS485 Transceiver Mode for RJ12
#define Buzzer PIN_PK1
#define Flash1_CS PIN_PK2
#define Flash2_CS PIN_PK3
#define NTC_Temp PIN_PK4 //Verify this is the NTC
#define Light PIN_PK5 //Light sensor
#define USB_Detect PIN_PK7 //Verify functionality
#define SD_Detect PIN_PA0 //Verify functioanlity
#define Switch4 PIN_PA2
#define RS485_Mode PIN_PA5 //RS485 Transceiver Mode for external JST conneciton

//Objects
HX711 scale;
SPIFlash flash1;
SPIFlash flash2;
DS1302 rtc(RTC_CE, RTC_DAT, RTC_CLK);
Servo servo;
Adafruit_MMA8451 mma = Adafruit_MMA8451();
MS5607 barometer;
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
Adafruit_LIS3MDL lis3mdl;
LSM6DSL IMU;
calData calib = { 0 };  //LSM6DSL Calibration data
AccelData accelData;    //LSM6DSL Sensor data
GyroData gyroData;      //LSM6DSL
MagData magData;        //LSM6DSL
Adafruit_INA219 currentLog(0x45); //INa219 for logical current measurement
Adafruit_INA219 currentServo(0x40); //INA219 for servo current measurements
Adafruit_INA219 currentPass(0x44); //INA219 for COTS passthrough
SX1231 radio = new Module(RFM_CS, RFM_IRQ, RFM_RST);
