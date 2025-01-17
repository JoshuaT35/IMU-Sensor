#include <random>
#include <bits/stdc++.h>
#include "bluetooth.h"

// extern variables
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service
std::unordered_map<std::string, BLEByteCharacteristic> switchCharacteristics;

// given an integer, generate that many switchCharacteristics
// with both read and write (need both? Might not since IMU will only send data, not receive)
void createSwitchCharacteristics(int numSC) {
    // error check if integer is not positive
    if (numSC <= 0) {
        // return error
        std::cerr << "createSwitchCharacteristics error: invalid number.\n";
        return;
    }

    // for each switchCharacteristics
    for (int i = 0; i < numSC; i++) {
        // generate a UUID
        // NOTE: error check
        std::string uuid = generateUUID();

        // create a switch characteristic
        BLEByteCharacteristic switchCharacteristic(uuid.c_str(), BLERead | BLEWrite);

        // store switch characteristic
        switchCharacteristics.insert(
            {uuid, switchCharacteristic}
        );
    }

    return;
}

// NOTE: change
std::string generateUUID() {
    // Hexadecimal characters
    const char hexChars[] = "0123456789abcdef";

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15); // For hex characters
    std::uniform_int_distribution<> disVariant(8, 11); // For variant

    // UUID format: xxxxxxxx-xxxx-4xxx-Nxxx-xxxxxxxxxxxx
    std::string uuid;
    uuid = "xxxxxxxx-xxxx-4xxx-Nxxx-xxxxxxxxxxxx";

    do {
        // UUID format: xxxxxxxx-xxxx-4xxx-Nxxx-xxxxxxxxxxxx
        uuid = "xxxxxxxx-xxxx-4xxx-Nxxx-xxxxxxxxxxxx";

        // Replace 'x' with random hex characters
        for (char& ch : uuid) {
            if (ch == 'x') {
                ch = hexChars[dis(gen)];
            } else if (ch == 'N') {
                ch = hexChars[disVariant(gen)];
            }
        }
    } while (switchCharacteristics.find(uuid) == switchCharacteristics.end());

    return uuid;
}
