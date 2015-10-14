#include <windows.h> 
#include "ofApp.h"

const int soundHeight = 40;
const int buttonRadius = 80;

const int MIN_WIDTH = 1000;
const int MIN_HEIGHT = 650;

const int loadingWidth = 400;
const int loadingHeight = 100;

const int GUIS_MARGIN = 250;

ofxUICanvas *fps, *guiInfo;

void ofApp::setup(){
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 

	maxTime = 120.0;		//in seconds
	maxEnding = 0;
	currentTime = 0.0;
	timeDisplay = 0;
	timeMarkerX = 18;

	draggingTimeMarker = false;
	playingSequence = false;
	draggingParticleSystemScene = false;
	draggingJointsDrawScene = false;

	previewPanelHeight = ofGetHeight() - 150 - 80 - soundHeight;
	previewPanelWidth = ofGetWidth() / 2 - 30;

	logo_alpha = 255;
	logoImage.loadImage("logo.png");
	logoImage.resize((ofGetHeight() * 16)/9 + 100, ofGetHeight() + 100);
	logo.allocate(logoImage.width, logoImage.height, GL_RGB32F_ARB);

	particleSystemImage.loadImage("particleSystem.png");
	particleSystemImage.resize((ofGetWidth() / 2 - 30)/2 - 20,  (((ofGetWidth() / 2 - 30)/2 - 20) * 9)/16);
	particleSystemScene.allocate(particleSystemImage.width, particleSystemImage.height, GL_RGB32F_ARB);
	
	jointsDrawImage.loadImage("jointsDraw.png");
	jointsDrawImage.resize((ofGetWidth() / 2 - 30)/2 - 20, (((ofGetWidth() / 2 - 30)/2 - 20) * 9)/16);
	jointsDrawScene.allocate(jointsDrawImage.width, jointsDrawImage.height, GL_RGB32F_ARB);

	particleSystemImageDraggable.loadImage("particleSystem.png");
	particleSystemImageDraggable.resize(particleSystemImageDraggable.width/4, particleSystemImageDraggable.height/4);
	particleSystemDraggable.allocate(particleSystemImageDraggable.width, particleSystemImageDraggable.height, GL_RGB32F_ARB);
	
	jointsDrawImageDraggable.loadImage("jointsDraw.png");
	jointsDrawImageDraggable.resize(jointsDrawImageDraggable.width/4, jointsDrawImageDraggable.height/4);
	jointsDrawDraggable.allocate(jointsDrawImageDraggable.width, jointsDrawImageDraggable.height, GL_RGB32F_ARB);

	projectingSequence = false;

	darkTheme = true;

	noScenesOnTimeline = true;
	noSoundOnTimeline = true;

	hoveringAddButton = hoveringDeleteButton = hoveringAddSoundButton = hoveringPlayPause = hoveringSkipLeft = hoveringSkipRight =
		hoveringExplorePS = hoveringExploreJD = hoveringPasteButton = hoveringLaunchButton = false;
	anySelected = false;
	
	showScenesPalette = true;
	showSoundsPanel = false;
	hoveringScenesMarker = hoveringParametersPanelMarker = hoveringSoundsPanelMarker = hoveringSoundTimeline = false;
	hoveringParticleSystemScene = hoveringJointsDrawScene = false;
	draggingAudioFile = false;

	//Setup FPS and INFO guis
	setupInfoPanels();

	//Setup preview screen
	previewPlayer.setup(ofGetWidth() / 2 + 15, 30, previewPanelWidth, previewPanelHeight, timelineObjects);

	//Setup 'Delete' button
	buttonSize = (ofGetWidth()/2) / 20;

	junkImage.loadImage("trash_button_normal.png");
	junkImage.resize(buttonSize, buttonSize);
	deleteButton.allocate(junkImage.width, junkImage.height, GL_RGB32F_ARB);

	exploreIcon_PS.loadImage("preview_normal.png");
	exploreIcon_PS.resize(buttonSize, buttonSize);
	exploreButton_PS.allocate(exploreIcon_PS.width, exploreIcon_PS.height, GL_RGB32F_ARB);

	exploreIcon_JD.loadImage("preview_normal.png");
	exploreIcon_JD.resize(buttonSize, buttonSize);
	exploreButton_JD.allocate(exploreIcon_JD.width, exploreIcon_JD.height, GL_RGB32F_ARB);

	exploringPS = exploringJD = exploringAudio = false;

	loading = false;

	// !!!!!!!!!!!  This should only be when user clicks '+' and selects file   !!!!!!!!!!!!
	SoundFile budamonkAcrossTheHall;
	budamonkAcrossTheHall.setup(10 + 8 + 8, 30 + 8 + 8, "01 Across the Hall", "budamonk.wav");
	soundFiles.push_back(budamonkAcrossTheHall);
}

void ofApp::update(){
	if(!exploringPS && !exploringJD && !exploringAudio){

		if (maxTime < 10.0)
			maxTime = 10.0;
	
		timeDisplay = (maxTime * (mouseX - 19)) / (18 + ofGetWidth() - 20 - 300 - 16 - 20);
		if(timeDisplay < 0)
			timeDisplay = 0;
		else if(timeDisplay >= maxTime)
			timeDisplay = maxTime;
	
	
		timeMarkerX = ((currentTime * ((18 + ofGetWidth() - (10 * 2) - 300) - 16 - 18)) / maxTime) + 18;
		
	
		if(draggingTimeMarker){
			currentTime = (maxTime * (mouseX - 18)) / (18 + ofGetWidth() - 20 - 300 - 16 - 18);
		}

		if(playingSequence)
			currentTime += 0.1;
	
		if(currentTime < 0)
			currentTime = 0;
		else if(currentTime >= maxTime){
			currentTime = maxTime;
			playingSequence = false; 
		}


		//Timeline objects
		for(int i = 0; i < timelineObjects.size(); i++){
			timelineObjects[i].update(timeDisplay, maxTime, showScenesPalette, showSoundsPanel);
			if(timelineObjects[i].beginning > maxTime)
				maxTime = timelineObjects[i].beginning;
			if(timelineObjects[i].duration < 0){
				timelineObjects.erase(timelineObjects.end() - (timelineObjects.size() - i));
			}		
		}


		if(timelineObjects.size() == 0)
			noScenesOnTimeline = true;
		else
			noScenesOnTimeline = false;

		if(soundFiles.size() > 0){
			for(int i = 0; i < soundFiles.size(); i++){
				if(soundFiles[i].soundsTimeline.size() > 0)
					noSoundOnTimeline = false;
				else
					noSoundOnTimeline = true;
			}

		}else
			noSoundOnTimeline = true;

		if(playingSequence)
			previewPlayer.update(currentTime);

		//Sound Objects
		for(int i = 0; i < soundFiles.size(); i++){
			soundFiles[i].update(showSoundsPanel, showScenesPalette, hoveringSoundTimeline, currentTime, maxTime, playingSequence);
		}
	

		//Check if needs to draw loading info
		if(loading){
			ofSetColor(5,5,5);
			ofFill();
			ofRect(ofGetWidth()/2 - loadingWidth/2, ofGetHeight()/2 - loadingHeight, loadingWidth, loadingHeight);
	
			ofNoFill();
			ofSetColor(detailColor);
			ofRect(ofGetWidth()/2 - loadingWidth/2, ofGetHeight()/2 - loadingHeight, loadingWidth, loadingHeight);

			ofSetColor(ofColor::darkGrey);
			ofDrawBitmapString("Setting up the Kinect sensor ...", ofGetWidth()/2 - loadingWidth/2 + 20, ofGetHeight()/2 - loadingHeight + 40);
		}

	}
	// ----------------------------------------------------------------------------------------
	else
	{
	if(exploringPS){
			printf("Particle System (Kinect):  update()\n");

			particleSystemKinectPreview.update();
		}else
			if(exploringJD){
				printf("Joints Draw (Kinect):  update()\n");

				jointsDrawKinectPreview.update();
			}
			else
				if(exploringAudio){
					interactiveAudioKinect.update();
				}
				else
					if(projectingSequence){
						sequenceProjection.update();
					}
	}
}

