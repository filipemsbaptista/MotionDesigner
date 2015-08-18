#include "JointsSelector.h"


void JointsSelector::setup(){
	radius = 8;

	img.loadImage("body_silhouette.jpeg");

	fbo.allocate(img.width, img.height, GL_RGB32F_ARB);

	hover_head = hover_neck = hover_shoulderL = hover_shoulderR = hover_elbowL = hover_elbowR = hover_handL = hover_handR =
			hover_torso = hover_hipL = hover_hipR = hover_kneeL = hover_kneeR = hover_footL = hover_footR = false;

	jointSelected = 0;

	setupJointsPositions();
}

void JointsSelector::update(bool isActive_Head, bool isActive_Neck, bool isActive_ShoulderL, bool isActive_ShoulderR, bool isActive_ElbowL, bool isActive_ElbowR, bool isActive_HandL, bool isActive_HandR,
							bool isActive_Torso, bool isActive_HipL, bool isActive_HipR, bool isActive_KneeL, bool isActive_KneeR, bool isActive_FootL, bool isActive_FootR){
	headActivated = isActive_Head;
	neckActivated = isActive_Neck;
	shoulderLActivated = isActive_ShoulderL;
	shoulderRActivated = isActive_ShoulderR;
	elbowLActivated = isActive_ElbowL;
	elbowRActivated = isActive_ElbowR;
	handLActivated = isActive_HandL;
	handRActivated = isActive_HandR;
	torsoActivated = isActive_Torso;
	hipLActivated = isActive_HipL;
	hipRActivated = isActive_HipR;
	kneeLActivated = isActive_KneeL;
	kneeRActivated = isActive_KneeR;
	footLActivated = isActive_FootL;
	footRActivated = isActive_FootR;
}

