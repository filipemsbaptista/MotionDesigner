#pragma once

#include "ofMain.h"
#include "JointsDrawDemo.h"

class BrushDemo : public ofBaseApp{
public:
		void setup();						
		void update(float dt, vector<ofPoint> joints);		
		void draw(ofColor bColor);

		ofPoint pos;						//Position
		float size;							//Brush size
		float time;
		float speed;						//Tracknig speed
		bool active;

		bool drawing;						//Is brush being drawn

		int targetJoint;			//0 - Head, 1 - Center, 2 - Left Hand, 3 - Right Hand, 4 - Left Knee, 5 - Right Knee 
		int getTargetJoint();
		int acquireTarget();
};