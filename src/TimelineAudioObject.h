#pragma once

#include "ofMain.h"
#include "AudioParametersList.h"

class TimelineAudioObject : public ofBaseApp{
public:
	void setup(string path, float prevObjEndingTime);
	void update(float currentTime, float maxTimelineTime, float shouldPlay, bool showScenesPalette, bool showSoundsPanel);
	void draw(int y, string name, float maxTimelineTime);
	void mouseDragged(int x, int y, float timeDisplay, float maxTime);
	void mousePressed(int x, int y, float timeDisplay);
	void mouseReleased(int x, int y);
	void mouseMoved(int x, int y);

	bool hoveringObject, hoveringBeginning, hoveringEnding, 
		draggingObject, draggingBeginning, draggingEnding,
		isSelected;
	float beginningOnClick, timestampOnClick, durationOnClick, amountToDrag;


	ofSoundPlayer sound;
	float objectWidth, objectX;
	float beginning, ending, duration;
	bool isPlaying;

	AudioParametersList pL;
	
	vector <float> timestampsOnClick;
};