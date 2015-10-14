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
		void setGUI_Head(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_Neck(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_ShoulderL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_ShoulderR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_ElbowL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_ElbowR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_HandL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_HandR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_Torso(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_HipL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_HipR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_KneeL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_KneeR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_FootL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD),
			setGUI_FootR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD);
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