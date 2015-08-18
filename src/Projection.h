#pragma once

#include "ofMain.h"
#include "TimelineGraphicalObject.h"
#include "SoundFile.h"
#include "KinectGraphicalScene.h"

class Projection: public ofBaseApp{
public:
	void setup(deque <TimelineGraphicalObject> scenesOnTimeline, deque <SoundFile> sounds);
	void update();
	void draw();

	deque <TimelineGraphicalObject> timelineObjects;
	deque <SoundFile> soundFiles;

	KinectGraphicalScene particleSystem, jointsDraw;

};
