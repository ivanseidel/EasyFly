#include "_types.h"

#include "PID.h"

PID::PID(double _kP, double _kI, double _kD, double _iLimit){
	kP = _kP;
	kI = _kI;
	kD = _kD;
	iLimit = _iLimit;
}
	
void PID::reset(){
	P = I = D = 0;
}

void PID::addNewSample(double _sample){
	sample = _sample;
}

void PID::setSetPoint(double _setPoint){
	setPoint = _setPoint;
}

double PID::process(float deltaTime){
	// Implementação P ID
	error = setPoint - sample;
	
	//P
	P = error * kP;
	
	//I
	I = I + (error * kI) * deltaTime;
	I = (I >  iLimit) ?  iLimit : I;
	I = (I < -iLimit) ? -iLimit : I;

	//D
	D = (lastSample - sample) * kD / deltaTime;
	lastSample = sample;
	
	// Sums
	pid = P + I + D;
	
	return pid;
}