void ofApp::draw(){
	//------------------------------------------
	if(darkTheme){
		backgroundColor = ofColor(5,5,5);
		primaryColor = ofColor(20,20,20); 
		secondaryColor = ofColor(30,30,30); 
		detailColor = ofColor::orange;
	} else {
		backgroundColor = ofColor(200, 200, 200);
		primaryColor = ofColor(ofColor::lightGray); 
		secondaryColor = ofColor(ofColor::gray); 
		detailColor = ofColor::darkBlue;
	}
	//-----------------------------------------


	if(!exploringPS && !exploringJD && !exploringAudio){
		ofBackground(backgroundColor);
	
		ofPushStyle();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
		ofSetColor(255, 255, 255, 5);
		drawGrid(10, 10);

		ofPopStyle();

		//Draw panels
		drawTimeline(10, ofGetHeight() - 150 - 10 - soundHeight);
		drawParametersPanel(10, 30);
		drawScenesPalette(10, 30);
		drawSoundsPanel(10, 30);
		drawPreviewPanel(ofGetWidth() / 2 + 15, 30);
		drawActionButtons(10 + timelineWidth, ofGetHeight() - 10 - timelineHeight);


		//Draw timeline objects
		for(int i = 0; i < timelineObjects.size(); i++)
			timelineObjects[i].draw(ofGetWidth() - (10 * 2) - 300, 150);
	
		for(int i = 0; i < soundFiles.size(); i++)
			soundFiles[i].draw(mouseX, mouseY, maxTime);
		
		for(int i = 0; i < soundFiles.size(); i++){
			if(soundFiles[i].draggingSoundFile)
				draggingAudioFile = true;
		}


		//Check cursor line draw
		if(!draggingParticleSystemScene && !draggingJointsDrawScene && !draggingAudioFile && mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 - soundHeight && mouseY < (ofGetHeight() - 150 - 10 + 8) + 150 - 16){
			ofSetColor(primaryColor);
			ofRect(mouseX + 5, ofGetHeight() - 150 + 8 - soundHeight, 55, 15);

			if(darkTheme)
				ofSetColor(ofColor::green);
			else
				ofSetColor(ofColor::red);

			ofLine(mouseX, ofGetHeight() - 150 - 10 + 8 - soundHeight, mouseX, (ofGetHeight() - 150 - 10 + 8) + 150 - 16);

			ostringstream buff; buff << timeDisplay; 
			ofDrawBitmapString(buff.str(), mouseX + 5, ofGetHeight() - 150 + 18 - soundHeight);
		}

		//Draw time marker
		if(draggingTimeMarker)
			if(darkTheme)
				ofSetColor(ofColor::white);
			else
				ofSetColor(ofColor::black);
		else
			if(darkTheme)
				ofSetColor(ofColor::darkGrey);
			else
				ofSetColor(ofColor(10,10,10));

		ofSetLineWidth(2);
		if(timeMarkerX < 18)
			timeMarkerX = 18;
		ofLine(timeMarkerX, (ofGetHeight() - 150 - 10) + 8 - soundHeight, timeMarkerX, (ofGetHeight() - 150 - 10) + 8 + 150 - 16);
		ofSetLineWidth(1);
		ostringstream buffer; buffer << currentTime; 
		ofDrawBitmapString(buffer.str(), timeMarkerX + 5, ofGetHeight() - 150 + 35 - soundHeight);

		//Check dragging scenes
		if(draggingParticleSystemScene  && !hoveringExplorePS){
			particleSystemDraggable.begin();
			particleSystemImageDraggable.draw(0,0);
			particleSystemDraggable.end();
			particleSystemDraggable.draw(mouseX + 15, mouseY + 15);
		}

		if(draggingJointsDrawScene && !hoveringExploreJD){
			jointsDrawDraggable.begin();
			jointsDrawImageDraggable.draw(0,0);
			jointsDrawDraggable.end();
			jointsDrawDraggable.draw(mouseX + 15, mouseY + 15);
		}

		//Check if needs to draw loading info
		if(loading){
			ofSetColor(5,5,5);
			ofFill();
			ofRect(ofGetWidth()/2 - loadingWidth/2, ofGetHeight()/2 - loadingHeight, loadingWidth, loadingHeight);
	
			ofNoFill();
			ofSetColor(detailColor);
			ofRect(ofGetWidth()/2 - loadingWidth/2, ofGetHeight()/2 - loadingHeight, loadingWidth, loadingHeight);
			ofDrawBitmapString("Loading", ofGetWidth()/2 - 25, ofGetHeight()/2 - loadingHeight + 25);
			
			ofSetColor(ofColor::darkGrey);
			ofDrawBitmapString("Setting up the Kinect sensor ...", ofGetWidth()/2 - loadingWidth/2 + 20, ofGetHeight()/2 - loadingHeight + 70);
		}
	}
	else
	{
		ofBackground(backgroundColor);

		if(exploringPS){
			printf("Particle System (Kinect):  draw()\n");
			particleSystemKinectPreview.draw();
		}else
			if(exploringJD){
				printf("Joints Draw (Kinect):  draw()\n");
				jointsDrawKinectPreview.draw();
			}
			else
				if(exploringAudio){
					interactiveAudioKinect.draw();
				}
	}

	if(logo_alpha > 0){
		drawLogo();
		if(ofGetElapsedTimef() > 5)
			logo_alpha -= 10;
	}
}

void ofApp::drawLogo(){
	ofSetColor(255,255,255);
	logo.begin();
	logoImage.draw(0,0);
	logo.end();
	ofSetColor(255,255,255, logo_alpha);
	logo.draw(0 - ((logo.getWidth() - ofGetWidth())/2), 0 - ((logo.getHeight() - ofGetHeight())/2));
}

void ofApp::drawGrid(float x, float y){
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    for(int i = 0; i < h; i+=y)
    {
        ofLine(0,i,w,i);
    }
    
    for(int j = 0; j < w; j+=x)
    {
        ofLine(j,0,j,h);
    }
}

