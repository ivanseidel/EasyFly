#include "_config.h"
#include "_types.h"

#include "IMU.h"
#include "Drone.h"
#include "System.h"
#include "Attitude.h"

// forward declarate callbacks
void threadAttitude_callback();
void threadDebug_callback();

IMU* imu;
Thread threadAttitude;
Thread threadDebug;

void Attitude::init(){

	// Init IMU
	imu = new IMU();
	imu->init();
	imu->setInterval(5);


	// Initialize Attitude Thread
	threadAttitude.setInterval(5);
	threadAttitude.onRun(threadAttitude_callback);

	// Debug Thread
	threadDebug.setInterval(200);
	threadDebug.onRun(threadDebug_callback);
	threadDebug.enabled = false;

	// System
	System.add(imu);
	System.add(&threadAttitude);
	System.add(&threadDebug);
}


void threadAttitude_callback(){
	if(imu->newData){
		imu->newData = false;

		// Copy the Yaw/Pitch/Roll
		Drone::ypr[0] = imu->ypr[0] * 180/M_PI;
		Drone::ypr[1] = imu->ypr[1] * 180/M_PI;
		Drone::ypr[2] = imu->ypr[2] * 180/M_PI;

		// Copy the Gravity
		Drone::gravity = imu->gravity;
	}
}


void threadDebug_callback(){

	LOG("YPR:\t"); 
	LOG(Drone::ypr[0]); LOG("\t");
	LOG(Drone::ypr[1]); LOG("\t");
	LOG(Drone::ypr[2]); LOG("\n");

}