void JointsSelector::draw(){
	fbo.begin();
	ofEnableSmoothing();

	//1. Draw body image
	ofSetColor(255,255,255);
	img.draw(0, 0);


	//2. Draw joints
	ofEnableAlphaBlending();  
	ofFill();
	ofSetColor(ofColor::green);
	drawJoints();

		
	//3. Draw bones
	drawBones();
		
	//Draw hover information
	if(hover_head){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(headPos.x, headPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_neck){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(neckPos.x, neckPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_shoulderL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(shoulderLPos.x, shoulderLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_shoulderR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(shoulderRPos.x, shoulderRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_elbowL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(elbowLPos.x, elbowLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_elbowR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(elbowRPos.x, elbowRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_handL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(handLPos.x, handLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_handR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(handRPos.x, handRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);

	}
	if(hover_torso){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(torsoPos.x, torsoPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_hipL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(hipLPos.x, hipLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_hipR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(hipRPos.x, hipRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_kneeL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(kneeLPos.x, kneeLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_kneeR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(kneeRPos.x, kneeRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_footL){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(footLPos.x, footLPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	if(hover_footR){
		ofNoFill();
		ofSetLineWidth(4);
		ofSetColor(ofColor::grey);
		ofCircle(footRPos.x, footRPos.y, 1, radius);
		ofFill();
		ofSetLineWidth(1);
	}
	fbo.end();
	glEnable(GL_BLEND);  
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

	ofSetColor(255,255,255);
	fbo.draw(ofGetWidth() - fbo.getWidth() - 15, 50);
	ofDrawBitmapString( "Joints:", ofGetWidth() - fbo.getWidth() - 15, 40);

	//Draw Joint GUI
	switch (jointSelected){
		case 0:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + headPos.x, 50 + headPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 1:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + neckPos.x, 50 + neckPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 2:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + shoulderLPos.x, 50 + shoulderLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 3:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + shoulderRPos.x, 50 + shoulderRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 4:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + elbowLPos.x, 50 + elbowLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 5:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + elbowRPos.x, 50 + elbowRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 6:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + handLPos.x, 50 + handLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 7:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + handRPos.x, 50 + handRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 8:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + torsoPos.x, 50 + torsoPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 9:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + hipLPos.x, 50 + hipLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 10:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + hipRPos.x, 50 + hipRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 11:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + kneeLPos.x, 50 + kneeLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 12:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + kneeRPos.x, 50 + kneeRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 13:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + footLPos.x, 50 + footLPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
		case 14:
			ofNoFill();
			ofSetLineWidth(3);
			ofCircle(ofGetWidth() - fbo.getWidth() - 16 + footRPos.x, 50 + footRPos.y, 1, radius + 1);
			ofSetLineWidth(1);
			break;
	}
}

void JointsSelector::setupJointsPositions(){
	headPos = ofPoint(fbo.getWidth()/2, 25);
	neckPos = ofPoint(fbo.getWidth()/2, 65);
	shoulderLPos = ofPoint(fbo.getWidth()/2 - 30, 75);
	shoulderRPos = ofPoint(fbo.getWidth()/2 + 30, 75);
	elbowLPos = ofPoint(fbo.getWidth()/2 - 40, 125);
	elbowRPos = ofPoint(fbo.getWidth()/2 + 40, 125);
	handLPos = ofPoint(fbo.getWidth()/2 - 58, 185);
	handRPos = ofPoint(fbo.getWidth()/2 + 58, 185);
	torsoPos = ofPoint(fbo.getWidth()/2, 120);
	hipLPos = ofPoint(fbo.getWidth()/2 - 20, 170);
	hipRPos = ofPoint(fbo.getWidth()/2 + 20, 170);
	kneeLPos = ofPoint(fbo.getWidth()/2 - 18, 240);
	kneeRPos = ofPoint(fbo.getWidth()/2 + 20, 240);
	footLPos = ofPoint(fbo.getWidth()/2 - 21, 305);
	footRPos = ofPoint(fbo.getWidth()/2 + 26, 305);
}

void JointsSelector::drawJoints(){
	//Draw head joint
		if(headActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(headPos.x, headPos.y, 1, radius);

		//Draw neck joint
		if(neckActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(neckPos.x, neckPos.y, 1, radius);

		//Draw shoulders joints
		if(shoulderLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(shoulderLPos.x, shoulderLPos.y, 1, radius);

		if(shoulderRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(shoulderRPos.x, shoulderRPos.y, 1, radius);

		//Draw elbows joints
		if(elbowLActivated)
			ofFill();	
		else
			ofNoFill();
		ofCircle(elbowLPos.x, elbowLPos.y, 1, radius);

		if(elbowRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(elbowRPos.x, elbowRPos.y, 1, radius);

		//Draw hands joints
		if(handLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(handLPos.x, handLPos.y, 1, radius);

		if(handRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(handRPos.x, handRPos.y, 1, radius);

		//Draw torso joint
		if(torsoActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(torsoPos.x, torsoPos.y, 1, radius);

		//Draw hips joints
		if(hipLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(hipLPos.x, hipLPos.y, 1, radius);

		if(hipRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(hipRPos.x, hipRPos.y, 1, radius);

		//Draw knees joints
		if(kneeLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(kneeLPos.x, kneeLPos.y, 1, radius);

		if(kneeRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(kneeRPos.x, kneeRPos.y, 1, radius);

		//Draw feet joints
		if(footLActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(footLPos.x, footLPos.y, 1, radius);

		if(footRActivated)
			ofFill();		
		else
			ofNoFill();
		ofCircle(footRPos.x, footRPos.y, 1, radius);
}

void JointsSelector::drawBones(){
		ofLine(ofPoint(headPos.x, headPos.y + radius), ofPoint(neckPos.x, neckPos.y - radius));
		ofLine(ofPoint(neckPos.x - radius, neckPos.y), ofPoint(shoulderLPos.x + radius, shoulderLPos.y - 5));
		ofLine(ofPoint(neckPos.x + radius, neckPos.y), ofPoint(shoulderRPos.x - radius, shoulderRPos.y - 5));
		ofLine(ofPoint(shoulderLPos.x - 3, shoulderLPos.y + 8), ofPoint(elbowLPos.x + 2, elbowLPos.y - 8));
		ofLine(ofPoint(shoulderRPos.x + 3, shoulderRPos.y + 8), ofPoint(elbowRPos.x - 2, elbowRPos.y - 8));
		ofLine(ofPoint(elbowLPos.x - 2, elbowLPos.y + 8), ofPoint(handLPos.x + 2, handLPos.y - 8));
		ofLine(ofPoint(elbowRPos.x + 2, elbowLPos.y + 8), ofPoint(handRPos.x - 2, handLPos.y - 8));
		ofLine(ofPoint(shoulderLPos.x + radius - 2, shoulderLPos.y + radius - 3), ofPoint(torsoPos.x - 3, torsoPos.y - radius));
		ofLine(ofPoint(shoulderRPos.x - radius + 2, shoulderRPos.y + radius - 3), ofPoint(torsoPos.x + 3, torsoPos.y - radius));
		ofLine(ofPoint(torsoPos.x - 3, torsoPos.y + radius), ofPoint(hipLPos.x + 2, hipLPos.y - radius));
		ofLine(ofPoint(torsoPos.x + 3, torsoPos.y + radius), ofPoint(hipRPos.x - 2, hipRPos.y - radius));
		ofLine(ofPoint(hipLPos.x + radius, hipLPos.y), ofPoint(hipRPos.x - radius, hipRPos.y));
		ofLine(ofPoint(hipLPos.x, hipLPos.y + radius), ofPoint(kneeLPos.x, kneeLPos.y - radius));
		ofLine(ofPoint(hipRPos.x, hipRPos.y + radius), ofPoint(kneeRPos.x, kneeRPos.y - radius));
		ofLine(ofPoint(kneeLPos.x, kneeLPos.y + radius), ofPoint(footLPos.x, footLPos.y - radius));
		ofLine(ofPoint(kneeRPos.x, kneeRPos.y + radius), ofPoint(footRPos.x, footRPos.y - radius));
}

int JointsSelector::getJointSelected(){
	return jointSelected;
}

void JointsSelector::keyPressed(int key){
	
}

void JointsSelector::keyReleased(int key){

}

void JointsSelector::mouseMoved(int mouseX, int mouseY ){
	//Check if mouse is inside joints selector
	if(mouseX > ofGetWidth() - fbo.getWidth() - 15 && mouseX < ofGetWidth() - 15 && mouseY > 50 && mouseY < 50 + fbo.getHeight()){
		
		//CHECK MOUSE HOVER
		//Head
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + headPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + headPos.x - radius)
			&& mouseY > (50 + headPos.y - radius) && mouseY < (50 + headPos.y + radius)){
			hover_head = true;
		}
		else
			hover_head = false;
		//Neck
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + neckPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + neckPos.x - radius)
			&& mouseY > (50 + neckPos.y - radius) && mouseY < (50 + neckPos.y + radius)){
			hover_neck = true;
		}
		else
			hover_neck = false;
		//Shoulders
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + shoulderLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + shoulderLPos.x - radius)
			&& mouseY > (50 + shoulderLPos.y - radius) && mouseY < (50 + shoulderLPos.y + radius)){
			hover_shoulderL = true;
		}
		else
			hover_shoulderL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + shoulderRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + shoulderRPos.x - radius)
			&& mouseY > (50 + shoulderRPos.y - radius) && mouseY < (50 + shoulderRPos.y + radius)){
			hover_shoulderR = true;
		}
		else
			hover_shoulderR = false;
		//Elbows
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + elbowLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + elbowLPos.x - radius)
			&& mouseY > (50 + elbowLPos.y - radius) && mouseY < (50 + elbowLPos.y + radius)){
			hover_elbowL = true;
		}
		else
			hover_elbowL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + elbowRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + elbowRPos.x - radius)
			&& mouseY > (50 + elbowRPos.y - radius) && mouseY < (50 + elbowRPos.y + radius)){
			hover_elbowR = true;
		}
		else
			hover_elbowR= false;
		//Hands
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + handLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + handLPos.x - radius)
			&& mouseY > (50 + handLPos.y - radius) && mouseY < (50 + handLPos.y + radius)){
			hover_handL = true;
		}
		else
			hover_handL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + handRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + handRPos.x - radius)
			&& mouseY > (50 + handRPos.y - radius) && mouseY < (50 + handRPos.y + radius)){
			hover_handR = true;
		}
		else
			hover_handR = false;
		//Torso
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + torsoPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + torsoPos.x - radius)
			&& mouseY > (50 + torsoPos.y - radius) && mouseY < (50 + torsoPos.y + radius)){
			hover_torso = true;
		}
		else
			hover_torso = false;
		//Hips
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + hipLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + hipLPos.x - radius)
			&& mouseY > (50 + hipLPos.y - radius) && mouseY < (50 + hipLPos.y + radius)){
			hover_hipL = true;
		}
		else
			hover_hipL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + hipRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + hipRPos.x - radius)
			&& mouseY > (50 + hipRPos.y - radius) && mouseY < (50 + hipRPos.y + radius)){
			hover_hipR = true;
		}
		else
			hover_hipR = false;
		//Knees
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + kneeLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + kneeLPos.x - radius)
			&& mouseY > (50 + kneeLPos.y - radius) && mouseY < (50 + kneeLPos.y + radius)){
			hover_kneeL = true;
		}
		else
			hover_kneeL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + kneeRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + kneeRPos.x - radius)
			&& mouseY > (50 + kneeRPos.y - radius) && mouseY < (50 + kneeRPos.y + radius)){
			hover_kneeR = true;
		}
		else
			hover_kneeR = false;
		//Feet
		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + footLPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + footLPos.x - radius)
			&& mouseY > (50 + footLPos.y - radius) && mouseY < (50 + footLPos.y + radius)){
			hover_footL = true;
		}
		else
			hover_footL = false;

		if(mouseX < (ofGetWidth() - fbo.getWidth() - 15 + footRPos.x + radius) && mouseX > (ofGetWidth() - fbo.getWidth() - 15 + footRPos.x - radius)
			&& mouseY > (50 + footRPos.y - radius) && mouseY < (50 + footRPos.y + radius)){
			hover_footR = true;
		}
		else
			hover_footR = false;
		//---------------- END OF HOVER CHECK  ----------------
	}
}

