#include <bits/stdc++.h>
#include <LSM6DS3.h>
#include <Wire.h>
#include "imu-sensor.h"

// declare extern variables runtime
// - I2C device address 0x6A
LSM6DS3 myIMU(I2C_MODE, 0x6A);
// (default is 2.5)
float accelerationThreshold = 2.5;
// (default is 0)
float aX = 0;
float aY = 0;
float aZ = 0;
float gX = 0;
float gY = 0;
float gZ = 0;

// set accelerationThreshold
void setAccelerationThreshold(float at) {
    if (at <= 0) {
        // return error
        std::cerr << "setAccelerationThreshold error: invalid number.\n";
        return;
    }
    accelerationThreshold = at;
    return;
};

// returns 1 (True) if significant motion detected, else 0 (False)
int significantMotionDetected() {
    // sum up the absolutes
    float aSum = fabs(aX) + fabs(aY) + fabs(aZ);
    
    // check if it's above the threshold
    if (aSum >= accelerationThreshold) {
        return 1;
    }
    return 0;
}
