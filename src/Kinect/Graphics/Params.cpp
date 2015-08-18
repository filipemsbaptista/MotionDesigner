#include "Params.h"

void Params::setup(int sceneType){
	switch(sceneType){
	case 0:		//Particle System
		eCenter = ofPoint(ofGetWidth()/2, ofGetHeight()/2, 1);
		eRad = 40;
		bornRate = 178;
		bornCount = 0;
		velRad = 200;
		lifeTime_PS = 5.0;
		rotate = 2;
		size_PS = 1;
		Zintensity = 2;
		force = 0.03;
		tracking = true;
		break;
	case 1:		//Joints Draw
		size_JD = 20;
		speed = 0.1;
		lifeTime_JD = 50.0;
		drawing = true;
		break;
	}
	
}