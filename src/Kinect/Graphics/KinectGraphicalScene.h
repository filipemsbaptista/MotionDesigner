#pragma once

#include "ofMain.h"
#include "Interface.h"
#include "JointsSelector.h"
#include "Params.h"
#include "Particle.h"
#include "Brush.h"
#include "NiTE.h"

//Declaration of a global variable for paramters class, through which all the parameters are acessed
//Particle System
extern Params param;
//Joints Draw
extern Params param_General, param_Head, param_Neck, param_ShoulderL, param_ShoulderR, param_ElbowL, param_ElbowR, param_HandL, param_HandR,
	param_Torso, param_HipL, param_HipR, param_KneeL, param_KneeR, param_FootL, param_FootR;

class KinectGraphicalScene : public ofBaseApp{
public:
	int sceneType;
	void setup(int typeOfScene, bool isExplore);
	void update();
	void draw();
 
	//GUI
	Interface interf;
	JointsSelector jointsSelector;
	bool drawInterface;

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float destX, destY, destZ;

	ofPoint headPos, neckPos, handLPos, elbowLPos, handRPos,
		elbowRPos, shoulderLPos, shoulderRPos, torsoPos, hipLPos, hipRPos,
		kneeLPos, kneeRPos, footLPos, footRPos, centerPos;
	bool drawSkeleton;

	bool exploreVersion;

	//Kinect
	nite::Status niteRc;
	nite::UserTracker userTracker;
	nite::UserTrackerFrameRef userTrackerFrame;

	void updateUserState(const nite::UserData& user, unsigned long long ts);
	void drawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2);


};
