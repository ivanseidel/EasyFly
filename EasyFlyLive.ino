// Misc stuffs
#include "_config.h"
#include "_types.h"


// 
// Libraries
// 
#include <math.h>
#include <Wire.h>
#include <Thread.h>
#include <I2Cdev.h>
#include <helper_3dmath.h>
#include <ThreadController.h>
#include <MPU6050_6Axis_MotionApps20.h>


// 
// Modules
// 
#include "IMU.h"
#include "PID.h"
#include "Drone.h"
#include "System.h"
#include "Motors.h"
#include "Attitude.h"
#include "Stabilizer.h"


void setup(){
	system_init();

	Motors::init();

	Attitude::init();

	Stabilizer::init();
}

void loop(){
	System.run();
}