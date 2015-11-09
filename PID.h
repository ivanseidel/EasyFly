#pragma once

class PID{
public:
	
	double error;
	double sample;
	double lastSample;
	double kP, kI, kD, iLimit;      
	double P, I, D;
	double pid;
	
	double setPoint;
	long lastProcess;
	
	PID(double _kP, double _kI, double _kD, double _iLimit);

	void reset();
	
	void addNewSample(double _sample);
	
	void setSetPoint(double _setPoint);
	
	double process(float deltaTime);
};