void ofApp::setupInfoPanels(){
	fps = new ofxUICanvas();
	fps->addFPS();
	fps->setPosition(ofGetWidth() - GUIS_MARGIN, 5);
	fps->setVisible(false);
	fps->autoSizeToFitWidgets();

	guiInfo = new ofxUISuperCanvas("INFO:");
	guiInfo->setPosition(ofGetWidth() - GUIS_MARGIN, 25);
	guiInfo->setVisible(false);
	guiInfo->addSpacer();
	string textString = "Press 'I' to hide/show these panels\n";
	guiInfo->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	string textString2 = "SHORTCUT KEYS:\n";
	guiInfo->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	guiInfo->addLabel("   SPACE - Play/Pause sequence", OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	guiInfo->addLabel("   ENTER - Replay sequence", OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	guiInfo->addLabel("   LEFT/RIGHT - Move time marker", OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	string textString3 = "   +/- - Expand/contract sequence duration";
	guiInfo->addTextArea("textarea", textString3, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	string textString4 = "   F - Fit sequence to the end of last scene";
	guiInfo->addTextArea("textarea", textString4, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	string textString5 = "   DEL - Remove selected scene";
	guiInfo->addTextArea("textarea", textString5, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	string textString6 = "   H - Show/hide virtual skeleton";
	guiInfo->addTextArea("textarea", textString6, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);

	guiInfo->autoSizeToFitWidgets();
}

void ofApp::drawParametersPanel(float x, float y){
	ofSetColor(255,255,255,255);

	int panelHeight = ofGetHeight() - 150 - 80 - soundHeight;
	int panelWidth = ofGetWidth() / 2;
	
	ofFill();
	
	if(!showScenesPalette && !showSoundsPanel){
		ofSetColor(secondaryColor);
		ofRect(ofPoint(x, y - 20), 135, 20);
		ofRect(ofPoint(x,y), panelWidth, panelHeight);

		ofSetColor(detailColor);
		ofLine(ofPoint(x, y - 20), ofPoint(x, y + panelHeight));
		ofLine(ofPoint(x, y + panelHeight), ofPoint(x + panelWidth, y + panelHeight));
		ofLine(ofPoint(x, y - 20), ofPoint(x + 135, y -20));
		ofLine(ofPoint(x + 135, y -20), ofPoint(x + 135, y));
		ofLine(ofPoint(x + 135, y), ofPoint(x + panelWidth, y));
		ofLine(ofPoint(x + panelWidth, y), ofPoint(x + panelWidth, y + panelHeight));

		ofDrawBitmapString("Parameters:", x + 10 , y - 5);
	
		ofSetColor(primaryColor);
		ofRect(ofPoint(x + 8,y + 8), panelWidth - 16, panelHeight - 16);

		if(darkTheme)
			ofSetColor(ofColor::darkGray);
		else
			ofSetColor(ofColor(10,10,10));

		anySelected = false;
		if(timelineObjects.size() > 0)
			for(int i = 0; i<timelineObjects.size(); i++)
				if(timelineObjects[i].isSelected)
					anySelected = true;
		
		if(soundFiles.size() > 0)
			for(int i = 0; i < soundFiles.size(); i++)
				for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++)
					if(soundFiles[i].soundsTimeline[j].isSelected)
						anySelected = true;
		if(!anySelected)
			ofDrawBitmapString("Click on a scene or sound from the timeline to show parameterizations", x + 8 + (panelWidth - 16)/7 - 10, y + (panelHeight - 16)/2  - 16);

		//Draw 'Add' button
		if(!hoveringAddButton)
			ofSetColor(ofColor(10, 10, 10));
		else
			ofSetColor(ofColor::darkGray);
		ofFill();
		ofRect(x + 8 + 5, y + 8 + panelHeight - 16 - 5 - buttonSize, buttonSize, buttonSize);

		if(!hoveringAddButton)
			ofSetColor(ofColor::darkGray);
		else
			ofSetColor(ofColor(10, 10, 10));
		ofSetLineWidth(2);
		ofLine(ofPoint(x + 8 + 5 + buttonSize/2, y + 8 + panelHeight -16 - 5 - buttonSize + 4), ofPoint(x + 8 + 5 + buttonSize/2, y + 8 + panelHeight -16 - 5 - buttonSize + 2 + buttonSize - 4 - 2));
		ofLine(ofPoint(x + 8 + 5 + 4, y + 8 + panelHeight -16 - 5 - buttonSize/2), ofPoint(x + 8 + 5 + buttonSize - 4, y + 8 + panelHeight -16 - 5 - buttonSize/2));
		ofxUISetLineWidth(1);

		//Draw 'Delete' button
		deleteButton.begin();
		if(!hoveringDeleteButton)
			junkImage.loadImage("trash_button_normal.png");
		else
			junkImage.loadImage("trash_button_hovering.png");
		junkImage.resize(buttonSize, buttonSize);
		junkImage.draw(0,0);
		deleteButton.end();
		deleteButton.draw(x + 8 + panelWidth - 16 - 5 - deleteButton.getWidth(), y + 8 + panelHeight - 16 - 5 - buttonSize);

		if(anySelected){
			//Draw 'Paste Settings' button
			ofFill();
			if(!hoveringPasteButton)
				ofSetColor(10,10,10);
			else
				ofSetColor(180,180,180);
			ofRect(x + 8 + 5, y + 8 + panelHeight - 16 - 5 - buttonSize - 10 - 30, 150, 30);
		
			ofNoFill();
			ofSetLineWidth(1);
			if(!hoveringPasteButton)
				ofSetColor(120,120,120);
			else
				ofSetColor(10,10,10);
			ofRect(x + 8 + 5 + 1, y + 8 + panelHeight - 16 - 5 - buttonSize - 10 - 30 + 1, 148, 28);

			if(!hoveringPasteButton)
				ofSetColor(180,180,180);
			else
				ofSetColor(10,10,10);
			ofDrawBitmapString("PASTE SETTINGS", x + 8 + 20, y + 8 + panelHeight - 16 - 5 - buttonSize - 10 - 10);
		}
	}
	else{
		if(!hoveringParametersPanelMarker)
			ofSetColor(primaryColor);
		else
			ofSetColor(secondaryColor.r + 15, secondaryColor.g + 15, secondaryColor.b + 15);

		ofRect(ofPoint(x, y - 20), 134, 19);

		ofSetColor(detailColor.r - 80, detailColor.g - 80, detailColor.b - 80);
		ofDrawBitmapString("Parameters:", x + 10 , y - 5);

		ofSetLineWidth(1);
		ofLine(ofPoint(x, y - 20), ofPoint(x + 134, y - 20));
		ofLine(ofPoint(x, y - 20), ofPoint(x, y));
		ofLine(ofPoint(x + 135, y - 20), ofPoint(x + 135, y));
	}
}

void ofApp::drawScenesPalette(float x, float y){
	ofSetColor(255,255,255,255);

	int panelHeight = ofGetHeight() - 150 - 80 - soundHeight;
	int panelWidth = ofGetWidth() / 2;
	
	ofFill();
	
	if(showScenesPalette){
		ofSetColor(secondaryColor);
		ofRect(ofPoint(x + 135, y - 20), 135, 20);
		ofRect(ofPoint(x,y), panelWidth, panelHeight);
			
		//Draw container
		ofSetColor(primaryColor);
		ofRect(ofPoint(x + 8,y + 8), panelWidth - 16, panelHeight - 16);

		//Draw marker and contour
		ofSetColor(detailColor);
		ofDrawBitmapString("Scenes:", x + 135 + 10 , y - 5);
		
		ofLine(ofPoint(x, y), ofPoint(x, y + panelHeight));
		ofLine(ofPoint(x, y), ofPoint(x + 135, y));
		ofLine(ofPoint(x + 135, y), ofPoint(x + 135, y -20));
		ofLine(ofPoint(x + 135, y -20), ofPoint(x + 135 + 135, y - 20));
		ofLine(ofPoint(x + 135 + 135, y - 20), ofPoint(x + 135 + 135, y));
		ofLine(ofPoint(x + 135 + 135, y), ofPoint(x + panelWidth, y));
		ofLine(ofPoint(x + panelWidth, y), ofPoint(x + panelWidth, y + panelHeight));
		ofLine(ofPoint(x, y + panelHeight), ofPoint(x + panelWidth, y + panelHeight));

	
		//Draw Scenes
		//	1. Particle System
		ofSetColor(ofColor(255, 255, 255));
		particleSystemScene.begin();
		particleSystemImage.draw(0,0);
		particleSystemScene.end();
		particleSystemScene.draw(x + 8 + 8, y + 8 + 8);
		ofSetColor(ofColor::darkGray);
		ofDrawBitmapString("Particles System", x + 8 + particleSystemScene.getWidth()/3, y + 8 + 15 + particleSystemScene.getHeight() + 10);

		if(darkTheme)
			ofSetColor(ofColor::darkGray);
		else
			ofSetColor(ofColor(10,10,10));
		ofNoFill();
		ofRect(x + 8 + 8, y + 8 + 8, particleSystemScene.getWidth(), particleSystemScene.getHeight());

		if(hoveringParticleSystemScene && !hoveringExplorePS){
				ofNoFill();
				ofSetLineWidth(2);
				ofRect(x + 8 + 8, y + 8 + 8, particleSystemScene.getWidth(), particleSystemScene.getHeight());
				ofSetLineWidth(1);
		}

		//Draw 'Explore' button
		exploreButton_PS.begin();
		if(!hoveringExplorePS)
			exploreIcon_PS.loadImage("preview_normal.png");
		else
			exploreIcon_PS.loadImage("preview_hovering.png");
		exploreIcon_PS.resize(buttonSize, buttonSize);
		exploreIcon_PS.draw(0,0);
		exploreButton_PS.end();
		exploreButton_PS.draw(x + 8 + 8 + buttonSize/2, y + 8 + 8 + particleSystemScene.getHeight() - buttonSize/2 - buttonSize);

		//
		//	2. JointsDraw
		ofSetColor(ofColor(255, 255, 255));
		jointsDrawScene.begin();
		jointsDrawImage.draw(0,0);
		jointsDrawScene.end();
		jointsDrawScene.draw(x + 8 + panelWidth - 16 - 8 - jointsDrawScene.getWidth(), y + 8 + 8);
		if(darkTheme)
			ofSetColor(ofColor::darkGray);
		else
			ofSetColor(ofColor(10,10,10));
		ofDrawBitmapString("Joints Draw", x + 8 + panelWidth - 16 - 8 - jointsDrawScene.getWidth() + jointsDrawScene.getWidth()/3, y + 8 + 15 + jointsDrawScene.getHeight() + 10);

		ofNoFill();
		ofRect(x + 8 + panelWidth - 16 - 8 - jointsDrawScene.getWidth(), y + 8 + 8, jointsDrawScene.getWidth(), jointsDrawScene.getHeight());

		if(hoveringJointsDrawScene && !hoveringExploreJD){
				ofNoFill();
				ofSetLineWidth(2);
				ofRect(x + 8 + panelWidth - 16 - 8 - jointsDrawScene.getWidth(), y + 8 + 8, jointsDrawScene.getWidth(), jointsDrawScene.getHeight());
				ofSetLineWidth(1);
		}
		
		//Draw 'Explore' button
		exploreButton_JD.begin();
		if(!hoveringExploreJD)
			exploreIcon_JD.loadImage("preview_normal.png");
		else
			exploreIcon_JD.loadImage("preview_hovering.png");
		
		exploreIcon_JD.resize(buttonSize, buttonSize);
		exploreIcon_JD.draw(0,0);
		exploreButton_JD.end();
		exploreButton_JD.draw(x + 8 + panelWidth - 16 - 8 - jointsDrawScene.getWidth() + buttonSize/2, y + 8 + 8 + jointsDrawScene.getHeight() - buttonSize/2 - buttonSize);
		
		//
	}else{
		if(!hoveringScenesMarker)
			ofSetColor(primaryColor);
		else
			ofSetColor(secondaryColor.r + 15, secondaryColor.g + 15, secondaryColor.b + 15);

		ofRect(ofPoint(x + 135 + 1, y - 20), 134, 19);

		ofSetColor(detailColor.r - 80, detailColor.g - 80, detailColor.b - 80);
		ofDrawBitmapString("Scenes:", x + 135 + 10 , y - 5);

		ofSetLineWidth(1);
		ofLine(ofPoint(x + 135 + 1, y - 20), ofPoint(x + 135 + 1 + 134, y - 20));
		ofLine(ofPoint(x + 135 + 1 + 134, y - 20), ofPoint(x + 135 + 1 + 134, y - 1));

	}
}

void ofApp::drawPreviewPanel(float x, float y){
	ofSetColor(secondaryColor);
	ofFill();
	
	
	ofRect(ofPoint(x,y), previewPanelWidth, previewPanelHeight);
	ofRect(ofPoint(x, y - 20), 100, 20);

	ofSetColor(detailColor);
	ofLine(ofPoint(x, y - 20), ofPoint(x, y + previewPanelHeight));
	ofLine(ofPoint(x, y + previewPanelHeight), ofPoint(x + previewPanelWidth, y + previewPanelHeight));
	ofLine(ofPoint(x, y - 20), ofPoint(x + 100, y - 20));
	ofLine(ofPoint(x + 100, y -20), ofPoint(x + 100, y));
	ofLine(ofPoint(x + 100, y), ofPoint(x + previewPanelWidth, y));
	ofLine(ofPoint(x + previewPanelWidth, y), ofPoint(x + previewPanelWidth, y + previewPanelHeight));

	ofDrawBitmapString("Preview:", x + 10 , y - 5);
	
	//Draw container
	ofSetColor(primaryColor);
	ofRect(ofPoint(x + 8,y + 8), previewPanelWidth - 16, previewPanelHeight - 16);

	//Draw player screen
	previewPlayer.draw(x, y, previewPanelHeight);
	


	//Draw player buttons
	//Play/Pause
	int buttonSize = 50;
	int triangleMarginX = 20;
	int triangleMarginY = 8;
	int rectWidth = 4;
	
	if(!hoveringPlayPause)
		ofSetColor(10,10,10);
	else
		ofSetColor(ofColor::darkGray);
	ofRect(x + 8 + previewPanelWidth/2 - buttonSize/2, y + 8 + previewPanelHeight - buttonSize, buttonSize, buttonSize/2);
	
	if(!hoveringPlayPause)
		ofSetColor(ofColor::darkGray);
	else
		ofSetColor(10,10,10);

	if(!playingSequence)
		ofTriangle(ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 + triangleMarginX, y + 8 + previewPanelHeight - buttonSize + triangleMarginY), ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 + triangleMarginX, y + 8 + previewPanelHeight - buttonSize/2 - triangleMarginY), ofPoint(x + 8 + previewPanelWidth/2 + buttonSize/2 - triangleMarginX, y + 8 + previewPanelHeight - buttonSize + (buttonSize/2)/2));
	else{
		ofRect(ofPoint(x + 8 + previewPanelWidth/2 - rectWidth - 2, y + 8 + previewPanelHeight - buttonSize + triangleMarginY), rectWidth, buttonSize/2 - (2 * triangleMarginY));
		ofRect(ofPoint(x + 8 + previewPanelWidth/2 + 2, y + 8 + previewPanelHeight - buttonSize + triangleMarginY), rectWidth, buttonSize/2 - (2 * triangleMarginY));
	}

	//Skip to timestamp
	int skipButtonSize = 40;
	int skipTriangleMarginX = 17;
	int skipTriangleMarginY = 6;
	int skipRectWidth = 2;
	//Skip left
	if(!hoveringSkipLeft)
		ofSetColor(10,10,10);
	else
		ofSetColor(ofColor::darkGray);
	ofRect(x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipButtonSize, y + 8 + previewPanelHeight - buttonSize + 3, skipButtonSize, skipButtonSize/2);
	
	if(!hoveringSkipLeft)
		ofSetColor(ofColor::darkGray);
	else
		ofSetColor(10,10,10);
	ofTriangle(ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipButtonSize + skipTriangleMarginX, y + 8 + previewPanelHeight - buttonSize + 3 + (skipButtonSize/2)/2), ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipTriangleMarginX, y + 8 + previewPanelHeight - buttonSize + 3 + skipTriangleMarginY), ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipTriangleMarginX, y + 8 + previewPanelHeight - buttonSize + 3 + skipButtonSize/2 - skipTriangleMarginY));
	ofRect(x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipButtonSize + skipTriangleMarginX - skipRectWidth, y + 8 + previewPanelHeight - buttonSize + 3 + skipTriangleMarginY, skipRectWidth, skipButtonSize/2 - (2*skipTriangleMarginY));

	//Skip right
	if(!hoveringSkipRight)
		ofSetColor(10,10,10);
	else
		ofSetColor(ofColor::darkGray);
	ofRect(x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10, y + 8 + previewPanelHeight - buttonSize + 3, skipButtonSize, skipButtonSize/2);
	
	if(!hoveringSkipRight)
		ofSetColor(ofColor::darkGray);
	else
		ofSetColor(10,10,10);
	ofTriangle(ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10 + skipButtonSize - skipTriangleMarginX - skipRectWidth + 2, y + 8 + previewPanelHeight - buttonSize + 3 + (skipButtonSize/2)/2), ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10 + skipTriangleMarginX, y + 8 + previewPanelHeight - buttonSize + 3 + skipTriangleMarginY), ofPoint(x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10 + skipTriangleMarginX, y + 8 + previewPanelHeight - buttonSize + 3 + skipButtonSize/2 - skipTriangleMarginY));
	ofRect(x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10 + skipButtonSize - skipTriangleMarginX - skipRectWidth + 2, y + 8 + previewPanelHeight - buttonSize + 3 + skipTriangleMarginY, skipRectWidth, skipButtonSize/2 - (2*skipTriangleMarginY));

	

	//Checking hover is here due to the lot of variables involved!
	//Left skip button
	if(mouseX > x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipButtonSize && mouseX < (x + 8 + previewPanelWidth/2 - buttonSize/2 - 5 - skipButtonSize) + skipButtonSize &&
		mouseY > y + 8 + previewPanelHeight - buttonSize + 3 && mouseY < (y + 8 + previewPanelHeight - buttonSize + 3) + skipButtonSize/2)
			hoveringSkipLeft = true;
	else
		hoveringSkipLeft = false;

	//Right skip button
	if(mouseX > x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10 && mouseX < (x + 8 + previewPanelWidth/2 - buttonSize/2 + 5 + skipButtonSize + 10) + skipButtonSize &&
		mouseY > y + 8 + previewPanelHeight - buttonSize + 3 && mouseY < (y + 8 + previewPanelHeight - buttonSize + 3) + skipButtonSize/2)
			hoveringSkipRight = true;
	else
		hoveringSkipRight = false;

}

