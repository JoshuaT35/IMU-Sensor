#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// include
#include <string>
#include <unordered_map>
#include <ArduinoBLE.h>

// --- UUIDS ---

// 1 for led service
#define LED_SERVICE_UUID "19B10000-E8F2-537E-4F6C-D104768A1214"

// 6 for IMU data
// note: number of switch characteristics must match number created
#define SWITCH_CHARACTERISTIC_ACCEL_X_UUID "19B10010-E8F2-537E-4F6C-D104768A1214"
#define SWITCH_CHARACTERISTIC_ACCEL_Y_UUID "19B10020-E8F2-537E-4F6C-D104768A1214"
#define SWITCH_CHARACTERISTIC_ACCEL_Z_UUID "19B10030-E8F2-537E-4F6C-D104768A1214"
#define SWITCH_CHARACTERISTIC_GYRO_X_UUID "19B10040-E8F2-537E-4F6C-D104768A1214"
#define SWITCH_CHARACTERISTIC_GYRO_Y_UUID "19B10050-E8F2-537E-4F6C-D104768A1214"
#define SWITCH_CHARACTERISTIC_GYRO_Z_UUID "19B10060-E8F2-537E-4F6C-D104768A1214"
// 1 for time of current reading
#define SWITCH_CHARACTERISTIC_CURRENT_TIME_UUID "19B10070-E8F2-537E-4F6C-D104768A1214"

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
