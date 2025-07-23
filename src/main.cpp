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

    // begin initialization of bluetooth
    delay(1000);
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
    led_service.addCharacteristic(switch_characteristic_current_time);

    // add service
    BLE.addService(led_service);

    // set the initial value for the characeristics
    switch_characteristic_accel_x.writeValue(0);
    switch_characteristic_accel_y.writeValue(0);
    switch_characteristic_accel_z.writeValue(0);
    switch_characteristic_gyro_x.writeValue(0);
    switch_characteristic_gyro_y.writeValue(0);
    switch_characteristic_gyro_z.writeValue(0);
    switch_characteristic_current_time.writeValue(0);

    // start advertising
    BLE.advertise();
    Serial.print("Advertising\n");

    // begin initialization of IMU
    if (myIMU.begin() != 0) {
        Serial.println("Device error");
    }
    else {
        Serial.println("aX,aY,aZ,gX,gY,gZ");
    }
    // set the acceleration threshold
    setAccelerationThreshold(2.5);
}

void loop() {
    // listen for Bluetooth® Low Energy peripherals to connect:
    BLEDevice central = BLE.central();

    // while the central is still connected to peripheral:
    while (central.connected()) {

        // get current time in milliseconds
        currentTime = millis();
        // if less than `sampleInterval` milliseconds has passed, do not read
        if (currentTime - previousTime < sampleInterval) {
            continue;
        }
        
        // otherwise, read data and update
        previousTime = currentTime;
        
        // read accelerometer data (units: g)
        aX = myIMU.readFloatAccelX();
        aY = myIMU.readFloatAccelY();
        aZ = myIMU.readFloatAccelZ();

        // read gyroscope data (units: degrees/s)
        gX = myIMU.readFloatGyroX();
        gY = myIMU.readFloatGyroY();
        gZ = myIMU.readFloatGyroZ();

        // debug: print data
        // Serial.print(aX);
        // Serial.print(" ");
        // Serial.print(aY);
        // Serial.print(" ");
        // Serial.print(aZ);
        // Serial.println();

        // write the data to the corresponding switch characteristic

        // uses: int writeValue(const void* value, int length, bool withResponse = true);
        switch_characteristic_accel_x.writeValue(aX);
        switch_characteristic_accel_y.writeValue(aY);
        switch_characteristic_accel_z.writeValue(aZ);
        switch_characteristic_gyro_x.writeValue(gX);
        switch_characteristic_gyro_y.writeValue(gY);
        switch_characteristic_gyro_z.writeValue(gZ);

        // uses: int writeValue(uint32_t value, bool withResponse = true);
        switch_characteristic_current_time.writeValue(currentTime);   // in (ms)
    }
}