void ofApp::drawSoundsPanel(float x, float y){
	ofSetColor(255,255,255,255);

	int panelHeight = ofGetHeight() - 150 - 80 - soundHeight;
	int panelWidth = ofGetWidth() / 2;
	
	ofFill();
	
	if(showSoundsPanel){
		ofSetColor(secondaryColor);
		ofRect(ofPoint(x + 135 + 135, y - 20), 135, 20);
		ofRect(ofPoint(x,y), panelWidth, panelHeight);

		//Draw container
		ofSetColor(primaryColor);
		ofRect(ofPoint(x + 8,y + 8), panelWidth - 16, panelHeight - 16);

		//Draw marker and contour
		ofSetColor(detailColor);
		ofDrawBitmapString("Sounds:", x + 135 + 135 + 10 , y - 5);
		
		ofLine(ofPoint(x, y), ofPoint(x, y + panelHeight));
		ofLine(ofPoint(x, y), ofPoint(x + 135 + 135, y));
		ofLine(ofPoint(x + 135 + 135, y), ofPoint(x + 135 + 135, y -20));
		ofLine(ofPoint(x + 135 + 135, y -20), ofPoint(x + 135 + 135 + 135, y - 20));
		ofLine(ofPoint(x + 135 + 135 + 135, y - 20), ofPoint(x + 135 + 135 + 135, y));
		ofLine(ofPoint(x + 135 + 135 + 135, y), ofPoint(x + panelWidth, y));
		ofLine(ofPoint(x + panelWidth, y), ofPoint(x + panelWidth, y + panelHeight));
		ofLine(ofPoint(x, y + panelHeight), ofPoint(x + panelWidth, y + panelHeight));

		//Draw 'Add' button
		if(!hoveringAddSoundButton)
			ofSetColor(ofColor(10, 10, 10));
		else
			ofSetColor(ofColor::darkGray);
		ofFill();
		ofRect(x + 8 + 5, y + 8 + panelHeight - 16 - 5 - buttonSize, buttonSize, buttonSize);

		if(!hoveringAddSoundButton)
			ofSetColor(ofColor::darkGray);
		else
			ofSetColor(ofColor(10, 10, 10));
		ofSetLineWidth(2);
		ofLine(ofPoint(x + 8 + 5 + buttonSize/2, y + 8 + panelHeight -16 - 5 - buttonSize + 4), ofPoint(x + 8 + 5 + buttonSize/2, y + 8 + panelHeight -16 - 5 - buttonSize + 2 + buttonSize - 4 - 2));
		ofLine(ofPoint(x + 8 + 5 + 4, y + 8 + panelHeight -16 - 5 - buttonSize/2), ofPoint(x + 8 + 5 + buttonSize - 4, y + 8 + panelHeight -16 - 5 - buttonSize/2));
		ofxUISetLineWidth(1);
	}
	else
	{
		if(!hoveringSoundsPanelMarker)
			ofSetColor(primaryColor);
		else
			ofSetColor(secondaryColor.r + 15, secondaryColor.g + 15, secondaryColor.b + 15);

		ofRect(ofPoint(x + 135 + + 135 + 1, y - 20), 134, 19);

		ofSetColor(detailColor.r - 80, detailColor.g - 80, detailColor.b - 80);
		ofDrawBitmapString("Sounds:", x + 135 + 135 + 10 , y - 5);

		ofSetLineWidth(1);
		ofLine(ofPoint(x + 135 + 135 + 1, y - 20), ofPoint(x + 135 + 135 + 1 + 134, y - 20));
		ofLine(ofPoint(x + 135 + 135 + 1 + 134, y - 20), ofPoint(x + 135 + 135 + 1 + 134, y - 1));
	}
}

