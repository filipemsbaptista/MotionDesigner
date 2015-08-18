#pragma once

#include "ofMain.h"

//Each parameter should be accessible by all the particles, and global variables can do that.
//But, it is better not to use many global variables, and hence we combine all the parameters in this separate class and declare just one global variable.

class Params{
	public:
		void setup(int sceneType);		// 0 - Particle System;	1 - Joints Draw

		// --- Particle System ---
		//Emitter
		ofPoint eCenter;		//Emitter center
		float eRad;				//Emitter Radius
		float bornRate;			//Particles born rate per second
		float bornCount;		//Integrated number of particles to born

		//Particle
		float velRad;			//Initial velocity limit
		float lifeTime_PS;		//Lifetime in seconds
		float size_PS;			//Maximum particle size
		float rotate;			//Direction rotation speed in angles per degrees
		int Zintensity;			//How much the user's distance from the camera affects the particles z coordinate
		
		//Tracking
		float force;			//Intensity of mouse attraction
		float tracking;			//Is particle tracking mouse
		
		//-----------------------------------------------------

		// --- Joints Draw ---
		float size_JD;			//Brush size
		float speed;			//Speed of tracking
		float lifeTime_JD;		//Ink trail
		bool drawing;			//Is joint drawing
};