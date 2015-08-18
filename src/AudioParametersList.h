#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class AudioParametersList : public ofBaseApp{
	public:
		void setup(float beginning, float ending);
		void update(bool isSelected, float beginning, float ending, bool showScenesPalette, bool showSoundsPanel);
		void exit();
		
		void mouseReleased(int x, int y, float beginning, float ending);
		
		void guiEvent(ofxUIEventArgs &e);

		vector <string> controllers, joints;
		int trackingReference_Speed, trackingReference_Volume, trackingReference_Pan;	// 0 - X-axis;	1 - Y-axis;	2 - Distance to marker;	3 - Distance to mouse
		int joint_Speed, joint_Volume, joint_Pan;	//0 - Head, 1 - Neck, 2 - Shoulder L, 3 - Shoulder R, 4 - Elbow L, 5 - Elbow R, 6 - Hand L, 7 - Hand R, 8 - Torso,
													//9 - Hip L, 10 - Hip R, 11 - Knee L, 12 - Knee R, 13 - Foot L, 14 - Foot R
		

		vector<vector<float>> parameters;
		vector <vector<float>> sliders_parameters;

		void pasteSettings();

		void addTimestamp(float timestamp, float speedJoint, float speedRef, float volumeJoint, float volumeRef, float panningJoint, float panningRef);
		vector<float> newTimestamp(float timestamp, float speedJoint, float speedRef, float volumeJoint, float volumeRef, float panningJoint, float panningRef);
		vector<vector<float>> selectionSort(vector<vector<float>> parameters);

		ofxUICanvas *ddl_gui, *gui; 
		ofxUIDropDownList *ddl;
		ofxUIDropDownList *ddl_speed, *ddl_volume, *ddl_pan, *ddl_joints_speed, *ddl_joints_volume, *ddl_joints_pan;

		vector<string> timestamps;
		vector<ofxUICanvas*> guis;

		ofxUICanvas* createParametersGUI(int index);

		bool selected;
		void showSelectedParametersGUI(bool showScenesPalette, bool showSoundsPanel);

		bool canAddTimestamp;
		void deleteTimestamp();
};