void ofApp::drawTimeline(float x, float y){
	ofSetColor(secondaryColor);
	ofFill();
	
	timelineHeight = 150 + soundHeight;
	timelineWidth = ofGetWidth() - (x * 2) - 300;

	ofRect(ofPoint(x,y), timelineWidth, timelineHeight);
	ofRect(ofPoint(x, y - 20), 115, 20);

	ofSetColor(detailColor);
	ofLine(ofPoint(x, y - 20), ofPoint(x, y + timelineHeight));
	ofLine(ofPoint(x, y + timelineHeight), ofPoint(x + timelineWidth, y + timelineHeight));
	ofLine(ofPoint(x, y - 20), ofPoint(x + 115, y -20));
	ofLine(ofPoint(x + 115, y -20), ofPoint(x + 115, y));
	ofLine(ofPoint(x + 115, y), ofPoint(x + timelineWidth, y));
	ofLine(ofPoint(x + timelineWidth, y), ofPoint(x + timelineWidth, y + timelineHeight));

	ofDrawBitmapString("Sequence:", x + 10 , y - 5);

	//Draw container
	ofSetColor(primaryColor);
	ofRect(ofPoint(x + 8,y + 8), timelineWidth - 16, timelineHeight - 16);
	
	//Draw scenes container
	ofSetColor(backgroundColor);
	ofRect(ofPoint(x + 8, ofGetHeight() - 150 - 10 + 60 - soundHeight), timelineWidth - 16, (timelineHeight - 16) - ((ofGetHeight() - 150 - 10 + 60) - (y + 8)));
	ofSetColor(ofColor::darkGray);
	if(noScenesOnTimeline)
		ofDrawBitmapString("Drag scenes here", x + 8 + 50, ofGetHeight() - 150 - 10 + 60 - soundHeight + ((timelineHeight - 16) - ((ofGetHeight() - 150 - 10 + 60) - (y + 8)))/2);
	
	//Draw sound container
	ofSetColor(backgroundColor);
	ofRect(ofPoint(x + 8, ofGetHeight() - 150 - 10 + 60 + 10 + soundHeight), timelineWidth - 16, soundHeight - 10);
	ofSetColor(ofColor::darkGray);
	if(noSoundOnTimeline)
		ofDrawBitmapString("Drag sound files here", x + 8 + 50,  ofGetHeight() - 150 - 10 + 60 + 10 + soundHeight + (soundHeight - 10)/2 + 2);

	if(mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 && mouseY < (ofGetHeight() - 150 - 10 + 8) + 150 - 16 - soundHeight){
		if(draggingJointsDrawScene || draggingParticleSystemScene){
			ofSetColor(ofColor::grey);
			ofNoFill();
			ofSetLineWidth(2);
			ofRect(ofPoint(x + 8, ofGetHeight() - 150 - 10 + 60 - soundHeight), timelineWidth - 16, (timelineHeight - 16) - ((ofGetHeight() - 150 - 10 + 60) - (y + 8)));
			ofSetLineWidth(1);
		}
	}

	if(draggingAudioFile && mouseX > 18 && mouseX < ofGetWidth() - (10 * 2) - 300 - 16 &&
							mouseY > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && mouseY < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
		ofNoFill();
		ofSetColor(ofColor::grey);
		ofSetLineWidth(2);
		ofRect(x + 8, ofGetHeight() - 150 - 10 + 60 + 10 + soundHeight, timelineWidth - 16, soundHeight - 10);
		ofSetLineWidth(1);
	}

	//Draw time ruler
	ofSetColor(ofColor::gray);
	ofSetLineWidth(0.1);
	ofLine(x + 10, y+10, x + timelineWidth - 10, y+10);
	for(int i = 0; i < timelineWidth - 20; i+=maxTime/6){
		ofLine(x + 10 + i, y + 10, x + 10 + i, y + 15);			// !!! Fix in order to to shrink when maxTime grows, and not the opposite !!!
    }
	ofDrawBitmapString("0.0", x + 10, y + 28);
	ostringstream buff; buff << maxTime; 
	ofDrawBitmapString(buff.str(), x + 10 + timelineWidth - 16 - 28, y + 28);

}

void ofApp::drawActionButtons(float x, float y){
	ofSetCircleResolution(30);

	int iconWidth = 40;
	int iconHeight = 30;

	ofFill();
	ofSetColor(ofColor::black);
	ofCircle(x + (ofGetWidth() - x)/2, y + 10 + buttonRadius , buttonRadius);

	ofNoFill();
	if(!hoveringLaunchButton)
		ofSetColor(ofColor::orange);
	else{
		ofSetColor(ofColor::white);
		ofSetLineWidth(2);
	}
	ofCircle(x + (ofGetWidth() - x)/2, y + 10 + buttonRadius , buttonRadius);
	ofSetLineWidth(1);
	ofRect(x + (ofGetWidth() - x)/2 - iconWidth, y + 10 + buttonRadius - iconHeight, iconWidth, iconHeight);
	ofLine(ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight), ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth, y + 10 + buttonRadius - iconHeight + 10));
	ofLine(ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight + iconHeight), ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth, y + 10 + buttonRadius - iconHeight + iconHeight - 10));
	ofLine(ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight + iconHeight), ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight));
	ofLine(ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15 + 25, y + 10 + buttonRadius - iconHeight - 6), ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight + 10));
	ofLine(ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15 + 25, y + 10 + buttonRadius - iconHeight + iconHeight + 6), ofPoint(x + (ofGetWidth() - x)/2 - iconWidth + iconWidth + 15, y + 10 + buttonRadius - iconHeight + iconHeight - 10));
	
	ofDrawBitmapString("Launch", x + (ofGetWidth() - x)/2 - 25, y + 10 + buttonRadius + buttonRadius/2);
}

