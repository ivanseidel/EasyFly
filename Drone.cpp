#include "_config.h"
#include "_types.h"

#include "Drone.h"
#include "Motors.h"

float Drone::vbat = 0;

Quaternion Drone::q = Quaternion();
VectorFloat Drone::gravity = VectorFloat(0,0,0);
float Drone::ypr[3] = {0,0,0};

STATE Drone::state = STOPPED;

float Drone::props[PROP_COUNT][5] = {
	// X Position 		  Y Position 		X Weight    Y Weight 	DIR
	{sin(TO_RAD(0)), 	cos(TO_RAD(0)),		0, 			0,			+1},
	{sin(TO_RAD(60)), 	cos(TO_RAD(60)),	0, 			0,			-1},
	{sin(TO_RAD(120)), 	cos(TO_RAD(120)),	0, 			0,			+1},
	{sin(TO_RAD(180)), 	cos(TO_RAD(180)),	0, 			0,			-1},
	{sin(TO_RAD(-120)), cos(TO_RAD(-120)),	0, 			0,			+1},
	{sin(TO_RAD(-60)), 	cos(TO_RAD(-60)),	0, 			0,			-1}
};


void Drone::setState(STATE newState){
	if(state != newState){
		LOG("$ Changing STATE: "); LOG(newState); LOG("\n");
	}

	state = newState;

	if(state != ARMED){
		Motors::stop();
	}

}