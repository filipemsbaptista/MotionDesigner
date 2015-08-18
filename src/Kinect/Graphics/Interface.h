#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "SliderParams.h"

class Interface : public ofBaseApp{
	public:
		//Common
		int sceneType;		// 0 - Particle Systen, 1 - Joints Draw
		bool exploreVersion;
		bool exploring;

		void setup(int typeOfScene, bool isExplore);
		void update(int jointSelected);
		void draw();

		void keyPressed(int key);
		void exit(); 
		void guiEvent(ofxUIEventArgs &e);

		//-------------------

		//Particle System
		ofxUICanvas *gui1, *gui2, *gui3, *gui4;
		void setGUI1(float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity),
			setGUI2(), setGUI3();

		SliderParams sP;
		
		//-------------------

		//Joints Draw
		int selectedJoint;
		ofxUICanvas *guiInfo, *guiFPS, *guiJoints;
		ofxUICanvas *gui_Head, *gui_Neck, *gui_ShoulderL, *gui_ShoulderR, *gui_ElbowL, *gui_ElbowR, *gui_HandL, *gui_HandR, *gui_Torso, 
			*gui_HipL, *gui_HipR, *gui_KneeL, *gui_KneeR, *gui_FootL, *gui_FootR;
		void setGUI_Head(float *size, float *lifeTime, float *speed),
			setGUI_Neck(float *size, float *lifeTime, float *speed),
			setGUI_ShoulderL(float *size, float *lifeTime, float *speed),
			setGUI_ShoulderR(float *size, float *lifeTime, float *speed),
			setGUI_ElbowL(float *size, float *lifeTime, float *speed),
			setGUI_ElbowR(float *size, float *lifeTime, float *speed),
			setGUI_HandL(float *size, float *lifeTime, float *speed),
			setGUI_HandR(float *size, float *lifeTime, float *speed),
			setGUI_Torso(float *size, float *lifeTime, float *speed),
			setGUI_HipL(float *size, float *lifeTime, float *speed),
			setGUI_HipR(float *size, float *lifeTime, float *speed),
			setGUI_KneeL(float *size, float *lifeTime, float *speed),
			setGUI_KneeR(float *size, float *lifeTime, float *speed),
			setGUI_FootL(float *size, float *lifeTime, float *speed),
			setGUI_FootR(float *size, float *lifeTime, float *speed);
		void setGUIInfo(), setGUIFPS();

		SliderParams sP_Head, sP_Neck, sP_ShoulderL, sP_ShoulderR, sP_ElbowL, sP_ElbowR, sP_HandL, sP_HandR, sP_Torso,
			sP_HipL, sP_HipR, sP_KneeL, sP_KneeR, sP_FootL, sP_FootR;

		void showJointPanel(bool visible);
		void updateSliders(ofxUISlider *slider, int selectedJoint);
		
		bool jointsVisible;

		bool isActive_Head, isActive_Neck, isActive_ShoulderL, isActive_ShoulderR, isActive_ElbowL, isActive_ElbowR, isActive_HandL, isActive_HandR, isActive_Torso,
			isActive_HipL, isActive_HipR, isActive_KneeL, isActive_KneeR, isActive_FootL, isActive_FootR;
		bool isJointActive_Head();
	
		//-------------------
};