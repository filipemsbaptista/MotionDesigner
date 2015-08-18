#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class GraphicsParametersList : public ofBaseApp{
	public:
		void setup(int sceneType, float beginning, float ending);
		void update(bool isSelected, float beginning, float ending, bool showScenesPalette, bool showSoundsPanel);
		void draw(float maxTime);
		void exit();
		
		void mouseDragged(int x, int y);
		void mousePressed(int x, int y);
		void mouseReleased(int x, int y, float beginning, float ending);
		void mouseMoved(int x, int y );
		
		void windowResized(int w, int h);
		void guiEvent(ofxUIEventArgs &e);


		vector<vector<float>> parameters;
		vector <vector<float>> sliders_parameters;

		void pasteSettings();


		void addTimestamp(float timestamp, float force, float size, float lifeTime, float history, float rotation, float eRad, float bornRate, float velRad, float sizeBrush, float lifeTimeBrush, float speed);
		vector<float> newTimestamp_ParticleSystem(float timestamp, float force, float size, float lifeTime, float history, float rotation, float eRad, float bornRate, float velRad);
		vector<float> newTimestamp_JointsDraw(float timestamp, float size, float lifeTime, float speed);
		vector<vector<float>> selectionSort(vector<vector<float>> parameters);

		int typeOfScene;
		
		ofxUICanvas *ddl_gui, *gui; 
		//ofxUICanvas *paste_gui;
		ofxUIDropDownList *ddl;

		vector<string> timestamps;
		vector<ofxUICanvas*> guis;

		ofxUICanvas* createParametersGUI(int index);

		bool selected;
		void showSelectedParametersGUI(bool showScenesPalette, bool showSoundsPanel);

		bool canAddTimestamp;
		void deleteTimestamp();
};