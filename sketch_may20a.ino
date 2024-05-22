/******************************************************************************
  Example1_BasicReadings.ino
  Example for the TMP117 I2C Temperature Sensor
  Madison Chodikov @ SparkFun Electronics
  May 29 2019
  ~

  This sketch configures the TMP117 temperature sensor and prints the
  temperature in degrees celsius and fahrenheit with a 500ms delay for
  easier readings. 

  Resources:
  Wire.h (included with Arduino IDE)
  SparkFunTMP117.h (included in the src folder) http://librarymanager/All#SparkFun_TMP117

  Development environment specifics:
  Arduino 1.8.9+
  Hardware Version 1.0.0

  This code is beerware; if you see me (or any other SparkFun employee) at
  the local, and you've found our code helpful, please buy us a round!

  Distributed as-is; no warranty is given.
******************************************************************************/

/*
  NOTE: For the most accurate readings:
  - Avoid heavy bypass traffic on the I2C bus
  - Use the highest available communication speeds
  - Use the minimal supply voltage acceptable for the system
  - Place device horizontally and out of any airflow when storing
  For more information on reaching the most accurate readings from the sensor,
  reference the "Precise Temperature Measurements with TMP116" datasheet that is
  linked on Page 35 of the TMP117's datasheet
*/

// #include <Wire.h>            // Used to establish serial communication on the I2C bus
// #include <SparkFun_TMP117.h> // Used to send and recieve specific information from our sensor
// #include <SparkFun_I2C_Mux_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux

// //The default address of the device is 0x70 = (MAIN)
// QWIICMUX myMux;

// // The default address of the device is 0x48 = (GND)
// TMP117 sensor; // Initalize sensor

// void setup()
// {
//   Wire.begin();
  
//   Serial.begin(115200);    // Start serial communication at 115200 baud
//   Wire.setClock(400000);   // Set clock speed to be the fastest for better communication (fast mode)


//   if (myMux.begin() == false)
//   {
//     Serial.println("Mux not detected. Freezing...");
//     while (1)
//       ;
//   }
//   Serial.println("Mux detected");

//   myMux.setPort(0); //Connect master to port labeled '1' on the mux

//   byte currentPortNumber = myMux.getPort();
//   Serial.print("CurrentPort: ");
//   Serial.println(currentPortNumber);


//   if (sensor.begin() == true) // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
//   {
//     Serial.println("Begin");
//   }
//   else
//   {
//     Serial.println("Device failed to setup- Freezing code.");
//     while (1); // Runs forever
//   }
// }

// void loop()
// {


//   Serial.println();

//   byte nDevices = 0;
//   for (byte address = 1; address < 127; address++)
//   {
//     Wire.beginTransmission(address);
//     byte error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address < 0x10)
//         Serial.print("0");
//       Serial.print(address, HEX);
//       Serial.println();

//       nDevices++;
//     }
//     else if (error == 4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address < 0x10)
//         Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }

//   if (nDevices == 0)
//     Serial.println("No I2C devices found");
//   else
//     Serial.println("Done");



//   // Data Ready is a flag for the conversion modes - in continous conversion the dataReady flag should always be high
//   if (sensor.dataReady() == true) // Function to make sure that there is data ready to be printed, only prints temperature values when data is ready
//   {
//     float tempC = sensor.readTempC();
//     float tempF = sensor.readTempF();
//     // Print temperature in °C and °F
//     Serial.println(); // Create a white space for easier viewing
//     Serial.print("Temperature in Celsius: ");
//     Serial.println(tempC);
//     Serial.print("Temperature in Fahrenheit: ");
//     Serial.println(tempF);
//     delay(15000); // Delay added for easier readings
//   }
// }


// /* Pro Micro Test Code
//    by: Nathan Seidle
//    modified by: Jim Lindblom
//    SparkFun Electronics
//    date: September 16, 2013
//    license: Public Domain - please use this code however you'd like.
//    It's provided as a learning tool.

//    This code is provided to show how to control the SparkFun
//    ProMicro's TX and RX LEDs within a sketch. It also serves
//    to explain the difference between Serial.print() and
//    Serial1.print().
// */

// // int RXLED = 17;  // The RX LED has a defined Arduino pin
// // // Note: The TX LED was not so lucky, we'll need to use pre-defined
// // // macros (TXLED1, TXLED0) to control that.
// // // (We could use the same macros for the RX LED too -- RXLED1,
// // //  and RXLED0.)

// // void setup()
// // {
// //   pinMode(RXLED, OUTPUT);  // Set RX LED as an output
// //   // TX LED is set as an output behind the scenes

// //   Serial.begin(9600); //This pipes to the serial monitor
// //   Serial.println("Initialize Serial Monitor");

// //   Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
// //   Serial1.println("Initialize Serial Hardware UART Pins");
// // }

