#include <string>
#include "bluetooth.h"
#include "imu-sensor.h"

// led service
// - Bluetooth® Low Energy LED Service
BLEService led_service(LED_SERVICE_UUID);

// low power mode
BLEUnsignedCharCharacteristic switch_characteristic_power_mode(SWITCH_CHARACTERISTIC_POWER_MODE_UUID, BLERead | BLEWrite);

// switch characteristics (read or write? they are to be read from)
// - Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEFloatCharacteristic switch_characteristic_accel_x(SWITCH_CHARACTERISTIC_ACCEL_X_UUID, BLERead);
BLEFloatCharacteristic switch_characteristic_accel_y(SWITCH_CHARACTERISTIC_ACCEL_Y_UUID, BLERead);
BLEFloatCharacteristic switch_characteristic_accel_z(SWITCH_CHARACTERISTIC_ACCEL_Z_UUID, BLERead);
BLEFloatCharacteristic switch_characteristic_gyro_x(SWITCH_CHARACTERISTIC_GYRO_X_UUID, BLERead);
BLEFloatCharacteristic switch_characteristic_gyro_y(SWITCH_CHARACTERISTIC_GYRO_Y_UUID, BLERead);
BLEFloatCharacteristic switch_characteristic_gyro_z(SWITCH_CHARACTERISTIC_GYRO_Z_UUID, BLERead);
BLEUnsignedLongCharacteristic switch_characteristic_current_time(SWITCH_CHARACTERISTIC_CURRENT_TIME_UUID, BLERead);


bool initBLE() {
    if (!BLE.begin()) {
        // Serial.println("Starting Bluetooth® Low Energy module failed!");
        return false;
    }

    BLE.setLocalName(IMU_NAME);
    BLE.setAdvertisedService(led_service);

    led_service.addCharacteristic(switch_characteristic_power_mode);
    led_service.addCharacteristic(switch_characteristic_accel_x);
    led_service.addCharacteristic(switch_characteristic_accel_y);
    led_service.addCharacteristic(switch_characteristic_accel_z);
    led_service.addCharacteristic(switch_characteristic_gyro_x);
    led_service.addCharacteristic(switch_characteristic_gyro_y);
    led_service.addCharacteristic(switch_characteristic_gyro_z);
    led_service.addCharacteristic(switch_characteristic_current_time);

    BLE.addService(led_service);

    // Initialize characteristics to 0
    switch_characteristic_accel_x.writeValue(0);
    switch_characteristic_accel_y.writeValue(0);
    switch_characteristic_accel_z.writeValue(0);
    switch_characteristic_gyro_x.writeValue(0);
    switch_characteristic_gyro_y.writeValue(0);
    switch_characteristic_gyro_z.writeValue(0);
    switch_characteristic_current_time.writeValue(0);

    BLE.advertise();
    // Serial.println("Advertising");

    // enter low power mode
    setPowerMode(MODE_LOW);

    return true;
}

BLEDevice waitForCentral() {
    return BLE.central();
}

bool deinitBLE() {
    // set to low power mode
    setPowerMode(MODE_LOW);
    
    return true;
}

// update time
void switchCharWriteTime(unsigned long value) {
    // uses: int writeValue(uint32_t value, bool withResponse = true);
    switch_characteristic_current_time.writeValue(value);
}

// write the IMU data to the corresponding switch characteristic
void updateBLEValues() {
    // uses: int writeValue(const void* value, int length, bool withResponse = true);
    switch_characteristic_accel_x.writeValue(aX);
    switch_characteristic_accel_y.writeValue(aY);
    switch_characteristic_accel_z.writeValue(aZ);
    switch_characteristic_gyro_x.writeValue(gX);
    switch_characteristic_gyro_y.writeValue(gY);
    switch_characteristic_gyro_z.writeValue(gZ);

    // debug: print data
    // Serial.print(aX);
    // Serial.print(" ");
    // Serial.print(aY);
    // Serial.print(" ");
    // Serial.print(aZ);
    // Serial.println();
}

void setBLEValuesToNull() {
    switch_characteristic_accel_x.writeValue(0);
    switch_characteristic_accel_y.writeValue(0);
    switch_characteristic_accel_z.writeValue(0);
    switch_characteristic_gyro_x.writeValue(0);
    switch_characteristic_gyro_y.writeValue(0);
    switch_characteristic_gyro_z.writeValue(0);
}

// Read current power mode from characteristic
PowerMode getPowerMode() {
    return (PowerMode)switch_characteristic_power_mode.value();
}

void setPowerMode(PowerMode mode) {
    uint8_t value = static_cast<uint8_t>(mode);
    switch_characteristic_power_mode.writeValue(value);
}
