#include "TimelineGraphicalObject.h"

const int soundHeight = 40;

void TimelineGraphicalObject::setup(int type, float prevObjEndingTime){
	typeOfScene = type;
	
	beginning = prevObjEndingTime;
	duration = 30.0;
	ending = beginning + duration;

	componentWidth = 0;
	componentX = 0;

	hoveringComponent = false;
	draggingComponent = false;
	hoveringBeginning = false;
	hoveringEnding = false;
	draggingBeginning = false;
	draggingEnding = false;
	isSelected = false;

	timestampOnClick = 0;
	amountToDrag = 0;
	beginningOnClick = 0;
	durationOnClick = 30;

	extendMargin = 20;

	
	pL.setup(type, beginning, ending);
}

void TimelineGraphicalObject::update(float displayTime, float maxTime, bool showScenesPalette, bool showSoundsPanel){
	maxTimelineTime = maxTime;

	ending = beginning + duration;
	
	componentWidth = ((duration  * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime);
	componentX = ((beginning * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime) + 18;

	if (beginning < 0)
		beginning = 0;
	
	if(ending > maxTimelineTime)
		duration = maxTimelineTime - beginning;

	pL.update(isSelected, beginning, ending, showScenesPalette, showSoundsPanel);
	
}

void TimelineGraphicalObject::draw(float timelineWidth, float timelineHeight){
	switch (typeOfScene){
	case 0:
		ofSetColor(ofColor::darkorange);
		break;
	case 1:
		ofSetColor(ofColor(0,90,250));
	break;
	}
	
	ofFill();
		
	ofRect(ofPoint(componentX, ofGetHeight() - 150 - 10 + 60 - soundHeight), componentWidth, timelineHeight - 16 - 60);

	
	ofSetColor(ofColor::white);
	if(draggingComponent)
		ofSetColor(255,255,255,50);
	else
		if(hoveringComponent)
			ofSetColor(255,255,255,120);
	if(draggingComponent || hoveringComponent)
		ofRect(ofPoint(componentX, ofGetHeight() - 150 - 10 + 60 - soundHeight), componentWidth, timelineHeight - 16 - 60);
	
	ofSetColor(ofColor::white);
	ofSetLineWidth(4);
	if(hoveringBeginning){
		ofTriangle(ofPoint(componentX - 10 - 3, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 - soundHeight), ofPoint(componentX - 6, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 - 5 - soundHeight), ofPoint(componentX - 6, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 + 5 - soundHeight));
		ofLine(ofPoint(componentX, ofGetHeight() - 150 - 10 + 60 - 1 - soundHeight),ofPoint(componentX, (ofGetHeight() - 150 - 10 + 60) + timelineHeight - 16 - 60 + 1 - soundHeight));
	}else
		if(hoveringEnding){
			ofTriangle(ofPoint(componentX + componentWidth + 13, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 - soundHeight), ofPoint(componentX  + componentWidth + 7, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 - 5 - soundHeight), ofPoint(componentX  + componentWidth + 7, ofGetHeight() - 150 - 10 + 60 + timelineHeight/2 - 40 + 5 - soundHeight));
			ofLine(ofPoint(componentX + componentWidth, ofGetHeight() - 150 - 10 + 60 - 1 - soundHeight),ofPoint(componentX + componentWidth, (ofGetHeight() - 150 - 10 + 60) + timelineHeight - 16 - 60 + 1 - soundHeight));
		}
	
	if(isSelected){
		ofSetColor(0);
		ofNoFill();
		ofRect(ofPoint(componentX + 3, ofGetHeight() - 150 - 10 + 60 - soundHeight + 3), componentWidth - 6, timelineHeight - 16 - 60 - 6);

	}
	ofSetColor(255,255,255,200);
	ofSetLineWidth(2);
	ofNoFill();
	ofRect(ofPoint(componentX, ofGetHeight() - 150 - 10 + 60 - soundHeight), componentWidth, timelineHeight - 16 - 60);
	ofSetLineWidth(1);

	ofSetColor(ofColor::black);

	switch (typeOfScene){
	case 0:
		ofDrawBitmapString("Particle System", componentX + 20, (ofGetHeight() - 150 - 10 + 10) + timelineHeight - 16 - 50 - soundHeight);
		break;
	case 1:
		ofDrawBitmapString("Joints Draw", componentX + 20, (ofGetHeight() - 150 - 10 + 10) + timelineHeight - 16 - 50 - soundHeight);
		break;
	}

	ostringstream buff_beggining, buff_duration, buff_ending; 
	buff_beggining << beginning; 
	buff_duration << duration;
	buff_ending << ending;

	//Begging
	ofDrawBitmapString(">" + buff_beggining.str(), componentX + 5, (ofGetHeight() - 150 - 10 + 40) + timelineHeight - 16 - 50 - soundHeight);
	//Duration
	ofDrawBitmapString(buff_duration.str(), componentX + componentWidth/2, (ofGetHeight() - 150 - 10 + 40) + timelineHeight - 16 - 50 - soundHeight);
	//Ending
	ofDrawBitmapString(buff_ending.str() + "<", componentX + componentWidth - 80, (ofGetHeight() - 150 - 10 + 40) + timelineHeight - 16 - 50 - soundHeight);


	//Draw timestamps markers
	ofSetColor(ofColor::red);
	float lineX = 0;
	for(int i = 0; i<pL.parameters.size();i++){
		lineX = ((pL.parameters[i][0] * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime) + 18;
		ofLine(lineX, (ofGetHeight() - 150 - 10) + 8 - 40 + 2, lineX, (ofGetHeight() - 150 - 10) + 8 + 100 - 16);
	}

}

void TimelineGraphicalObject::mouseDragged(int x, int y, float timeDisplay, float maxTime, deque<TimelineGraphicalObject> timelineObjects){
	amountToDrag = timeDisplay - timestampOnClick;
	
	if(draggingComponent){
		if(beginningOnClick + amountToDrag >= 0  && ending <= maxTime)
			beginning = beginningOnClick + amountToDrag;
		else
			if(beginningOnClick + amountToDrag < 0)
				beginning = 0;
			else
				if(ending > maxTime){
					beginning = maxTime - duration;
				}
	
		for(int i = 0; i< timestampsOnClick.size();i++){
			if(timestampsOnClick[i] + amountToDrag >= beginning && timestampsOnClick[i] + amountToDrag <= ending)
				pL.parameters[i][0] = timestampsOnClick[i] + amountToDrag;
		}
	}
	
	if(draggingBeginning){
		if(durationOnClick - amountToDrag > 10){
			beginning = beginningOnClick + amountToDrag;
			duration = durationOnClick - amountToDrag;
		}

		for(int i = 0; i< timestampsOnClick.size();i++){
			if(timestampsOnClick[i] + amountToDrag >= beginning && timestampsOnClick[i] + amountToDrag <= ending)
				pL.parameters[i][0] = timestampsOnClick[i] + amountToDrag;
		}
	}
	
	if(draggingEnding){
		if(durationOnClick + amountToDrag > 10)
			duration = durationOnClick + amountToDrag;
		
		for(int i = 0; i< timestampsOnClick.size();i++){
			if(timestampsOnClick[i] + amountToDrag >= beginning && timestampsOnClick[i] + amountToDrag <= ending)
				pL.parameters[i][0] = timestampsOnClick[i] + amountToDrag;
		}
	}
}

void TimelineGraphicalObject::mousePressed(int x, int y, float timeDisplay){
	timestampOnClick = timeDisplay;
	beginningOnClick = beginning;
	durationOnClick = duration;

	timestampsOnClick.clear();
		for(int i = 0; i < pL.parameters.size(); i++){
			timestampsOnClick.push_back(pL.parameters[i][0]);
	}
	
	if(hoveringComponent){
		draggingComponent = true;
		isSelected = true;		
	}

	if(hoveringBeginning){
		draggingBeginning = true;
	}

	if(hoveringEnding){
		draggingEnding = true;
	}

	if((x > componentX + componentWidth || x < componentX ) && y > ofGetHeight() - 150 - 10 + 8 - 40 && y < (ofGetHeight() - 150 - 10 + 8) + 150 - 16)
		isSelected = false;
}

void TimelineGraphicalObject::mouseReleased(int x, int y){
	if(draggingComponent){
		draggingComponent = false;
		amountToDrag = 0;
		timestampOnClick = 0;
		beginningOnClick = 0;
	}

	if(draggingBeginning){
		draggingBeginning = false;
	}

	if(draggingEnding){
		draggingEnding= false;
	}

	pL.mouseReleased(x,y, beginning, ending);
}

void TimelineGraphicalObject::mouseMoved(int x, int y){
	if(x > componentX + extendMargin && x < componentX + componentWidth - extendMargin && y > ofGetHeight() - 150 - 10 + 60 - soundHeight && y < (ofGetHeight() - 150 - 10 + 60) + (150 - 16 - 60) - soundHeight){
		hoveringComponent = true;
	}
	else
		hoveringComponent = false;

	if(x > componentX && x < componentX + extendMargin && y > ofGetHeight() - 150 - 10 + 60 - soundHeight && y < (ofGetHeight() - 150 - 10 + 60) + (150 - 16 - 60) - soundHeight){
		hoveringBeginning = true;
	}
	else
		hoveringBeginning = false;

	if(x > componentX + componentWidth - extendMargin && x < componentX + componentWidth && y > ofGetHeight() - 150 - 10 + 60 - soundHeight && y < (ofGetHeight() - 150 - 10 + 60) + (150 - 16 - 60) - soundHeight){
		hoveringEnding = true;
	}
	else
		hoveringEnding = false;
}

void TimelineGraphicalObject::windowResized(int w, int h){

}