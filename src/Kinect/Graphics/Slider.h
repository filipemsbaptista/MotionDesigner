#pragma once

#include "ofMain.h"

//Slider class
class Slider {
public:
	string title;		//Title
	ofRectangle rect;	//Rectangle for drawing
	float *value;       //Pointer to value which the slider changes
	float minV, maxV;   //Minimum and maximum values
};
