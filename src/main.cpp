#include <ArduinoBLE.h>
#include <LSM6DS3.h>
#include <Wire.h>

#include "bluetooth.h"
#include "imu-sensor.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // begin initialization
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");

        while (1);
    }

    // set advertised local name and service UUID:
    BLE.setLocalName("LED");
    BLE.setAdvertisedService(led_service);

    // add the characteristic to the service
    led_service.addCharacteristic(switch_characteristic_accel_x);
    led_service.addCharacteristic(switch_characteristic_accel_y);
    led_service.addCharacteristic(switch_characteristic_accel_z);
    led_service.addCharacteristic(switch_characteristic_gyro_x);
    led_service.addCharacteristic(switch_characteristic_gyro_y);
    led_service.addCharacteristic(switch_characteristic_gyro_z);

    // add service
    BLE.addService(led_service);

    // set the initial value for the characeristics
    switch_characteristic_accel_x.writeValue(0);
    switch_characteristic_accel_y.writeValue(0);
    switch_characteristic_accel_z.writeValue(0);
    switch_characteristic_gyro_x.writeValue(0);
    switch_characteristic_gyro_y.writeValue(0);
    switch_characteristic_gyro_z.writeValue(0);

    // start advertising
    BLE.advertise();
}

void loop() {
    Serial.print("loop is running\n");
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
        if (!significantMotionDetected()) {
            return;
        }

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

        // debug: print the data
        Serial.print(aX, 3);
        Serial.print(',');
        Serial.print(aY, 3);
        Serial.print(',');
        Serial.print(aZ, 3);
        Serial.print(',');
        Serial.print(gX, 3);
        Serial.print(',');
        Serial.print(gY, 3);
        Serial.print(',');
        Serial.print(gZ, 3);
        Serial.println();
    }

        // when the central disconnects, print it out:
        Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
    }
}
