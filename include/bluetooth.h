#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// include
#include <string>
#include <unordered_map>
#include <ArduinoBLE.h>

// bluetooth ledService ()
extern BLEService ledService;

// switchCharacteristics (identify by uuid)
extern std::unordered_map<std::string, BLEByteCharacteristic> switchCharacteristics;

// given an integer, generate that many switchCharacteristics
// with both read and write (need both? Might not since IMU will only send data, not receive)
void createSwitchCharacteristics(int numSC);

// generate a random uuid
std::string generateUUID();

#endif
