#include <Arduino.h>
#include <bluefruit.h>

#include "bluetooth.h"
#include "imu-sensor.h"
#include "led-control.h"

// // update time
// unsigned long currentTime;
// unsigned long previousTime = 0;
// // sample time (ms)
// const unsigned long sampleInterval = 100;

void setup() {
    // TO REMOVE: initialize pins
    initLEDs();

    // begin initialization of bluetooth
    if (!initBLE()) while (1);

    // begin initialization of IMU
    if (!initIMU()) while (1);

    // set the acceleration threshold
    setAccelerationThreshold(2.5);
}

void loop() {        
    // --- Low Power Mode, transmit NULL data ---
    if (getPowerMode() == MODE_LOW) {
        // TO REMOVE: turn on red light
        pinRedOnly();

        // NULL accel and gyro data
        setBLEValuesToNull();
    }
    // --- High Power Mode, read data ---
    else if (getPowerMode() == MODE_HIGH) {
        // TO REMOVE: turn on blue light
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

    // NOTE: put a check so that these don't run EVERY loop
    // TO REMOVE: turn of all pins
    allPinsOff();
}
