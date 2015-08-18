#pragma once

#include "ofMain.h"
#include "ParamsDemo.h"
#include "ParticleDemo.h"

//Declaration of a global variable for paramters class, through which all the parameters are acessed
extern ParamsDemo paramsDemo;

class ParticleSystemDemo : public ofBaseApp{
	public:
		void setup(int x, int y, int width, int height);
		void update(int x, int y, int width, int height);
		void updateParameters(vector<vector<float>> parameters, float currentTime);
		void draw(bool skeletonVisible);
 
		void windowResized(int x, int y, int w, int h);

		ofColor getBackgroundColor();


		deque<ParticleDemo> particles;	//Particles

		//Virtual skeleton
		ofPoint head, neck, shoulderL, shoulderR, elbowL, elbowR, handL, handR, torso, hipL, hipR, kneeL, kneeR, footL, footR;
		bool head_goingLeft, elbowL_goingLeft, handL_goingLeft, kneeR_goingLeft;
		bool head_ascending, elbowL_ascending, handL_ascending, kneeR_ascending;

		vector<ofPoint> joints;
		void setupJoints(int screenCenterX, int screenCenterY);
		void updateJoints();
		void drawJoints();


		ofColor backgroundColor;
};
