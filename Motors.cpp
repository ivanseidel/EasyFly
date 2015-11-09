#include "_config.h"

#include <Thread.h>

#include "Motors.h"


void Motors::init(){

	// Initialize as output
	for(int i = 0; i < sizeof(MOTOR_PINS)/sizeof(int); i++){
		pinMode(MOTOR_PINS[i], OUTPUT);
	}

	// Increase PWM frequency
	// TCCR0B = TCCR0B & B11111000 | B00000001; // D5 & D6
	TCCR1B = TCCR1B & B11111000 | B00000001; // D9 & D10
	TCCR2B = TCCR2B & B11111000 | B00000001; // D3 & D11

	// Stop motors
	Motors::stop();
}

void Motors::setPower(int powers[PROP_COUNT]){

	for(int i = 0; i < PROP_COUNT; i++){
		
		int tmpPower = map(powers[i], 0, 100, MOTOR_PW_MIN, MOTOR_PW_MAX);

		tmpPower = (tmpPower < MOTOR_PW_MIN) ? MOTOR_PW_MIN : tmpPower;
		tmpPower = (tmpPower > MOTOR_PW_MAX) ? MOTOR_PW_MAX : tmpPower;

		if(powers[i] >= 0)
			analogWrite(MOTOR_PINS[i], tmpPower);
		else
			digitalWrite(MOTOR_PINS[i], LOW);
	}
}

void Motors::stop(){
	int powers[] = {-1,-1,-1,-1,-1,-1};
	Motors::setPower(powers);
}