void ofApp::addTimelineObject(int typeOfObject){
	float prevObjEndingTime = 0;
	if(timelineObjects.size() > 0){prevObjEndingTime = timelineObjects[timelineObjects.size() - 1].ending + 1;
	}
	
	TimelineGraphicalObject newTO;
	newTO.setup(typeOfObject, prevObjEndingTime);
	timelineObjects.push_back(newTO);
	
	if(newTO.ending > maxTime)
		maxTime = newTO.ending;

	printf("Scene sucessfully added to timeline!\n");

	previewPlayer.updateTimelineObjects(timelineObjects);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(!exploringPS && !exploringJD &&!exploringAudio){
		switch (key){
		case '+':
			maxTime += 10.5;
			break;
		case '-':
			maxTime -= 10.5;
			break;
		case ' ':
			playingSequence = !playingSequence;
			break;
		case OF_KEY_RETURN:
			currentTime = 0;
			playingSequence = true;
			if(timelineObjects.size() > 0)
				previewPlayer.resetDemos();
			if(soundFiles.size()>0){
				for(int i = 0; i < soundFiles.size(); i++)
					soundFiles[i].resetAudioPlay(maxTime);
			}
			break;
		case OF_KEY_RIGHT:
			currentTime++;
			break;
		case OF_KEY_LEFT:
			currentTime--;
			break;
		case OF_KEY_DEL:
			//Graphical scenes on timeline
			if(timelineObjects.size() > 0){
				for(int i = 0; i < timelineObjects.size(); i++){
					if(timelineObjects[i].isSelected){
						delete timelineObjects[i].pL.ddl_gui;
						//delete timelineObjects[i].pL.paste_gui;
						timelineObjects[i].pL.guis[i]->setVisible(false);
						delete timelineObjects[i].pL.guis[i];
						timelineObjects.erase(timelineObjects.begin() + i);
					}
				}
				previewPlayer.updateTimelineObjects(timelineObjects);
			}

			//Audio scenes on timeline
			if(soundFiles.size()>0){
				for(int i = 0; i < soundFiles.size(); i++)
					if(soundFiles[i].soundsTimeline.size()>0)
						for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++)
							if(soundFiles[i].soundsTimeline[j].isSelected){
								delete soundFiles[i].soundsTimeline[j].pL.ddl_gui;
								soundFiles[i].soundsTimeline[j].pL.guis[j]->setVisible(false);
								delete soundFiles[i].soundsTimeline[j].pL.guis[j];
								soundFiles[i].soundsTimeline.erase(soundFiles[i].soundsTimeline.begin() + j);
							}
			}

			break;
		case 'f':
			maxEnding = 0;
			if(timelineObjects.size() > 0){
				for(int i = 0; i < timelineObjects.size(); i++){
					if(timelineObjects[i].ending > maxEnding)
						maxEnding = timelineObjects[i].ending;
				}
			}

			if(soundFiles.size()>0){
				for(int i = 0; i < soundFiles.size(); i++){
					if(soundFiles[i].soundsTimeline.size() > 0){
						for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++){
							if(soundFiles[i].soundsTimeline[j].ending > maxEnding)
								maxEnding = soundFiles[i].soundsTimeline[j].ending;
						}
					}
				}
			}
			maxTime = maxEnding;
			break;
		case 't':
			darkTheme = !darkTheme;
			break;
		case 'i':
			fps->toggleVisible();
			guiInfo->toggleVisible();
			break;

		case 'h':
			previewPlayer.skeletonVisible = !previewPlayer.skeletonVisible;
			break;
		}
	}
	else
	{
		if(exploringPS){
			particleSystemKinectPreview.keyPressed(key);
		}
		else
			if(exploringJD)
				jointsDrawKinectPreview.keyPressed(key);
			else
				if(exploringAudio)
					interactiveAudioKinect.keyPressed(key);
		switch (key){
		case 'e':
			if(exploringPS){
				loading = false;

				particleSystemKinectPreview.drawInterface = false;
				particleSystemKinectPreview.interf.gui1->setVisible(false);
				particleSystemKinectPreview.interf.gui2->setVisible(false);
				particleSystemKinectPreview.interf.gui3->setVisible(false);
				particleSystemKinectPreview.exit();
				exploringPS = false;
			}
			else 
				if(exploringJD){
					loading = false;

					jointsDrawKinectPreview.drawInterface = false;
					jointsDrawKinectPreview.interf.guiFPS->setVisible(false);
					jointsDrawKinectPreview.interf.guiInfo->setVisible(false);
					//jointsDrawKinectPreview.interf.guiJoints->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Head->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Neck->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ShoulderL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ShoulderR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ElbowL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ElbowR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HandL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HandR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Torso->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HipL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HipR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_KneeL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_KneeR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_FootL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_FootR->setVisible(false);
					jointsDrawKinectPreview.exit();
					exploringJD = false;
				}
				else
					if(exploringAudio){
						loading = false;

						interactiveAudioKinect.sound.stop();
						interactiveAudioKinect.exit();
						for(int i = 0; i < soundFiles.size(); i++)
							if(soundFiles[i].exploringAudio){
								soundFiles[i].exploringAudio = false;
							}

						exploringAudio = false;
					}
			break;
		}
	}

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){
	if(!exploringPS && !exploringJD && !exploringAudio){

		//Check Launch button
		if(mouseX > (10 + timelineWidth + (ofGetWidth() - (10 + timelineWidth))/2) - buttonRadius && mouseX < (10 + timelineWidth + (ofGetWidth() - (10 + timelineWidth))/2) + buttonRadius
			&& mouseY > (ofGetHeight() - 10 - timelineHeight) + 10 && mouseY < ((ofGetHeight() - 10 - timelineHeight) + 10) + buttonRadius*2){
				printf("Hovering Launch button ... \n");
				hoveringLaunchButton = true;
		}
		else
			hoveringLaunchButton = false;
			

		//Check panel selection
		if(mouseX > 10 && mouseX < 10 + 135 && mouseY > 30 - 20 && mouseY < 30){
			//printf("Hovering Parameters Marker ... \n");
			hoveringParametersPanelMarker = true;
		}
		else{
			hoveringParametersPanelMarker = false;

			if(mouseX > 10 + 135 && mouseX < 10 + 135 + 135 && mouseY > 30 - 20 && mouseY < 30){
				//printf("Hovering Scenes Marker ... \n");
				hoveringScenesMarker = true;
			}
			else{
				hoveringScenesMarker = false;
				if(mouseX > 10 + 135 + 135 && mouseX < 10 + 135 + 135 + 135 && mouseY > 30 - 20 && mouseY < 30){
					//printf("Hovering Sounds Marker ... \n");
					hoveringSoundsPanelMarker = true;
				}
				else
					hoveringSoundsPanelMarker = false;	
			}
		}
		
		

		//Check in which panel I'm at
		if(mouseX < 10 + ofGetWidth()/2 - 8 && mouseX > 18 && mouseY > 38 && mouseY < 38 + ofGetHeight() - 150 - 96 - soundHeight){
			if(showScenesPalette){
				//printf("Inside Scenes Palette!\n");

				if(mouseX > 10 + 8 + 8 && mouseX < 10 + 8 + 8 + particleSystemScene.getWidth() &&
					mouseY > 30 + 8 + 8 && mouseY < 30 + 8 + 8 + particleSystemScene.getHeight()){
					hoveringParticleSystemScene = true; 
					if(mouseX > 10 + 8 + 8 + buttonSize/2 && mouseX < 10 + 8 + 8 + buttonSize/2 + buttonSize &&
						mouseY > 30 + 8 + 8 + particleSystemScene.getHeight() - buttonSize/2 - buttonSize && mouseY < 30 + 8 + 8 + particleSystemScene.getHeight() - buttonSize/2)
						hoveringExplorePS = true;
					else
						hoveringExplorePS = false;
					//printf("Particle System ...\n");
				}
				else{
					hoveringParticleSystemScene = false;

					if(mouseX > 10 + 8 + ofGetWidth()/2 - 16 - 8 - jointsDrawScene.getWidth() && mouseX < 10 + 8 + ofGetWidth()/2 - 16 - 8 &&
						mouseY > 30 + 8 + 8 && mouseY < 30 + 8 + 8 + jointsDrawScene.getHeight()){
						//printf("Joints Draw ...\n");
						hoveringJointsDrawScene = true;
						if(mouseX > 10 + 8 + ofGetWidth()/2 - 16 - 8 - jointsDrawScene.getWidth() + buttonSize/2 && mouseX < 10 + 8 + ofGetWidth()/2 - 16 - 8 - jointsDrawScene.getWidth() + buttonSize/2 + buttonSize &&
						mouseY > 30 + 8 + 8 + jointsDrawScene.getHeight() - buttonSize/2 - buttonSize && mouseY < 30 + 8 + 8 + jointsDrawScene.getHeight() - buttonSize/2)
							hoveringExploreJD = true;
						else
							hoveringExploreJD = false;
					}
					else
						hoveringJointsDrawScene = false;
				}
			}else{
				if(!showSoundsPanel){
					//printf("Inside Parameters Panel!\n");

					if(mouseX > 10 + 8 + 5 && mouseX < 10 + 8 + 5 + ofGetWidth() / 2 / 20 && mouseY >  30 + 8 + ofGetHeight() - 150 - 80 - 40 - 16 - 5 - 40 && mouseY < 30 + 8 + ofGetHeight() - 150 - 80 - 40 - 16 - 5)
						hoveringAddButton = true;
					else{
						hoveringAddButton = false;
						if(mouseX > 10 + 8 + (ofGetWidth()/2) - 16 - 5 - deleteButton.getWidth() && mouseX < 10 + 8 + (ofGetWidth()/2) - 16 - 5  &&
							mouseY > 10 + 8 + ofGetHeight() - 150 - 80 - soundHeight - 16 - 10 && mouseY < (10 + 8 +  ofGetHeight() - 150 - 80 - soundHeight - 16 - 10) + deleteButton.getHeight()){
								hoveringDeleteButton = true;
						}
						else{
							hoveringDeleteButton = false;
							if(anySelected){
								if(mouseX > 18 + 5 && mouseX < 18 + 5 + 150 && mouseY > 18 + (ofGetHeight() - 150 - 80 - (ofGetWidth()/2) / 20) - 16 - 5 - (ofGetWidth()/2) / 20 - 10 - 20 && mouseY < 18 + (ofGetHeight() - 150 - 80 - (ofGetWidth()/2) / 20) - 16 - 5 - (ofGetWidth()/2) / 20){
									hoveringPasteButton = true;
								}
								else
									hoveringPasteButton = false;
							}
						}
					}
				}
				else
				{
					//printf("Inside Sounds Panel!\n");
					if(mouseX > 10 + 8 + 5 && mouseX < 10 + 8 + 5 + ofGetWidth() / 2 / 20 && mouseY >  30 + 8 + ofGetHeight() - 150 - 80 - 40 - 16 - 5 - 40 && mouseY < 30 + 8 + ofGetHeight() - 150 - 80 - 40 - 16 - 5)
						hoveringAddSoundButton = true;
					else
						hoveringAddSoundButton = false;
				}
			}
		}
		else
			if(mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 - soundHeight && mouseY < (ofGetHeight() - 150 - 10 + 8) + 150 - 16){
				//printf("Inside Timeline!\n");
				if(mouseX > 18 && mouseX < ofGetWidth() - (10 * 2) - 300 - 16 &&
					mouseY > ofGetHeight() - 150 - 10 + 60 + 10 + 40 && mouseY < ofGetHeight() - 150 - 10 + 60 + 10 + 40 + 30){
						//Inside sound timeline container
						hoveringSoundTimeline = true;
					}
					else
						hoveringSoundTimeline = false;
			}
			else
				if(mouseX > ofGetWidth() / 2 + 15 && mouseX < (ofGetWidth() / 2 + 15) + ofGetWidth() / 2 - 30 && mouseY > 30 && mouseY < 30 + ofGetHeight() - 150 - 80 - soundHeight ){
					//printf("Inside Preview Panel!\n");
					cout << "Mouse: (" << mouseX << ", " << mouseY << ")" << endl;

					if(mouseX > (ofGetWidth() / 2 + 15) + 8 + (ofGetWidth() / 2 - 30)/2 - 50/2 && mouseX < ((ofGetWidth() / 2 + 15) + 8 + (ofGetWidth() / 2 - 30)/2 - 50/2) + 50 &&
						mouseY > 30 + 8 + (ofGetHeight() - 150 - 80 - soundHeight) - 50 && mouseY < (30 + 8 + (ofGetHeight() - 150 - 80 - soundHeight) - 50) + 50/2){
						hoveringPlayPause = true;
					}
					else
						hoveringPlayPause = false;
				}
				else
					hoveringAddButton = hoveringPasteButton = hoveringDeleteButton = hoveringParticleSystemScene = hoveringJointsDrawScene = hoveringPlayPause = hoveringExplorePS = hoveringExploreJD = false;


		for(int i = 0; i < timelineObjects.size(); i++)
			timelineObjects[i].mouseMoved(mouseX, mouseY);

		for(int i = 0; i < soundFiles.size(); i++)
			soundFiles[i].mouseMoved(mouseX, mouseY);
	}	// -------------------------------------------------------------------------------------------------
	else{
		if(exploringPS)
			particleSystemKinectPreview.mouseMoved(mouseX, mouseY);
		else
			if(exploringJD)
				jointsDrawKinectPreview.mouseMoved(mouseX,mouseY);
	}
}

