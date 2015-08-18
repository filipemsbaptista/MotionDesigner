#pragma once

#include "ofMain.h"


class ParticleDemo{
	public:
		ParticleDemo();							//Class constructor
		void setup();						//Start particle
		void update(float dt, vector<ofPoint> joints);					//Recalculate physics
		void draw(ofColor pColor1, ofColor pColor2);			//Draw particle

		ofPoint pos;						//Position
		ofPoint vel;						//Velocity
		float time;							//Time of living
		float lifeTime;						//Allowed lifetime
		float size;							//Maximum particle size
		bool live;							//Is particle alive

		float force;						//Intensity of mouse attraction
		bool tracking;						//Is particle tracking mouse

		ofColor color;
		float newR, newG, newB;

		int targetJoint;			//0 - Head, 1 - Neck, 2 - Left Shoulder, 3 - Right Shoulder, 4 - Left Elbow, 5 - Right Elbow,
									//6 - Left Hand, 7 - Right Hand, 8 - Torso, 9 - Left Hip, 10 - Right Hip, 11 - Left Knee, 12 - Right Knee, 13 - Left Foot, 14 - Right Foot

};