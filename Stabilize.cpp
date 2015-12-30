#include "_config.h"
#include "_types.h"

#include <Thread.h>

#include "PID.h"
#include "Drone.h"
#include "Motors.h"
#include "System.h"
#include "Stabilizer.h"

void threadCheckFall_callback();
void threadStabilizer_callback();

Thread threadCheckFall;
Thread threadStabilizer;


// 
// PID Setup
// 
PID pidYaw(1, 0, 0, 100);
PID pidRoll(1, 0, 0, 100);
PID pidPitch(1, 0, 0, 100);

void Stabilizer::init(){

	// Compute Propeler Weigth Values
	float sum[2] = {0, 0};
	for(int i = 0; i < PROP_COUNT; i++){
		sum[0] += abs(Drone::props[i][PROP_X]);
		sum[1] += abs(Drone::props[i][PROP_Y]);
	};

	// LOG("PROP VALS: \n");
	for(int i = 0; i < PROP_COUNT; i++){
		Drone::props[i][PROP_X_W] = abs(Drone::props[i][PROP_X]) / sum[PROP_X];
		Drone::props[i][PROP_Y_W] = abs(Drone::props[i][PROP_Y]) / sum[PROP_Y];

		// LOG(" = ");  LOG(i+1); 
		// LOG(" ["); LOG(Drone::props[i][2]);
		// LOG(", "); LOG(Drone::props[i][3]);LOG("]\n");
	};

	// Safety thread
	threadCheckFall.setInterval(200);
	threadCheckFall.onRun(threadCheckFall_callback);

	// Stabilizer thread
	threadStabilizer.setInterval(10);
	threadStabilizer.onRun(threadStabilizer_callback);

	// Add threads to System
	System.add(&threadCheckFall);
	System.add(&threadStabilizer);

}


// 
// Checks if drone has inclinated too much
// 
void threadCheckFall_callback(){
	if(Drone::state != ARMED)
		return;

	if(Drone::gravity.z > STABILITY_GRAVITY_Z_MIN)
		return;

	Drone::setState(ALARM_CRASHED);
}

int powers[PROP_COUNT];

unsigned long lastComputeTime = 0;
void threadStabilizer_callback(){

	// Find out dt (delta time)
	unsigned long now = millis();
	float dt = (now - lastComputeTime) / 1000.0;
	lastComputeTime = now;

	if(Drone::state != ARMED){
		pidYaw.reset();
		pidRoll.reset();
		pidPitch.reset();

		Motors::stop();
		return;
	}

	// Check if dt is good to go
	if(dt <= 0.0 || dt >= 0.2){
		LOG("$ dt too high! "); LOG(dt); LOG("\n");
		return;
	}

	pidYaw.addNewSample(Drone::ypr[2]);
	pidRoll.addNewSample(Drone::ypr[2]);
	pidPitch.addNewSample(Drone::ypr[1]);

	float outYaw = pidYaw.process(dt);
	float outRoll = pidRoll.process(dt);
	float outPitch = pidPitch.process(dt);

	// Iterate and distribute power to propelers
	for(int i = 0; i < PROP_COUNT; i++){

		powers[i] = outPitch * Drone::props[i][PROP_Y_W] +
					outRoll * Drone::props[i][PROP_X_W] +
					outYaw * Drone::props[i][PROP_DIR];

	}

	// Output Motor powers
	Motors::setPower(powers);

}
