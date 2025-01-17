#ifndef IMU_SENSOR.H
#define IMU_SENSOR.H

#include <LSM6DS3.h>
#include <Wire.h>

// NOTE: use IMU class?

// imu
extern LSM6DS3 myIMU;

// variables
extern float accelerationThreshold;
extern float aX, aY, aZ, gX, gY, gZ;

// set accelerationThreshold (default is 2.5)
void setAccelerationThreshold(float at);

#endif
