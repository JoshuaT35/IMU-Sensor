#include "bluetooth.h"
#include "imu-sensor.h"

// led service
// - Bluetooth® Low Energy LED Service
BLEService led_service(LED_SERVICE_UUID);

// low power mode
BLECharacteristic switch_characteristic_power_mode(
    SWITCH_CHARACTERISTIC_POWER_MODE_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_WRITE),
    SECMODE_OPEN,
    SECMODE_OPEN
);

// switch characteristics (read or write? they are to be read from)
// - Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLECharacteristic switch_characteristic_accel_x(
    SWITCH_CHARACTERISTIC_ACCEL_X_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_accel_y(
    SWITCH_CHARACTERISTIC_ACCEL_Y_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_accel_z(
    SWITCH_CHARACTERISTIC_ACCEL_Z_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_gyro_x(
    SWITCH_CHARACTERISTIC_GYRO_X_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_gyro_y(
    SWITCH_CHARACTERISTIC_GYRO_Y_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_gyro_z(
    SWITCH_CHARACTERISTIC_GYRO_Z_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

BLECharacteristic switch_characteristic_current_time(
    SWITCH_CHARACTERISTIC_CURRENT_TIME_UUID,
    static_cast<uint8_t>(CHR_PROPS_READ | CHR_PROPS_NOTIFY),
    SECMODE_OPEN,
    SECMODE_NO_ACCESS
);

// --- functions ---
bool initBLE() {
    Bluefruit.begin();
    Bluefruit.setName(IMU_NAME);

    // begin BLE service
    led_service.begin();

    // begin BLE characteristics (implicitly added to service)
    switch_characteristic_power_mode.begin();
    switch_characteristic_accel_x.begin();
    switch_characteristic_accel_y.begin();
    switch_characteristic_accel_z.begin();
    switch_characteristic_gyro_x.begin();
    switch_characteristic_gyro_y.begin();
    switch_characteristic_gyro_z.begin();
    switch_characteristic_current_time.begin();

    // Initialize characteristics to 0
    // Initialize characteristics to 0
    uint8_t zero_u8 = 0;
    float zero_f = 0.0f;
    uint32_t zero_u32 = 0;

    setPowerMode(MODE_LOW);
    switch_characteristic_accel_x.write(&zero_f, sizeof(zero_f));
    switch_characteristic_accel_y.write(&zero_f, sizeof(zero_f));
    switch_characteristic_accel_z.write(&zero_f, sizeof(zero_f));
    switch_characteristic_gyro_x.write(&zero_f, sizeof(zero_f));
    switch_characteristic_gyro_y.write(&zero_f, sizeof(zero_f));
    switch_characteristic_gyro_z.write(&zero_f, sizeof(zero_f));
    switch_characteristic_current_time.write(&zero_u32, sizeof(zero_u32));

    // Advertising
    Bluefruit.Advertising.addService(led_service);
    Bluefruit.Advertising.addName();
    Bluefruit.Advertising.start();

    // enter low power mode
    setPowerMode(MODE_LOW);

    return true;
}

bool deinitBLE() {
    // set to low power mode
    setPowerMode(MODE_LOW);
    return true;
}

// update time
void switchCharWriteTime(unsigned long value) {
    switch_characteristic_current_time.notify(&value, sizeof(value));
}

// write the IMU data to the corresponding switch characteristic
void updateBLEValues() {
    switch_characteristic_accel_x.notify(&aX, sizeof(aX));
    switch_characteristic_accel_y.notify(&aY, sizeof(aY));
    switch_characteristic_accel_z.notify(&aZ, sizeof(aZ));

    switch_characteristic_gyro_x.notify(&gX, sizeof(gX));
    switch_characteristic_gyro_y.notify(&gY, sizeof(gY));
    switch_characteristic_gyro_z.notify(&gZ, sizeof(gZ));

    // debug: print data
    // Serial.print(aX);
    // Serial.print(" ");
    // Serial.print(aY);
    // Serial.print(" ");
    // Serial.print(aZ);
    // Serial.println();
}

void setBLEValuesToNull() {
    float zero = 0.0f;

    switch_characteristic_accel_x.notify(&zero, sizeof(zero));
    switch_characteristic_accel_y.notify(&zero, sizeof(zero));
    switch_characteristic_accel_z.notify(&zero, sizeof(zero));

    switch_characteristic_gyro_x.notify(&zero, sizeof(zero));
    switch_characteristic_gyro_y.notify(&zero, sizeof(zero));
    switch_characteristic_gyro_z.notify(&zero, sizeof(zero));
}

// Read current power mode from characteristic
PowerMode getPowerMode() {
    uint8_t value = 0;
    switch_characteristic_power_mode.read(&value, sizeof(value));
    return static_cast<PowerMode>(value);
}

void setPowerMode(PowerMode mode) {
    uint8_t value = static_cast<uint8_t>(mode);
    switch_characteristic_power_mode.write(&value, sizeof(value));
}
