#include <ArduinoBLE.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <Arduino.h>

#include "bluetooth.h"
#include "imu-sensor.h"
#include "led-control.h"

// // update time
// unsigned long currentTime;
// unsigned long previousTime = 0;
// // sample time (ms)
// const unsigned long sampleInterval = 100;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    delay(1000);

    // begin initialization of bluetooth
    if (!initBLE()) while (1);

    // begin initialization of IMU
    if (!initIMU()) while (1);

    // set the acceleration threshold
    setAccelerationThreshold(2.5);
}

void loop() {
    // listen for Bluetooth® Low Energy peripherals to connect:
    BLEDevice central = waitForCentral();

    // while the central is still connected to peripheral:
    while (central.connected()) {

        // --- track time ---
        // get current time in milliseconds
        // currentTime = millis();

        // // if less than `sampleInterval` milliseconds has passed, do not read
        // if (currentTime - previousTime < sampleInterval) {
        //     continue;
        // }
        
        // // otherwise, read data and update
        // previousTime = currentTime;
        
        // --- Low Power Mode, transmit NULL data ---
        if (getPowerMode() == MODE_LOW) {
            // turn on red light
            pinRedOnly();

            // NULL accel and gyro data
            setBLEValuesToNull();
        }
        // --- High Power Mode, read data ---
        else if (getPowerMode() == MODE_HIGH) {
            // turn on blue light
            pinBlueOnly();
            
            // read accelerometer data (units: g)
            readAccelerationIMU();

            // read gyroscope data (units: degrees/s)
            readGyroscopeIMU();

            // write the data to the corresponding switch characteristics
            updateBLEValues();
        }

        // write the time
        switchCharWriteTime(millis());
    }

    // NOTE: put a check so that these don't run EVERY loop
    // de-initialize BLE
    deinitBLE();
    // turn of all pins
    allPinsOff();
}
