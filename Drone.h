#pragma once

#include "_config.h"
#include "_types.h"

#define PROP_X				0
#define PROP_Y				1
#define PROP_X_W			2
#define PROP_Y_W			3
#define PROP_DIR			4

class Drone{
public:
	static STATE state;

	static void setState(STATE newState);

	static float vbat;
	
	static Quaternion q;
	static VectorFloat gravity;
	static float ypr[3]; // DEGREES

	static TARGET_STATE targetState;

	static float props[PROP_COUNT][5];
};