void ofApp::mouseDragged(int x, int y, int button){
	
	if(!exploringPS && !exploringJD && !exploringAudio){
		if(!draggingParticleSystemScene && !draggingJointsDrawScene)
			for(int i = 0; i < timelineObjects.size(); i++)
				timelineObjects[i].mouseDragged(mouseX, mouseY, timeDisplay, maxTime, timelineObjects);
	}
	else{
		if(exploringPS)
			particleSystemKinectPreview.mouseDragged(mouseX, mouseY);
		else
			if(exploringJD)
				jointsDrawKinectPreview.mouseDragged(mouseX,mouseY);
	}

	for(int i = 0; i < soundFiles.size(); i++)
			soundFiles[i].mouseDragged(mouseX, mouseY, timeDisplay, maxTime);
}

void ofApp::mousePressed(int x, int y, int button){
	if(!exploringPS && !exploringJD && !exploringAudio){
		if(hoveringScenesMarker){
			showScenesPalette = true;
			showSoundsPanel = false;
		}
		else
			if(hoveringParametersPanelMarker){
				showScenesPalette = false;
				showSoundsPanel = false;
			}
			else
				if(hoveringSoundsPanelMarker){
					showScenesPalette = false;
					showSoundsPanel = true;
				}
			
		if(mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 - soundHeight && mouseY < ofGetHeight() - 150 - 10 + 60 - soundHeight)
			draggingTimeMarker = true;

		if(hoveringParticleSystemScene && !hoveringExplorePS){
			draggingParticleSystemScene = true;
		}

		if(hoveringExplorePS){
			loading = true;
		}
		else
			if(hoveringExploreJD){
				loading = true;
			}
			else{
				if(soundFiles.size()>0){
					for(int i = 0; i < soundFiles.size(); i++)
						if(soundFiles[i].exploringAudio){
							loading = true;
						}
				}
			}

		if(hoveringJointsDrawScene && !hoveringExploreJD){
			draggingJointsDrawScene = true;
		}

		if(hoveringPlayPause)
			playingSequence = !playingSequence;

		for(int i = 0; i < timelineObjects.size(); i++)
			timelineObjects[i].mousePressed(mouseX, mouseY, timeDisplay);

		for(int i = 0; i < soundFiles.size(); i++)
			soundFiles[i].mousePressed(mouseX, mouseY, timeDisplay);

		//Player controls
		float newCurrentCandidate = 0;
		if(hoveringSkipLeft){
			for(int i = 0; i < timelineObjects.size(); i++){
					for(int j = 0; j < timelineObjects[i].pL.parameters.size(); j++)
						if(timelineObjects[i].pL.parameters[j][0] < currentTime){
							if(timelineObjects[i].pL.parameters[j][0] > newCurrentCandidate)
								newCurrentCandidate = timelineObjects[i].pL.parameters[j][0];	
						}
			}
			currentTime = newCurrentCandidate;
		}

		newCurrentCandidate = maxTime;
		if(hoveringSkipRight){
			for(int i = 0; i < timelineObjects.size(); i++){
				for(int j = 0; j < timelineObjects[i].pL.parameters.size(); j++)
					if(timelineObjects[i].pL.parameters[j][0] > currentTime){
						if(timelineObjects[i].pL.parameters[j][0] < newCurrentCandidate)
								newCurrentCandidate = timelineObjects[i].pL.parameters[j][0];	
					}
			}
			currentTime = newCurrentCandidate;
		}
	}

}

