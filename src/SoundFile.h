#pragma once

#include "ofMain.h"
#include "TimelineAudioObject.h"

class SoundFile: public ofBaseApp{
public:
	void setup(int x, int y, string name, string path);
	void update(bool showSoundPanel, bool showScenesPalette, bool hoveringTimeline, float currentTime, float maxTimelineTime, bool playingSequence);
	void draw(int mouseX, int mouseY, float maxTimelineTime);
	void drawSoundFile();

	//void keyPressed(int key);
	//void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, float timeDisplay, float maxTime);
	void mousePressed(int x, int y, int timeDisplay);
	void mouseReleased(int x, int y);
	void windowResized(int w, int h);
	//void dragEvent(ofDragInfo dragInfo);
	//void gotMessage(ofMessage msg);

	void resetAudioPlay(float maxTime);

	//Sound Panel Data
	bool visibleOnPanel;
	bool hoveringSoundFile, hoveringExploreButton, draggingSoundFile, hoveringSoundTimeline;
	bool exploringAudio;
		
	ofImage musicImage, musicImageDraggable, exploreIcon;
	ofFbo musicIcon, musicIconDraggable, exploreButton;
	string fileName, filePath;
	int posX, posY;


	//Timeline Data
	deque <TimelineAudioObject> soundsTimeline; 
	void addSoundObject();


};