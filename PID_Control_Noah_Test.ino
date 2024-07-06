
#include <math.h>
#include <SPI.h>
#include <Wire.h>
#include <SparkFunTMP102.h>


// Sensors
TMP102 sensor0;

// Time inits
float time1, time2, deltaTime;

void setup() {

  Serial.begin(9600);
  Wire.begin();

  sensor0.begin();  // TMP102

  time2 = millis();  // Set initial time to startup

}


// PID Constants 
const float kP = 2, kI = .5, kD = 5;       // Random so far
const float targetTemp = 30;              // Celsius 
const float minTemp = 20, maxTemp = 35;   // Note sure of these

// Initial Values
float pidError, pidP, pidI, pidD, pidOutput;
float prevError = 0;
float deltaError;
float integral = 0;

void loop() {

  // Error 
  float tempReading = sensor0.readTempC();
  pidError = targetTemp - tempReading;

  // Proportion
  pidP = kP * pidError;

  // Integral
  pidI = pidI  + (pidError * kI);

  // Derivative 
  time1 = time2;
  time2 = millis();
  deltaTime = (time2 - time1) / 1000;
  deltaError = pidError - prevError;
  pidD = kD * (deltaError / deltaTime);
  
  // Set Error
  prevError = pidError;

  // PID
  pidOutput = pidP + pidI + pidD;

  // From 0 to 255 for PWM
  if (pidOutput < 0) pidOutput = 0;
  if (pidOutput > 255) pidOutput = 255;

  // Adjust PWM
  analogWrite(A1, pidOutput);

  // Serial
  Serial.print(pidOutput);
  Serial.print(", ");

  Serial.print(tempReading);
  Serial.print(", ");

  float time = micros() / 1e6; // temp
  Serial.print(time);
  Serial.println("\n");

  delay(200);

}