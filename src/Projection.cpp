#include "Projection.h"

void Projection::setup(deque <TimelineGraphicalObject> scenesOnTimeline, deque <SoundFile> sounds){
	timelineObjects = scenesOnTimeline;
	soundFiles = sounds;

	for(int i = 0; i < timelineObjects.size(); i++)
		if(timelineObjects[i].typeOfScene == 0)
			particleSystem.setup(0, false);
		else
			if(timelineObjects[i].typeOfScene == 1)
				jointsDraw.setup(1, false);
}

void Projection::update(){

}

void Projection::draw(){

}

