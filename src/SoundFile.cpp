#include "SoundFile.h"

const int buttonSize = 20;

void SoundFile::setup(int x, int y, string name, string path){
	posX = x;
	posY = y;
	fileName = name;
	filePath = path;

	musicImage.loadImage("musicIcon.png");
	musicImage.resize((ofGetWidth() / 2 - 30)/5,  (ofGetWidth() / 2 - 30)/5);
	musicIcon.allocate(musicImage.width, musicImage.height, GL_RGB32F_ARB);

	musicImageDraggable.loadImage("musicIcon.png");
	musicImageDraggable.resize(musicImageDraggable.width/5, musicImageDraggable.height/5);
	musicIconDraggable.allocate(musicImageDraggable.width, musicImageDraggable.height, GL_RGB32F_ARB);

	exploreIcon.loadImage("preview_normal.png");
	exploreIcon.resize(buttonSize, buttonSize);
	exploreButton.allocate(exploreIcon.width, exploreIcon.height, GL_RGB32F_ARB);

	exploringAudio = false;

	hoveringSoundFile = hoveringExploreButton = draggingSoundFile = hoveringSoundTimeline = false;
}

void SoundFile::update(bool showSoundPanel, bool showScenesPanel, bool hoveringTimeline, float currentTime, float maxTimelineTime, bool playingSequence){
	visibleOnPanel = showSoundPanel;
	hoveringSoundTimeline = hoveringTimeline;

	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].update(currentTime, maxTimelineTime, playingSequence, showScenesPanel, showSoundPanel);
	}
}

void SoundFile::draw(int mouseX, int mouseY, float maxTimelineTime){
	if(visibleOnPanel){
		drawSoundFile();

		//Draw 'Explore' button
		exploreButton.begin();
		if(!hoveringExploreButton)
			exploreIcon.loadImage("preview_normal.png");
		else
			exploreIcon.loadImage("preview_hovering.png");
		exploreIcon.resize(buttonSize, buttonSize);
		exploreIcon.draw(0,0);
		exploreButton.end();
		exploreButton.draw(posX + buttonSize/2, posY + musicImage.getHeight() - buttonSize/2 - buttonSize);

		if(draggingSoundFile){
			musicIconDraggable.begin();
			musicImageDraggable.draw(0,0);
			musicIconDraggable.end();
			musicIconDraggable.draw(mouseX + 5, mouseY - musicIconDraggable.getHeight());
		}
	}

	
	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].draw(ofGetHeight() - 150 - 10 + 60 + 10 + 40, fileName, maxTimelineTime);
	}
}

//Draw the sound file icon on the Sounds Panel
void SoundFile::drawSoundFile(){
	ofSetColor(ofColor(255, 255, 255));
	musicIcon.begin();
	musicImage.draw(0,0);
	musicIcon.end();
	musicIcon.draw(posX, posY);

	ofFill();
	ofSetColor(10,10,10);
	ofRect(posX, posY + musicIcon.getHeight(), musicIcon.getWidth(), musicIcon.getHeight()/5);
	ofSetColor(169,169,169);
	ofDrawBitmapString(fileName, posX + 10, posY + musicIcon.getHeight() + 15);

	ofNoFill();
	if(hoveringSoundFile)
		ofSetColor(230, 230, 230);
	else
		ofSetColor(169,169,169);
	ofRect(posX, posY, musicIcon.getWidth(), musicIcon.getHeight() + musicIcon.getHeight()/5);
}

void SoundFile::mouseMoved(int x, int y ){
	if(visibleOnPanel){
		if(x > posX && x < posX + musicIcon.getWidth() && y > posY && y < posY + musicIcon.getHeight() + musicIcon.getHeight()/5){
			hoveringSoundFile = true;
			
			if(x > posX + buttonSize/2 && x < posX + buttonSize/2 + buttonSize &&
				y > posY + musicImage.getHeight() - buttonSize/2 - buttonSize && mouseY < posY + musicImage.getHeight() - buttonSize/2)
						hoveringExploreButton = true;
					else
						hoveringExploreButton = false;
		}
		else
			hoveringSoundFile = hoveringExploreButton = false;
	}

	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].mouseMoved(x, y);
	}
}

void SoundFile::mousePressed(int x, int y, int timeDisplay){
	if(visibleOnPanel){
		if(hoveringSoundFile && !hoveringExploreButton){
			draggingSoundFile = true;
		}
	}

	if(hoveringExploreButton){
		exploringAudio = true;
		hoveringExploreButton = false;
	}

	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].mousePressed(x, y, timeDisplay);
	}
}

void SoundFile::mouseReleased(int x, int y){
	if(draggingSoundFile && 
		x > 18 && x < 18 + ofGetWidth() - (10 * 2) - 300 - 16 && 
		y > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && y < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
			addSoundObject();
			soundsTimeline[soundsTimeline.size() - 1].pL.addTimestamp(soundsTimeline[soundsTimeline.size() - 1].beginning, 0, 0, 6, 1, 2, 0);
			soundsTimeline[soundsTimeline.size() - 1].pL.addTimestamp(soundsTimeline[soundsTimeline.size() - 1].ending, 0, 0, 6, 1, 2, 0);

			hoveringSoundFile = draggingSoundFile = false;
	}
	else
		hoveringSoundFile = draggingSoundFile = false;

	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].mouseReleased(x, y);
	}
}

void SoundFile::mouseDragged(int x, int y, float timeDisplay, float maxTime){
	for(int i = 0; i < soundsTimeline.size(); i++){
		soundsTimeline[i].mouseDragged(x, y, timeDisplay, maxTime);
	}
}

void SoundFile::windowResized(int w, int h){
	musicImage.loadImage("musicIcon.png");
	musicImage.resize((ofGetWidth() / 2 - 30)/5,  (ofGetWidth() / 2 - 30)/5);
	musicIcon.allocate(musicImage.width, musicImage.height, GL_RGB32F_ARB);

	musicImageDraggable.loadImage("musicIcon.png");
	musicImageDraggable.resize(musicImageDraggable.width/5, musicImageDraggable.height/5);
	musicIconDraggable.allocate(musicImageDraggable.width, musicImageDraggable.height, GL_RGB32F_ARB);

	exploreIcon.loadImage("preview_normal.png");
	exploreIcon.resize(buttonSize, buttonSize);
	exploreButton.allocate(exploreIcon.width, exploreIcon.height, GL_RGB32F_ARB);
}

void SoundFile::addSoundObject(){
	printf("\n > Adding sound object to sequence ...\n");
	TimelineAudioObject soundObject;
	float begining = 0;
	if(soundsTimeline.size()>0)
		begining = soundsTimeline[soundsTimeline.size() - 1].ending;
	soundObject.setup(filePath, begining);
	soundsTimeline.push_back(soundObject);
}

void SoundFile::resetAudioPlay(float maxTime){
		float minorBeginning = maxTime;
		
		if(soundsTimeline.size()>0){
			//Find first sound to appear on timeline
			for(int i = 0; i < soundsTimeline.size(); i++){
				if(soundsTimeline[i].beginning < minorBeginning)
					minorBeginning = soundsTimeline[i].beginning;
			}
			//Replay that sound
			for(int i = 0; i < soundsTimeline.size(); i++){
				if(soundsTimeline[i].beginning == minorBeginning){
					soundsTimeline[i].sound.stop();
					soundsTimeline[i].sound.play();
				}
			}
		}
}