void ofApp::mouseReleased(int x, int y, int button){
	if(!exploringPS && !exploringJD && !exploringAudio){
		
		if(hoveringLaunchButton && !noScenesOnTimeline){
			controlWindow.setup("Control", 50, 50, 1024, 768, false);
			//projectorWindow.setup("Projection", ofGetScreenWidth(), 0, ofGetScreenWidth(), ofGetScreenHeight(), true);
			projectorWindow.setup("Projection", 0, 0, ofGetScreenWidth(), ofGetScreenHeight(), false);
			
			sequenceProjection.setup(timelineObjects, soundFiles);

			projectingSequence = true;
		}
	
		if(hoveringExplorePS){
			playingSequence = false;
			exploringPS = true;
			
			particleSystemKinectPreview.setup(0, true);
		}
		else
			if(hoveringExploreJD){
				playingSequence = false;
				exploringJD = true;
				
				jointsDrawKinectPreview.setup(1, true);
			}


		if(draggingAudioFile)
			draggingAudioFile = false;

		if(draggingTimeMarker){
			if(timelineObjects.size() > 0)
				previewPlayer.resetDemos();
			draggingTimeMarker = false;
		}

		if(draggingParticleSystemScene && mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 && mouseY < (ofGetHeight() - 150 - 10 + 8) + 150 - 16 - soundHeight){
			addTimelineObject(0);	//0 - Particle System
			timelineObjects[timelineObjects.size()-1].pL.addTimestamp(timelineObjects[timelineObjects.size()-1].beginning, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
			timelineObjects[timelineObjects.size()-1].pL.addTimestamp(timelineObjects[timelineObjects.size()-1].ending, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);

			hoveringParticleSystemScene = draggingParticleSystemScene = false;	
		}else
			if(draggingJointsDrawScene && mouseX > 18 && mouseX < 18 + ofGetWidth() - 20 - 300 - 16 && mouseY > ofGetHeight() - 150 - 10 + 8 && mouseY < (ofGetHeight() - 150 - 10 + 8) + 150 - 16 - soundHeight){
				addTimelineObject(1);	//1 - Particle System
				timelineObjects[timelineObjects.size()-1].pL.addTimestamp(timelineObjects[timelineObjects.size()-1].beginning, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
				timelineObjects[timelineObjects.size()-1].pL.addTimestamp(timelineObjects[timelineObjects.size()-1].ending, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
			
				hoveringJointsDrawScene = draggingJointsDrawScene = false;	
			}

		//Quit dragging even if I'm outside the timeline
		if(draggingParticleSystemScene)
			hoveringParticleSystemScene = draggingParticleSystemScene = false;
		else
			if(draggingJointsDrawScene)
				hoveringJointsDrawScene = draggingJointsDrawScene = false;

		if(hoveringAddButton){
			for(int i = 0; i < timelineObjects.size();i++){
				if(timelineObjects[i].isSelected && timelineObjects[i].beginning < currentTime && timelineObjects[i].ending > currentTime)
					switch(timelineObjects[i].typeOfScene){
					case 0:
						timelineObjects[i].pL.addTimestamp(currentTime, 0.03, 2, 5, 0.7, 20, 40, 100, 200, 0, 0, 0);
						break;
					case 1:
						timelineObjects[i].pL.addTimestamp(currentTime, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0.9, 0.1);
						break;
				}
			}
			for(int i = 0; i < soundFiles.size();i++){
				for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++){
					if(soundFiles[i].soundsTimeline[j].isSelected && soundFiles[i].soundsTimeline[j].beginning < currentTime && soundFiles[i].soundsTimeline[j].ending > currentTime){
						soundFiles[i].soundsTimeline[j].pL.addTimestamp(currentTime, 0, 0, 6, 1, 2, 0);
					}	
				}
			}
			hoveringAddButton = false;
		}
		else{
			if(hoveringDeleteButton){
				printf("Deleting timestamp ...\n");
		
				if(timelineObjects.size() > 0)
					for(int i = 0; i < timelineObjects.size(); i++)
						if(timelineObjects[i].isSelected)
							timelineObjects[i].pL.deleteTimestamp();

				for(int i = 0; i < soundFiles.size();i++){
					for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++){
						if(soundFiles[i].soundsTimeline[j].isSelected){
							soundFiles[i].soundsTimeline[j].pL.deleteTimestamp();
						}	
					}
				}

			}
			else
				if(hoveringPasteButton){
					printf("Pasting settings...\n");
					for(int i = 0; i < timelineObjects.size(); i++)
						if(timelineObjects[i].isSelected)
							timelineObjects[i].pL.pasteSettings();
					
					for(int i = 0; i < soundFiles.size();i++){
						for(int j = 0; j < soundFiles[i].soundsTimeline.size(); j++){
							if(soundFiles[i].soundsTimeline[j].isSelected){
								soundFiles[i].soundsTimeline[j].pL.pasteSettings();
							}	
						}
					}
				}
		}

		if(hoveringAddSoundButton){
			printf("Chosse a sound file to open...\n");

			/*
			char szFile[260]; // buffer for selected filename  

			OPENFILENAME ofn;  
			ZeroMemory(&ofn, sizeof(ofn));  
			ofn.lStructSize = sizeof(ofn);  
			ofn.lpstrFile = szFile;  
			ofn.lpstrFile[0] = '\0';  
			ofn.nMaxFile = sizeof(szFile);  
			ofn.lpstrFileTitle = NULL;  
			ofn.nMaxFileTitle = 0;  
			ofn.lpstrInitialDir = NULL;  
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  

			// Display the Open dialog box.  
			GetOpenFileName(&ofn);
			*/
			
			/*
			ofFileDialogResult fdr;
			fdr = ofSystemLoadDialog("Open sound file", false, "C:\Program Files\openFrameworks\apps\myApps\editorGUI_Test\bin\data");
			*/
		}

		//Check if calling interactive sound scene
		if(soundFiles.size()>0){
			printf("More than one sound file on the panel!\n");
			for(int i = 0; i < soundFiles.size(); i++)
				if(soundFiles[i].exploringAudio){
					printf("About to setup an interactive audio scene!\n");
					loading = true;
					interactiveAudioKinect.setup(soundFiles[i].filePath);
					exploringAudio = true;
				}
		}


		for(int i = 0; i < timelineObjects.size(); i++){
			timelineObjects[i].mouseReleased(mouseX, mouseY);
		}
	
		for(int i = 0; i < soundFiles.size(); i++){
			soundFiles[i].mouseReleased(mouseX, mouseY);
		}

		previewPlayer.updateTimelineObjects(timelineObjects);
	}
	else{
		if(exploringPS){
			particleSystemKinectPreview.mouseReleased(mouseX, mouseY);
		
			if(!particleSystemKinectPreview.interf.exploring){
				loading = false;

				particleSystemKinectPreview.drawInterface = false;
				particleSystemKinectPreview.interf.gui1->setVisible(false);
				particleSystemKinectPreview.interf.gui2->setVisible(false);
				particleSystemKinectPreview.interf.gui3->setVisible(false);
				particleSystemKinectPreview.exit();
				exploringPS = false;
			}
		}
		else
			if(exploringJD){
				jointsDrawKinectPreview.mouseReleased(mouseX, mouseY);
				
				if(!jointsDrawKinectPreview.interf.exploring){
					loading = false;

					jointsDrawKinectPreview.drawInterface = false;
					jointsDrawKinectPreview.interf.guiFPS->setVisible(false);
					jointsDrawKinectPreview.interf.guiInfo->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Head->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Neck->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ShoulderL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ShoulderR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ElbowL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_ElbowR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HandL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HandR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_Torso->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HipL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_HipR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_KneeL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_KneeR->setVisible(false);
					jointsDrawKinectPreview.interf.gui_FootL->setVisible(false);
					jointsDrawKinectPreview.interf.gui_FootR->setVisible(false);
					jointsDrawKinectPreview.exit();
					exploringJD = false;
				}
			}
	}
}

void ofApp::windowResized(int w, int h){
	//Check if the minimum resolution is respected
	if(ofGetWidth() < MIN_WIDTH)
		ofSetWindowShape(MIN_WIDTH, ofGetHeight());
	if(ofGetHeight() < MIN_HEIGHT)
		ofSetWindowShape(ofGetWidth(), MIN_HEIGHT);
	
	logoImage.loadImage("logo.png");
	logoImage.resize((ofGetHeight() * 16)/9 + 100, ofGetHeight() + 100);
	logo.allocate(logoImage.width, logoImage.height, GL_RGB32F_ARB);

	if(!exploringPS && !exploringJD && !exploringAudio){
		//Resize scenes on the palette
		//	Particle System
		particleSystemImage.loadImage("particleSystem.png");
		particleSystemImage.resize((ofGetWidth() / 2 - 30)/2 - 20, (((ofGetWidth() / 2 - 30)/2 - 20) * 9)/16);
		particleSystemScene.allocate(particleSystemImage.width, particleSystemImage.height, GL_RGB32F_ARB);
		//	Joints Draw
		jointsDrawImage.loadImage("jointsDraw.png");
		jointsDrawImage.resize((ofGetWidth() / 2 - 30)/2 - 20, (((ofGetWidth() / 2 - 30)/2 - 20) * 9)/16);
		jointsDrawScene.allocate(jointsDrawImage.width, jointsDrawImage.height, GL_RGB32F_ARB);

		//Resize draggable images
		//	Particle System
		particleSystemImageDraggable.loadImage("particleSystem.png");
		particleSystemImageDraggable.resize(particleSystemImageDraggable.width/4, particleSystemImageDraggable.height/4);
		particleSystemDraggable.allocate(particleSystemImageDraggable.width, particleSystemImageDraggable.height, GL_RGB32F_ARB);
		//	Joints Draw
		jointsDrawImageDraggable.loadImage("jointsDraw.png");
		jointsDrawImageDraggable.resize(jointsDrawImageDraggable.width/4, jointsDrawImageDraggable.height/4);
		jointsDrawDraggable.allocate(jointsDrawImageDraggable.width, jointsDrawImageDraggable.height, GL_RGB32F_ARB);

		//Resize preview player
		previewPanelHeight = ofGetHeight() - 150 - 80 - soundHeight;
		previewPanelWidth = ofGetWidth() / 2 - 30;
		previewPlayer.windowResized(previewPanelWidth);
	
		previewPlayer.resetDemos();

		buttonSize = (ofGetWidth()/2) / 20;
		junkImage.loadImage("trash_button_normal.png");
		junkImage.resize(buttonSize, buttonSize);
		deleteButton.allocate(junkImage.width, junkImage.height, GL_RGB32F_ARB);

		exploreIcon_PS.loadImage("preview_normal.png");
		exploreIcon_PS.resize(buttonSize, buttonSize);
		exploreButton_PS.allocate(exploreIcon_PS.width, exploreIcon_PS.height, GL_RGB32F_ARB);

		exploreIcon_JD.loadImage("preview_normal.png");
		exploreIcon_JD.resize(buttonSize, buttonSize);
		exploreButton_JD.allocate(exploreIcon_JD.width, exploreIcon_JD.height, GL_RGB32F_ARB);

		fps->setPosition(ofGetWidth() - GUIS_MARGIN, 5);
		guiInfo->setPosition(ofGetWidth() - GUIS_MARGIN, 25);

		for(int i = 0; i < soundFiles.size(); i++){
			soundFiles[i].windowResized(w,h);
		}
	}
	else {
		if(exploringPS)
			particleSystemKinectPreview.windowResized(w,h);
		else
			if(exploringJD)
				jointsDrawKinectPreview.windowResized(w,h);
			else
				if(exploringAudio)
					interactiveAudioKinect.windowResized(w,h);
	}
}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}