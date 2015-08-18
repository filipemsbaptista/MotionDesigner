#include "Brush.h"

int newTarget = -1;

//----------------------------------
int Brush::acquireTarget(){
	newTarget = newTarget + 1;
	if(newTarget > 14)
		newTarget = 0;
	cout << "\n (My target is: " << newTarget << ")" << endl;
	return newTarget;
}
//----------------------------------

void Brush::setup(bool isActive_Head, bool isActive_Neck, bool isActive_ShoulderL, bool isActive_ShoulderR, bool isActive_ElbowL, bool isActive_ElbowR, bool isActive_HandL, bool isActive_HandR,
			bool isActive_Torso, bool isActive_HipL, bool isActive_HipR, bool isActive_KneeL, bool isActive_KneeR, bool isActive_FootL, bool isActive_FootR){
	
	pos = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));

	time = 0;

	switch (targetJoint){
	case 0:
		if(isActive_Head){
			size = param_Head.size_JD;
			speed  = param_Head.speed;
			break;
		}
	case 1:
		if(isActive_Neck){
			size = param_Neck.size_JD;
			speed  = param_Neck.speed;
			break;
		}
	case 2:
		if(isActive_ShoulderL){
			size = param_ShoulderL.size_JD;
			speed  = param_ShoulderL.speed;
			break;
		}
	case 3:
		if(isActive_ShoulderR){
			size = param_ShoulderR.size_JD;
			speed  = param_ShoulderR.speed;
			break;
		}
	case 4:
		if(isActive_ElbowL){
			size = param_ElbowL.size_JD;
			speed  = param_ElbowL.speed;
			break;
		}
	case 5:
		if(isActive_ElbowR){
			size = param_ElbowR.size_JD;
			speed  = param_ElbowR.speed;
			break;
		}
	case 6:
		if(isActive_HandL){
			size = param_HandL.size_JD;
			speed  = param_HandL.speed;
			break;
		}
	case 7:
		if(isActive_HandR){
			size = param_HandR.size_JD;
			speed  = param_HandR.speed;
			break;
		}
	case 8:
		if(isActive_Torso){
			size = param_Torso.size_JD;
			speed  = param_Torso.speed;
			break;
		}
	case 9:
		if(isActive_HipL){
			size = param_HipL.size_JD;
			speed  = param_HipL.speed;
			break;
		}
	case 10:
		if(isActive_HipR){
			size = param_HipR.size_JD;
			speed  = param_HipR.speed;
			break;
		}
	case 11:
		if(isActive_KneeL){
			size = param_KneeL.size_JD;
			speed  = param_KneeL.speed;
			break;
		}
	case 12:
		if(isActive_KneeR){
			size = param_KneeR.size_JD;
			speed  = param_KneeR.speed;
			break;
		}
	case 13:
		if(isActive_FootL){
			size = param_FootL.size_JD;
			speed  = param_FootL.speed;
			break;
		}
	case 14:
		if(isActive_FootR){
			size = param_FootR.size_JD;
			speed  = param_FootR.speed;
			break;
		}
	default:
		break;
	}

	targetJoint = acquireTarget();

}

void Brush::update(float dt, float destX, float destY, float destZ){

	switch (targetJoint){
		case 0:
			size = param_Head.size_JD;
			speed  = param_Head.speed;
			break;
		case 1:
			size = param_Neck.size_JD;
			speed  = param_Neck.speed;
			break;
		case 2:
			size = param_ShoulderL.size_JD;
			speed  = param_ShoulderL.speed;
			break;
		case 3:
			size = param_ShoulderR.size_JD;
			speed  = param_ShoulderR.speed;
			break;
		case 4:
			size = param_ElbowL.size_JD;
			speed  = param_ElbowL.speed;
			break;
		case 5:
			size = param_ElbowR.size_JD;
			speed  = param_ElbowR.speed;
			break;
		case 6:
			size = param_HandL.size_JD;
			speed  = param_HandL.speed;
			break;
		case 7:
			size = param_HandR.size_JD;
			speed  = param_HandR.speed;
			break;
		case 8:
			size = param_Torso.size_JD;
			speed  = param_Torso.speed;
			break;
		case 9:
			size = param_HipL.size_JD;
			speed  = param_HipL.speed;
			break;
		case 10:
			size = param_HipR.size_JD;
			speed  = param_HipR.speed;
			break;
		case 11:
			size = param_KneeL.size_JD;
			speed  = param_KneeL.speed;
			break;
		case 12:
			size = param_KneeR.size_JD;
			speed  = param_KneeR.speed;
			break;
		case 13:
			size = param_FootL.size_JD;
			speed  = param_FootL.speed;
			break;
		case 14:
			size = param_FootR.size_JD;
			speed  = param_FootR.speed;
			break;
	}

	pos.x += (destX - pos.x) * speed;		
	pos.y += (-destY - pos.y) * speed;	
	pos.z += (destZ - pos.z) * speed;	
}

void Brush::draw(ofColor bColor){
		if(!drawing)
			ofSetColor(bColor.r, bColor.g, bColor.b, 0);
		else
			ofSetColor(bColor);

		ofCircle(pos, size);
}

int Brush::getTargetJoint(){
	return targetJoint;
}