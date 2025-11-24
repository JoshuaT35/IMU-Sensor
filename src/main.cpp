#include <ArduinoBLE.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include <Arduino.h>

#include "bluetooth.h"
#include "imu-sensor.h"

unsigned long currentTime;
unsigned long previousTime;
// sample time (ms)
const unsigned long sampleInterval = 100;

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
        // --- Low Power Mode, transmit NULL data ---
        if (getPowerMode() == MODE_LOW) {
            // write nothing
            setBLEValuesToNull();
            continue;
        }
        // --- High Power Mode, read data ---
        else if (getPowerMode() == MODE_HIGH) {
            // get current time in milliseconds
            currentTime = millis();

            // if less than `sampleInterval` milliseconds has passed, do not read
            if (currentTime - previousTime < sampleInterval) {
                continue;
            }
            
            // otherwise, read data and update
            previousTime = currentTime;
            
            // read accelerometer data (units: g)
            readAccelerationIMU();

            // read gyroscope data (units: degrees/s)
            readGyroscopeIMU();

            // write the data to the corresponding switch characteristic
            updateBLEValues();
        }
    }

    // de-initialize BLE
    deinitBLE();
}
