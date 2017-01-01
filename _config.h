#pragma once

#include <Arduino.h>

//
// Util Math
//
#define TO_RAD(deg)						(deg * M_PI / 180)


//
// Project
//
#define PROJECT_NAME					"EasyFlyLive v0.1"


//
// Serial
//
#define SERIAL_SPEED					57600
#define LOG								Serial.print


//
// Battery
//
#define BAT_WARNING						3.6
#define BAT_CRITICAL					3.4
#define BAT_TO_VOLTAGE(adc)				(7.7567 - (adc*0.0044))


//
// Pins
//
#define PIN_LED							8
#define PIN_VBAT						A0


//
// I2C
//
#define I2C_SPEED						400
#define I2C_PULLUPS_ENABLE				PORTC |= 1<<4; PORTC |= 1<<5 // Pins A4/A5 to PU


//
// IMU (MOU6050)
//
#define IMU_I2C_ADR						0x68


//
// Stability Checks
//
#define STABILITY_GRAVITY_Z_MIN			0.5


//
// Propeler Positions in the Drone
//
#define PROP_COUNT						6


//
// Motors
//
#define MOTOR_PW_MAX					255
#define MOTOR_PW_MIN					30

#define MOTOR_PIN_1 					9
#define MOTOR_PIN_2 					6
#define MOTOR_PIN_3 					5
#define MOTOR_PIN_4 					3
#define MOTOR_PIN_5 					11
#define MOTOR_PIN_6 					10

const int MOTOR_PINS[PROP_COUNT] = {
	MOTOR_PIN_1,
	MOTOR_PIN_2,
	MOTOR_PIN_3,
	MOTOR_PIN_4,
	MOTOR_PIN_5,
	MOTOR_PIN_6
};
