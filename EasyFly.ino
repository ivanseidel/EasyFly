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

	for(int i = 0; i < 100; i += 5){
		Serial.print("Speed: ");
		Serial.println(i);
		delay(10);
		int powers0[] = {i, i, i, i, i, i};
		Motors::setPower(powers0);
		delay(400);
	}

	// delay(3000);
	int powers1[] = {-1, -1, -1, -1, -1, -1};
	Motors::setPower(powers1);
	delay(6000);

	// int powers2[] = {-1, -1, -1, 100, 100, 100};
	// Motors::setPower(powers2);
	// delay(2000);
	//
	// int powers3[] = {100, 100, 100, 100, 100, 100};
	// Motors::setPower(powers3);
	// delay(2000);

}

void loop(){


	System.run();
}