// // void loop()
// // {
// //   Serial.println("Hello world!");  // Print "Hello World" to the Serial Monitor
// //   Serial1.println("Hello! Can anybody hear me?");  // Print "Hello!" over hardware UART

// //   digitalWrite(RXLED, LOW);   // set the RX LED ON
// //   TXLED0; //TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
// //   delay(15000);              // wait for a second

// //   digitalWrite(RXLED, HIGH);    // set the RX LED OFF
// //   TXLED1; //TX LED macro to turn LED ON
// //   delay(15000);              // wait for a second
// // }

// /*
//   Use the Qwiic Mux to access multiple I2C devices on seperate busses.
//   By: Nathan Seidle @ SparkFun Electronics
//   Date: May 17th, 2020
//   License: This code is public domain but you buy me a beer if you use this
//   and we meet someday (Beerware license).

//   Some I2C devices respond to only one I2C address. This can be a problem
//   when you want to hook multiple of a device to the I2C bus. An I2C Mux
//   solves this issue by allowing you to change the 'channel' or port that
//   the master is talking to.

//   This example shows how to connect to different ports.
//   The TCA9548A is a mux. This means when you enableMuxPort(2) then the SDA and SCL lines of the master (Arduino)
//   are connected to port 2. Whatever I2C traffic you do, such as distanceSensor.startRanging() will be communicated to whatever
//   sensor you have on port 2.

//   Hardware Connections:
//   Attach the Qwiic Mux Shield to your RedBoard or Uno.
//   Plug a device into port 0 or 1
//   Serial.print it out at 115200 baud to serial monitor.

//   SparkFun labored with love to create this code. Feel like supporting open
//   source? Buy a board from SparkFun!
//   https://www.sparkfun.com/products/14685
// */

// #include <Wire.h>

// #include <SparkFun_I2C_Mux_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux
// QWIICMUX myMux;

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("Qwiic Mux Shield Read Example");

//   Wire.begin();

//   if (myMux.begin() == false)
//   {
//     Serial.println("Mux not detected. Freezing...");
//     while (1)
//       ;
//   }
//   Serial.println("Mux detected");

//   myMux.setPort(1); //Connect master to port labeled '1' on the mux

//   byte currentPortNumber = myMux.getPort();
//   Serial.print("CurrentPort: ");
//   Serial.println(currentPortNumber);

//   Serial.println("Begin scanning for I2C devices");
// }

// void loop()
// {
//   Serial.println();

//   byte nDevices = 0;
//   for (byte address = 1; address < 127; address++)
//   {
//     Wire.beginTransmission(address);
//     byte error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address < 0x10)
//         Serial.print("0");
//       Serial.print(address, HEX);
//       Serial.println();

//       nDevices++;
//     }
//     else if (error == 4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address < 0x10)
//         Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }

//   if (nDevices == 0)
//     Serial.println("No I2C devices found");
//   else
//     Serial.println("Done");

//   delay(15000);
// }

/*
  Reading CO2 and temperature from the STC3x
  By: Paul Clark
  Based on earlier code by: Nathan Seidle
  SparkFun Electronics
  Date: June 11th, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/18385

  This example prints the current CO2 concentration (%) and temperature in C.

  Hardware Connections:
  Attach RedBoard to computer using a USB cable.
  Connect STC31 to RedBoard using Qwiic cable.
  Open Serial Monitor at 115200 baud.
*/

#include <Wire.h>

#include "SparkFun_STC3x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_STC3x
STC3x mySensor;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("STC3x Example"));
  Wire.begin();

  //mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

  if (mySensor.begin() == false)
  {
    Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
    while (1)
      ;
  }

  //We need to tell the sensor what binary gas and full range we are using
  //Possible values are:
  //  STC3X_BINARY_GAS_CO2_N2_100   : Set binary gas to CO2 in N2.  Range: 0 to 100 vol%
  //  STC3X_BINARY_GAS_CO2_AIR_100  : Set binary gas to CO2 in Air. Range: 0 to 100 vol%
  //  STC3X_BINARY_GAS_CO2_N2_25    : Set binary gas to CO2 in N2.  Range: 0 to 25 vol%
  //  STC3X_BINARY_GAS_CO2_AIR_25   : Set binary gas to CO2 in Air. Range: 0 to 25 vol%

  if (mySensor.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25) == false)
  {
    Serial.println(F("Could not set the binary gas! Freezing..."));
    while (1)
      ;
  }
}

void loop()
{
  if (mySensor.measureGasConcentration()) // measureGasConcentration will return true when fresh data is available
  {
    Serial.println();

    Serial.print(F("CO2(%):"));
    Serial.print(mySensor.getCO2(), 2);

    Serial.print(F("\tTemperature(C):"));
    Serial.print(mySensor.getTemperature(), 2);

    Serial.println();
  }
  else
    Serial.print(F("."));

  delay(500);
}