void JointsSelector::mouseDragged(int x, int y, int button){

}

void JointsSelector::mousePressed(int x, int y, int button){
}

void JointsSelector::mouseReleased(int x, int y){
	if(hover_head){
		jointSelected = 0;
	}
	if(hover_neck){
		jointSelected = 1;
	}
	if(hover_shoulderL){
		jointSelected = 2;
	}
	if(hover_shoulderR){
		jointSelected = 3;
	}
	if(hover_elbowL){
		jointSelected = 4;

	}
	if(hover_elbowR){
		jointSelected = 5;
	}
	if(hover_handL){
		jointSelected = 6;
	}
	if(hover_handR){
		jointSelected = 7;
	}
	if(hover_torso){
		jointSelected = 8;
	}
	if(hover_hipL){
		jointSelected = 9;
	}
	if(hover_hipR){
		jointSelected = 10;
	}
	if(hover_kneeL){
		jointSelected = 11;
	}
	if(hover_kneeR){
		jointSelected = 12;
	}
	if(hover_footL){
		jointSelected = 13;
	}
	if(hover_footR){
		jointSelected = 14;
	}
}

void JointsSelector::windowResized(int w, int h){

}

void JointsSelector::gotMessage(ofMessage msg){

}

void JointsSelector::dragEvent(ofDragInfo dragInfo){ 

}
