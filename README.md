# IMU-Sensor (XIAO nRF52840 Sense – PlatformIO)

This project contains firmware developed for the **Seeed Studio XIAO nRF52840 Sense** board using **PlatformIO**.
The code is tailored for applications involving the onboard IMU (LSM6DS3) sensors supported by the nRF52840 SoC.

Note that 

## 🚀 Features
- Built for the **XIAO nRF52840 Sense** development board  
- Uses **PlatformIO** as the build environment  
- Supports the onboard **LSM6DS3 IMU** (accelerometer + gyroscope)  
- Structured for easy extension into BLE, sensor fusion, and real-time data processing applications  

## 📁 Project Structure
- <code>main.cpp</code>: The main code to be run.
- <code>bluetooth.h</code>, <code>bluetooth.cpp</code>: Code to enable and run Bluetooth Low Energy (BLE) on the board. Also contains the switch characteristics.
- <code>imu-sensor.h</code>, <code>imu-sensor.cpp</code>: Code to control the IMU sensor of the board.
- <code>led-control.h</code>, <code>led-control.cpp</code>: Code to cotnol the LEDs of the board.

## 📝 Notes
- If the following error is encountered:
<br></br>
<code>.pio\libdeps\xiaoblesense\Seeed Arduino LSM6DS3\LSM6DS3.cpp:108:17: error: ‘class arduino::MbedSPI’ has no member named ‘setBitOrder’ SPI.setBitOrder(MSBFIRST);</code>
<br></br>
Simply comment out the offending line in `LSM6DS3.cpp`, and then rebuild the project.
