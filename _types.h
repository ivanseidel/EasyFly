#pragma once

#include <stdint.h>
#include <math.h>
#include <helper_3dmath.h>

enum STATE{
	STOPPED = 0,
	ARMED,
	
	ALARM_INIT,
	ALARM_CRASHED,
	ALARM_LOW_BATTERY
};

struct TARGET_STATE{
	float yaw;
	float roll;
	float pitch;
	float throttle;
};