#include "TimelineAudioObject.h"

const int dragMargin =  20;

void TimelineAudioObject::setup(string path, float prevObjEndingTime){
	cout << "Setting up '" << path << "'" << endl;
	sound.loadSound( path );
	sound.setMultiPlay( true );
	
	beginning = prevObjEndingTime;
	duration = 60.0;
	ending = beginning + duration;

	isPlaying = false;

	timestampOnClick = 0;
	amountToDrag = 0;
	beginningOnClick = 0;

	isSelected = false;

	timestampOnClick = 0;
	amountToDrag = 0;
	beginningOnClick = 0;
	durationOnClick = 30;

	printf(" > Setting up Audio Parameters List...\n");
	pL.setup(beginning, ending);
	printf(" > Finished Audio Parameters List setup!\n");
}

void TimelineAudioObject::update(float currentTime, float maxTimelineTime, float shouldPlay, bool showScenesPalette, bool showSoundsPanel){
	ending = beginning + duration;
	if(ending > maxTimelineTime){
		duration = maxTimelineTime - beginning;
		ending = beginning + duration;
	}

	objectWidth = ((duration  * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime);
	objectX = ((beginning * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime) + 18;

	if(currentTime < beginning){
		sound.stop();
		isPlaying = false;
	}else{
		if(currentTime <= ending){
			if(!isPlaying){
				sound.play();
				isPlaying = true;
			}
			else
				sound.setPaused(!shouldPlay);
		}
		else
			if(currentTime > ending){
				sound.stop();
				isPlaying = false;
			}

	}

	pL.update(isSelected, beginning, ending, showScenesPalette, showSoundsPanel);

}

void TimelineAudioObject::draw(int y, string name, float maxTimelineTime){
	ofSetColor(40,40,40);
	ofFill();
	ofRect(objectX, y, objectWidth, 30);

	//Draw hovering and dragging feedback
	ofSetColor(ofColor::white);
	if(draggingObject)
		ofSetColor(255,255,255,50);
	else
		if(hoveringObject)
			ofSetColor(255,255,255,85);

	if(draggingObject || hoveringObject)
		ofRect(objectX, y, objectWidth, 30);
			
	if(isSelected){
		ofSetColor(0);
		ofNoFill();
		ofRect(ofPoint(objectX + 3, y + 3), objectWidth - 6, 30 - 6);
	}

	//Draw time data
	ofSetColor(200,200,200);
	ostringstream buff_beggining, buff_duration, buff_ending, buff_name; 
	buff_beggining << beginning; 
	buff_duration << duration;
	buff_ending << ending;
	buff_name << name;

	//Begging
	ofDrawBitmapString(">" + buff_beggining.str(), objectX + 10, y + 20);
	//Duration
	ofDrawBitmapString(buff_name.str(), objectX + 100, y + 20);
	//Ending
	ofDrawBitmapString(buff_ending.str() + "<", objectX + objectWidth - 70, y + 20);


	//Draw resize feedback
	ofSetColor(ofColor::white);
	ofSetLineWidth(3);
	if(hoveringBeginning){
		ofTriangle(ofPoint(objectX - 10 - 5, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 15), ofPoint(objectX - 10, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 10), ofPoint(objectX - 10, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 20));
		ofLine(ofPoint(objectX, ofGetHeight() - 150 - 10 + 60 + 10 + 40),ofPoint(objectX, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30));
	}else
		if(hoveringEnding){
			ofTriangle(ofPoint(objectX + objectWidth + 10, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 10), ofPoint(objectX  + objectWidth + 15, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 15), ofPoint(objectX  + objectWidth + 10, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 20));
			ofLine(ofPoint(objectX + objectWidth, ofGetHeight() - 150 - 10 + 60 + 10 + 40),ofPoint(objectX + objectWidth, ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30));
		}
	ofSetLineWidth(1);

	//Draw timestamps markers
	ofSetColor(ofColor::blue);
	float lineX = 0;
	for(int i = 0; i<pL.parameters.size();i++){
		lineX = ((pL.parameters[i][0] * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTimelineTime) + 18;
		ofLine(lineX, y - 10, lineX, y + 30);
		//ofLine(lineX, (ofGetHeight() - 150 - 10) + 8 - 40 + 2, lineX, y + 30);

	}
	
}

void TimelineAudioObject::mouseDragged(int x, int y, float timeDisplay, float maxTime){
	amountToDrag = timeDisplay - timestampOnClick;
	
	if(draggingObject){
		if(beginningOnClick + amountToDrag >= 0  && ending <= maxTime)
			beginning = beginningOnClick + amountToDrag;
		else
			if(beginningOnClick + amountToDrag < 0)
				beginning = 0;
			else
				if(ending > maxTime){
					beginning = maxTime - duration;
				}
	}

	if(draggingBeginning){
		if(durationOnClick - amountToDrag > 10){
			beginning = beginningOnClick + amountToDrag;
			duration = durationOnClick - amountToDrag;
		}
	}
	
	if(draggingEnding){
		if(durationOnClick + amountToDrag > 10)
			duration = durationOnClick + amountToDrag;
	}

	if(draggingObject || draggingBeginning || draggingEnding){
		for(int i = 0; i< timestampsOnClick.size();i++){
			if(timestampsOnClick[i] + amountToDrag >= beginning && timestampsOnClick[i] + amountToDrag <= ending)
				pL.parameters[i][0] = timestampsOnClick[i] + amountToDrag;
		}
	}
}


void TimelineAudioObject::mousePressed(int x, int y, float timeDisplay){
	timestampOnClick = timeDisplay;
	beginningOnClick = beginning;
	durationOnClick = duration;

	timestampsOnClick.clear();
		for(int i = 0; i < pL.parameters.size(); i++){
			timestampsOnClick.push_back(pL.parameters[i][0]);
	}

	if(hoveringObject){
		draggingObject = true;
		isSelected = true;		
	}

	if(hoveringBeginning){
		draggingBeginning = true;
	}

	if(hoveringEnding){
		draggingEnding = true;
	}

	if((x > objectX + objectWidth || x < objectX ) && y > ofGetHeight() - 150 - 10 + 8 - 40 && y < (ofGetHeight() - 150 - 10 + 8) + 150 - 16)
		isSelected = false;
}

void TimelineAudioObject::mouseReleased(int x, int y){
	if(draggingObject){
		draggingObject = false;
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

	pL.mouseReleased(x,y,beginning,ending);
}

void TimelineAudioObject::mouseMoved(int x, int y){
	if(x > objectX + dragMargin && x < objectX + objectWidth - dragMargin && y > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && y < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
		hoveringObject = true;
	}
	else
		hoveringObject = false;

	if(x > objectX && x < objectX + dragMargin && y > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && y < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
		hoveringBeginning = true;
	}
	else
		hoveringBeginning = false;

	if(x > objectX + objectWidth - dragMargin && x < objectX + objectWidth && y > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && y < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
		hoveringEnding = true;
	}
	else
		hoveringEnding = false;
}