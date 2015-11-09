#include "_config.h"
#include "_types.h"

#include "Arduino.h"

#include "Drone.h"
#include "System.h"
#include "Motors.h"
#include "Attitude.h"

// <Fast Forward declaration>
void heartBeat_callback();
void serialDebug_callback();
void batteryChecker_callback();

ThreadController System;

Thread heartBeat;
Thread serialDebug;
Thread batteryChecker;

void system_init(){

	// Setup Pins
	pinMode(PIN_LED, OUTPUT);

	// Serial
	Serial.begin(SERIAL_SPEED);
	while(!Serial);
	
	// Startup Message
	LOG("\n\nUP! "); LOG(PROJECT_NAME); LOG("\n");

	// Setup HeartBeat
	heartBeat.setInterval(500);
	heartBeat.onRun(heartBeat_callback);

	// Setup Serial Debug
	serialDebug.setInterval(10);
	serialDebug.onRun(serialDebug_callback);

	// Battery Checker
	batteryChecker.setInterval(4000);
	batteryChecker.onRun(batteryChecker_callback);

	// Add Threads to System
	System.add(&heartBeat);
	System.add(&serialDebug);
	System.add(&batteryChecker);
};


bool ledState = false;
void heartBeat_callback(){
	// Blinking
	ledState = !ledState;
	digitalWrite(PIN_LED, ledState);

	
	if(Drone::vbat <= BAT_WARNING){
		// Battery warning
		heartBeat.setInterval(ledState ? 100 : 900);
	}else if(Drone::state == ARMED){
		// Drone is Flying!
		heartBeat.setInterval(100);
	}else if(Drone::state != STOPPED){
		// Drone is Alarmed
		heartBeat.setInterval(ledState ? 900 : 100);
	}else{
		// No state (IDDLE)
		heartBeat.setInterval(ledState ? 50 : 2000);
	}

}


void serialDebug_callback(){
	if(!Serial.available())
		return;

	char cmd = Serial.read();

	if(cmd == 'p'){
		// Ping Back
		LOG("$ Ping back\n");
	}else if(cmd == '1'){
		Drone::setState(ARMED);
	}else if(cmd == '0'){
		Drone::setState(STOPPED);
	}else if(cmd == 'i'){
		LOG("$ Toggling DEBUG in IMU\n");
		threadDebug.enabled = !threadDebug.enabled;
	}else if(cmd == 'v'){
		LOG("$ Battery: "); LOG(Drone::vbat); LOG("\n");
	}

}

int criticals = 0;
void batteryChecker_callback(){

	Drone::vbat = BAT_TO_VOLTAGE(analogRead(PIN_VBAT));

	if(Drone::vbat <= BAT_CRITICAL){
		criticals ++;
		if(criticals >= 3){
			Drone::setState(ALARM_LOW_BATTERY);
		}
	}else if(Drone::state == ALARM_LOW_BATTERY){
		criticals = 0;
		Drone::setState(STOPPED);
	}
}