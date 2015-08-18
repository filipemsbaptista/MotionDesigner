#pragma once

#include "ofMain.h"

class SliderParams{
public:
	//Particle System
	float *force, *size_PS, *lifeTime_PS, *history, *rotate, *eRad, *bornRate, *velRad;
	int *Zintesity;

	//Joints Draw
	float *size_JD, *lifeTime_JD, *speed;

};