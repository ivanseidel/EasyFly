#include <math.h>
#include <Wire.h>
#include <Thread.h>
#include <MPU6050_6Axis_MotionApps20.h>

#include "_config.h"

#include "IMU.h"

#include "Drone.h"
#include "System.h"

IMU::IMU(): Thread(){

}

bool IMU::init(){
	bool devStatus;

	LOG("IMU::init\n");

	// Fastwire::setup(100, true);
	Wire.begin();
	TWBR = ((16000000L / 400000L) - 16) / 2;
	delay(1);
	mpu.initialize();

	if(!mpu.testConnection()){
		LOG("MPU6050 connection failed\n");
		return false;
	}

	mpu.setDMPEnabled(false);
	mpu.resetDMP();
	// Reset IMU
	mpu.reset();
	delay(50);

	// Activate MPU6050
	mpu.setSleepEnabled(false);

	// load and configure the DMP
	devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1688); // 1688 factory default for my test chip

	// make sure it worked (returns 0 if so)
	if (devStatus != 0) {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print("DMP Initialization failed (code ");
		Serial.print(devStatus);
		Serial.println(")");

		return false;
	}

	dmpEnabled = false;
	return true;
}


bool IMU::shouldRun(unsigned long time){

	// Turn ON/OFF DMP (Digital Motion Processing)
	if(enabled != dmpEnabled){
		mpu.setDMPEnabled(enabled);
		LOG( enabled ? "$IMU is [ON]\n" : "$IMU is [OFF]\n" );
		dmpEnabled = enabled;
	}

	if(!Thread::shouldRun(time))
		return false;

	interruptStatus = mpu.getIntStatus();
	fifoCount = mpu.getFIFOCount();

	return (fifoCount >= 42);
}

void IMU::run(){

	if (interruptStatus & 0x02) {
		runned();

		// read a packet from FIFO
		mpu.getFIFOBytes(packet, 42);
		// mpu.resetFIFO();

		// Convert and save state to Drone
		mpu.dmpGetQuaternion(&q, packet);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

		newData = true;
	}

	if (interruptStatus & 0x10) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
	}

}