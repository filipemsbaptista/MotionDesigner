#include "ofMain.h"
#include "Particle.h"

int _target = 0;

Particle::Particle(){
	live = false;
}

// ---------------------------------------------------------
ofPoint Particle::randomPointInCircle(float maxRad){
	ofPoint pnt;
	float rad = ofRandom(0, maxRad);
	float angle = ofRandom(0, M_TWO_PI);

	pnt.x = cos(angle) * rad;
	pnt.y = sin(angle) * rad;

	return pnt;
}

int Particle::acquireTarget(){
	_target = _target + 1;
	if(_target > 14)
		_target = 0;
	return _target;
}
// ---------------------------------------------------------

void Particle::setup(){
	pos = param.eCenter + randomPointInCircle(param.eRad);
	vel = randomPointInCircle(param.velRad);

	time = 0;
	lifeTime = param.lifeTime_PS;
	live = true;
	size = param.size_PS;
	force = param.force;
	tracking = param.tracking;

	targetJoint = acquireTarget();

}

void Particle::update(float dt, float destX, float destY, float destZ){

	if(live){
		//Rotate vel
		vel.rotate(0, 0, param.rotate * dt);

		//Update pos
		pos += vel * dt;		//Euler method
		if(tracking){	
			pos.x += (destX - pos.x) * ofRandom(force/2, force);		//The effect of the attraction force will be between the parametrized value and half of it
			pos.y += (-destY - pos.y) * ofRandom(force/2, force);		//This avoids that every particle have the exact same speed
			pos.z += (destZ - pos.z) * ofRandom(force/2, force);		
		}
		//We calculate the x and y distance of the ball to the mouse position and
		// add a little portion of it to the x and y variables

		//Update time and check if particle should die
		time += dt;
		if(time >= lifeTime){
			live = false;		//Particle is now considered dead
		}
	}
}

//During its lifetime, the size increases from 1 to 'size' and then decreases back
void Particle::draw(ofColor birthColor, ofColor deathColor){
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

int Particle::getTargetJoint(){
	return targetJoint;
}