#pragma once

#include "_config.h"

class Motors{

public:
	static void init();

	// 
	// Inputs: M1-M6: 0-100
	// 
	static void setPower(int powers[PROP_COUNT]);

	// 
	// Stop all motors
	// 
	static void stop();

};