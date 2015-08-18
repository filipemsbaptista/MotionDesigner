#include "ofMain.h"
#include "ParticleSystemDemo.h"
#include "ParticleDemo.h"

int target = 0;

ParticleDemo::ParticleDemo(){
	live = false;
}

// ---------------------------------------------------------
ofPoint randomPointInCircle(float maxRad){
	ofPoint pnt;
	float rad = ofRandom(0, maxRad);
	float angle = ofRandom(0, M_TWO_PI);

	pnt.x = cos(angle) * rad;
	pnt.y = sin(angle) * rad;

	return pnt;
}

int acquireTarget(){
	target = target + 1;
	if(target > 14)
		target = 0;
	return target;
}
// ---------------------------------------------------------

void ParticleDemo::setup(){
	targetJoint = acquireTarget();

	//pos = ofPoint(paramsDemo.eCenter.x - (ofGetWidth()/2 + 8 + 10), paramsDemo.eCenter.y - (10 + 8 + 8 + 8)) + randomPointInCircle(paramsDemo.eRad);
	pos = paramsDemo.eCenter + randomPointInCircle(paramsDemo.eRad);
	vel = randomPointInCircle(paramsDemo.velRad);

	time = 0;
	lifeTime = paramsDemo.lifeTime;
	live = true;
	size = paramsDemo.size;
	force = paramsDemo.force;
	tracking = paramsDemo.tracking;
	}

void ParticleDemo::update(float dt, vector<ofPoint> joints){

	if(live){
		vel.rotate(0, 0, paramsDemo.rotate * dt);

		//Update pos
		pos += vel * dt;		//Euler method
		if(tracking){	
			pos.x += (((joints[targetJoint].x)) - pos.x) * ofRandom(force/2, force);		//The effect of the attraction force will be between the parametrized value and half of it
			pos.y += ((joints[targetJoint].y) - pos.y) * ofRandom(force/2, force);		//This avoids that every particle have the exact same speed
			pos.z += (joints[targetJoint].z - pos.z) * ofRandom(force/2, force);		
		}
	
		//Update time and check if particle should die
		time += dt;
		if(time >= lifeTime){
			live = false;		//Particle is now considered dead
		}

		cout << "Dest = (" << joints[targetJoint].x << ", " << joints[targetJoint].y << ", " << joints[targetJoint].z << ")" << endl;

	}
}

//During its lifetime, the size increases from 1 to 'size' and then decreases back
void ParticleDemo::draw(ofColor birthColor, ofColor deathColor){
	ofFill();

	if(live){
		//Compute size
		float pSize = ofMap(fabs(time - lifeTime/2), 0, lifeTime/2, size, 1);

		//Compute color
		newR = ofMap(time , 0, lifeTime, birthColor.r, deathColor.r);
		newG = ofMap(time , 0, lifeTime, birthColor.g, deathColor.g);
		newB = ofMap(time , 0, lifeTime, birthColor.b, deathColor.b);
		color = ofColor(newR, newG, newB);
		ofSetColor(color);

		ofCircle(pos, size);	//Draw particle
	}
}