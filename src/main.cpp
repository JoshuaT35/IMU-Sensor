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
    // TO REMOVE: initialize serial, pins
    initLEDs();
    Serial.begin(9600);

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

        // Reduce Power usage
        Bluefruit.setTxPower(-8); // reduce BLE transmit power
        Bluefruit.Advertising.setInterval(1000, 2000); // 1–2 seconds

        // NULL accel and gyro data
        if (Bluefruit.Periph.connected() && switch_characteristic_accel_x.notifyEnabled()) {
            setBLEValuesToNull();
        }
    }

    // --- High Power Mode, read data ---
    if (getPowerMode() == MODE_HIGH) {
        // TO REMOVE: turn on blue light
        pinBlueOnly();

        // Increase Power usage
        Bluefruit.setTxPower(4); // full power for reliable high-speed streaming

        // Only stream if connected AND notifications are enabled
        if (Bluefruit.Periph.connected() && switch_characteristic_accel_x.notifyEnabled()) {
            // read accelerometer data (units: g)
            readAccelerationIMU();
            // read gyroscope data (units: degrees/s)
            readGyroscopeIMU();
            // write the data to the corresponding switch characteristics
            updateBLEValues();
        }
    }

    // write the time
    switchCharWriteTime(millis());

    // if in high-power mode but have been disconnected past limit
    checkConnectionTimeout();

    // NOTE: put a check so that these don't run EVERY loop
    // TO REMOVE: turn of all pins
    allPinsOff();
}
