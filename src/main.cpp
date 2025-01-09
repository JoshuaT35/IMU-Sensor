#include <ArduinoBLE.h>
#include <LSM6DS3.h>
#include <Wire.h>

void setup() {
  // Initialize the serial communication at 9600 baud rate
  Serial.begin(9600); 

  // Wait for the serial monitor to open
  while (!Serial);  // Optional, useful for some boards like Leonardo
  
  // Print a message to the serial monitor
  Serial.println("Hello, PlatformIO!");
}

void loop() {
  // Keep printing a message every second
  Serial.println("Looping...");
  delay(1000);  // Delay for 1 second
}
