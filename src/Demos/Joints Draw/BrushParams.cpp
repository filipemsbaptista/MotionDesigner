#include "BrushParams.h"

void BrushParams::setup(){
	size = 20;
	speed = 0.1;

	drawing = true;

	color = (ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
}