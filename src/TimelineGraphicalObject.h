#pragma once

#include "ofMain.h"
#include "GraphicsParametersList.h"

class TimelineGraphicalObject : public ofBaseApp{
	public:
		void setup(int type, float prevObjEndingTime);			
		void update(float displayTime, float maxTime, bool showScenesPalette, bool showSoundsPanel);
		void draw(float timelineWidth, float timelineHeight);
		
		void mouseDragged(int x, int y, float timeDisplay, float maxTime, deque<TimelineGraphicalObject> TimelineGraphicalObjects);
		void mousePressed(int x, int y, float timeDisplay);
		void mouseReleased(int x, int y);
		void mouseMoved(int x, int y );
		void windowResized(int w, int h);

		float componentWidth;
		float componentX;

		int typeOfScene;			//0 - Particle System, 1 - JointsDraw
		float beginning, ending, duration;

		bool hoveringComponent, draggingComponent;
		bool hoveringBeginning, draggingBeginning;
		bool hoveringEnding, draggingEnding;
		bool isSelected;

		float beginningOnClick, durationOnClick, timestampOnClick, amountToDrag;

		float extendMargin;

		GraphicsParametersList pL;

		float maxTimelineTime;

		vector <float> timestampsOnClick;

};