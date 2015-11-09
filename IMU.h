#pragma once

#include "_types.h"

#include <Wire.h>
#include <Thread.h>
#include <MPU6050_6Axis_MotionApps20.h>

class IMU: public Thread{
private:
	MPU6050 mpu;

	// Is the DMP in MPU enabled?
	bool dmpEnabled;

	// Last saved packet
	uint8_t packet[64];

	uint8_t fifoCount;
	uint8_t interruptStatus;

public:
	bool newData;

	IMU();

	bool init();

	// Checks if the Thread should run (Time && Enabled && FIFO buffer)
	bool shouldRun(unsigned long time);

	// Override the usual Run method
	void run();

	Quaternion q;
	VectorFloat gravity;
	float ypr[3];

};