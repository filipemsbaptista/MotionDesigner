#include "BrushDemo.h"

int myTarget = -1;

//----------------------------------
int BrushDemo::acquireTarget(){
	myTarget = myTarget + 1;
	if(myTarget > 14)
		myTarget = 0;
	cout << "\n (My target is: " << myTarget << ")" << endl;
	return myTarget;
}
//----------------------------------

void BrushDemo::setup(){
	pos = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	time = 0;
	size = params.size;
	speed  = params.speed;

	targetJoint = acquireTarget();
}

void BrushDemo::update(float dt, vector<ofPoint> joints){
	size = params.size;
	speed  = params.speed;
	
	pos.x += ((joints[targetJoint].x) - pos.x) * speed;
	pos.y += ((joints[targetJoint].y) - pos.y) * speed;
	pos.z += (joints[targetJoint].z - pos.z) * speed;
}

void BrushDemo::draw(ofColor bColor){
	if(!drawing)
		ofSetColor(bColor.r, bColor.g, bColor.b, 0);
	else
		ofSetColor(bColor);

	ofCircle(pos, size);
}