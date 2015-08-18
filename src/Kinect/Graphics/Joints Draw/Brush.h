#pragma once

#include "ofMain.h"
#include "KinectGraphicalScene.h"

class Brush{
	public:
		void setup(bool isActive_Head, bool isActive_Neck, bool isActive_ShoulderL, bool isActive_ShoulderR, bool isActive_ElbowL, bool isActive_ElbowR, bool isActive_HandL, bool isActive_HandR,
			bool isActive_Torso, bool isActive_HipL, bool isActive_HipR, bool isActive_KneeL, bool isActive_KneeR, bool isActive_FootL, bool isActive_FootR);						
		void update(float dt,
			float destX,
			float destY,
			float destZ);					
		void draw(ofColor bColor);			

		ofPoint pos;						//Position
		float size;							//Brush size
		float time;
		float speed;						//Tracknig speed
		bool active;

		bool drawing;						//Is brush being drawn

		ofColor color;
		float newR, newG, newB;

		
		int targetJoint;			//0 - Head, 1 - Center, 2 - Left Hand, 3 - Right Hand, 4 - Left Knee, 5 - Right Knee 
		int getTargetJoint();
		int acquireTarget();
};