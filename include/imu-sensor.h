#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H

#include <LSM6DS3.h>
#include <Wire.h>

// name of imu
#define IMU_NAME "Imu-Sensor"

// NOTE: use IMU class?

// imu
extern LSM6DS3 myIMU;

// variables
extern float accelerationThreshold;
extern float aX, aY, aZ, gX, gY, gZ;

// set accelerationThreshold (default is 2.5)
void setAccelerationThreshold(float at);

// returns 0 if significant motion detected, else 1
int significantMotionDetected();

// imu functions
bool initIMU();
void readAccelerationIMU();
void readGyroscopeIMU();

#endif
