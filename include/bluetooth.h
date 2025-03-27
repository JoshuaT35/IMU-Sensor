#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// include
#include <string>
#include <unordered_map>
#include <ArduinoBLE.h>

// --- UUIDS ---

// 1 for led service
#define LED_SERVICE_UUID "0b91a798-23b1-4369-9d45-a3a26d936904"

// 6 for IMU data
// note: number of switch characteristics must match number created
#define SWITCH_CHARACTERISTIC_ACCEL_X_UUID "026080c9-dc3a-401b-829c-2ee3b5565200"
#define SWITCH_CHARACTERISTIC_ACCEL_Y_UUID "e0a0b53e-5c53-4acf-bf79-39d2982362e9"
#define SWITCH_CHARACTERISTIC_ACCEL_Z_UUID "94b54966-faa7-48c1-9b53-7e44a9a872be"
#define SWITCH_CHARACTERISTIC_GYRO_X_UUID "d30c8099-5b3e-4d4f-9c42-40b47a3f71ea"
#define SWITCH_CHARACTERISTIC_GYRO_Y_UUID "734c0d37-c4fc-4265-953f-0aa24d28b1a5"
#define SWITCH_CHARACTERISTIC_GYRO_Z_UUID "e51f3e60-3fdd-4591-9910-87362247c68d"
// 1 for time between readings
#define SWITCH_CHARACTERISTIC_CURRENT_TIME_UUID "72d913bb-e8df-44b8-b8ec-4f098978e0be"

// bluetooth ledService ()
extern BLEService led_service;

// switchCharacteristics
extern BLEFloatCharacteristic switch_characteristic_accel_x;
extern BLEFloatCharacteristic switch_characteristic_accel_y;
extern BLEFloatCharacteristic switch_characteristic_accel_z;
extern BLEFloatCharacteristic switch_characteristic_gyro_x;
extern BLEFloatCharacteristic switch_characteristic_gyro_y;
extern BLEFloatCharacteristic switch_characteristic_gyro_z;
extern BLEUnsignedLongCharacteristic switch_characteristic_current_time;

#endif
