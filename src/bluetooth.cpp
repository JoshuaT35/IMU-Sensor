#include <string>
#include "bluetooth.h"

// led service
// - Bluetooth® Low Energy LED Service
BLEService led_service(LED_SERVICE_UUID);

// switch characteristics (read or write? they are to be read from)
// - Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switch_characteristic_accel_x(SWITCH_CHARACTERISTIC_ACCEL_X_UUID, BLERead | BLEWrite);
BLEByteCharacteristic switch_characteristic_accel_y(SWITCH_CHARACTERISTIC_ACCEL_Y_UUID, BLERead | BLEWrite);
BLEByteCharacteristic switch_characteristic_accel_z(SWITCH_CHARACTERISTIC_ACCEL_Z_UUID, BLERead | BLEWrite);
BLEByteCharacteristic switch_characteristic_gyro_x(SWITCH_CHARACTERISTIC_GYRO_X_UUID, BLERead | BLEWrite);
BLEByteCharacteristic switch_characteristic_gyro_y(SWITCH_CHARACTERISTIC_GYRO_Y_UUID, BLERead | BLEWrite);
BLEByteCharacteristic switch_characteristic_gyro_z(SWITCH_CHARACTERISTIC_GYRO_Z_UUID, BLERead | BLEWrite);
