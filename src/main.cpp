#include <ArduinoBLE.h>
#include <LSM6DS3.h>
#include <Wire.h>

#include "bluetooth.h"
#include "imu-sensor.h"

unsigned long previousTime = 0; // Store the last timestamp

void setup() {
    setAccelerationThreshold(2.5);

    Serial.begin(9600);
    while (!Serial);

    // begin initialization
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");

        while (1);
    }

    // set advertised local name and service UUID:
    BLE.setLocalName(IMU_NAME);
    BLE.setAdvertisedService(led_service);

    // add the characteristic to the service
    led_service.addCharacteristic(switch_characteristic_accel_x);
    led_service.addCharacteristic(switch_characteristic_accel_y);
    led_service.addCharacteristic(switch_characteristic_accel_z);
    led_service.addCharacteristic(switch_characteristic_gyro_x);
    led_service.addCharacteristic(switch_characteristic_gyro_y);
    led_service.addCharacteristic(switch_characteristic_gyro_z);
    led_service.addCharacteristic(switch_characteristic_time);

    // add service
    BLE.addService(led_service);

    // set the initial value for the characeristics
    switch_characteristic_accel_x.writeValue(0);
    switch_characteristic_accel_y.writeValue(0);
    switch_characteristic_accel_z.writeValue(0);
    switch_characteristic_gyro_x.writeValue(0);
    switch_characteristic_gyro_y.writeValue(0);
    switch_characteristic_gyro_z.writeValue(0);
    switch_characteristic_time.writeValue(0);

    // start advertising
    BLE.advertise();
}

void loop() {
    // listen for Bluetooth® Low Energy peripherals to connect:
    BLEDevice central = BLE.central();

    // if a central is connected to peripheral:
    if (central) {
        Serial.print("Connected to central: ");
        // print the central's MAC address:
        Serial.println(central.address());

        // while the central is still connected to peripheral:
        while (central.connected()) {
            
            // read accelerometer data
            aX = myIMU.readFloatAccelX();
            aY = myIMU.readFloatAccelY();
            aZ = myIMU.readFloatAccelZ();

            // if motion is not significant, return
            // NOTE: must be called only after reading accelerometer data
            if (!significantMotionDetected()) {
                return;
            }

            unsigned long currentTime = millis(); // Get current time in milliseconds
            unsigned long deltaTime = currentTime - previousTime; // Time difference

            // read gyroscope data
            gX = myIMU.readFloatGyroX();
            gY = myIMU.readFloatGyroY();
            gZ = myIMU.readFloatGyroZ();

            // write the data to the corresponding switch characteristic
            switch_characteristic_accel_x.writeValue(aX);
            switch_characteristic_accel_y.writeValue(aY);
            switch_characteristic_accel_z.writeValue(aZ);
            switch_characteristic_gyro_x.writeValue(gX);
            switch_characteristic_gyro_y.writeValue(gY);
            switch_characteristic_gyro_z.writeValue(gZ);
            switch_characteristic_time.writeValue(deltaTime);   // in (ms)

            // debug: print the data
            // Serial.print(aX, 3);
            // Serial.print(',');
            // Serial.print(aY, 3);
            // Serial.print(',');
            // Serial.print(aZ, 3);
            // Serial.print(',');
            // Serial.print(gX, 3);
            // Serial.print(',');
            // Serial.print(gY, 3);
            // Serial.print(',');
            // Serial.print(gZ, 3);
            // Serial.print(',');
            // Serial.print(deltaTime, 3);
            // Serial.println();
        }

        // when the central disconnects, print it out:
        Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
    }
}
