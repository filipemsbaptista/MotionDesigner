#pragma once

#include "ofMain.h"
#include "ParticleSystemDemo.h"
#include "JointsDrawDemo.h"
#include "TimelineGraphicalObject.h"

class PreviewPlayer: public ofBaseApp {
public:
	ofFbo previewPlayer;
	void setup(int x, int y, float panelWidth, float panelHeight, deque <TimelineGraphicalObject> timelineObjs);
	void update(float t);
	void draw(int x, int y, float panelHeight);

	void windowResized(int panelWidth);

	void updateTimelineObjects(deque<TimelineGraphicalObject> timelineObjs);

	float currentTime;

	deque <TimelineGraphicalObject> timelineObjects;

	ParticleSystemDemo particleSystem_demo;
	JointsDrawDemo jointsDraw_demo;

	void resetDemos();
	bool skeletonVisible;

};