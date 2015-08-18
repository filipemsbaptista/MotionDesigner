#pragma once

#include "ofMain.h"
#include "TimelineGraphicalObject.h"
#include "PreviewPlayer.h"
#include "ofxUI.h"		//	Just for the FPS slider
#include "SoundFile.h"
#include "KinectGraphicalScene.h"
#include "KinectAudioScene.h"
#include "ofxSecondWindow.h"
#include "Projection.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		void setupInfoPanels();

		float maxTime, currentTime, maxEnding;
		float timeDisplay, timeMarkerX;
		bool draggingTimeMarker, playingSequence;

		ofImage logoImage;
		ofFbo logo;
		int logo_alpha;

		void drawLogo();
		void drawGrid(float x, float y);
		void drawTimeline(float x, float y);
		void drawParametersPanel(float x, float y);
		void drawScenesPalette(float x, float y);
		void drawSoundsPanel(float x, float y);
		void drawPreviewPanel(float x, float y);
		void drawActionButtons(float x, float y);
		
		float timelineHeight, timelineWidth;

		bool loading;

		bool showScenesPalette, showSoundsPanel, hoveringScenesMarker, hoveringParametersPanelMarker, hoveringSoundsPanelMarker, hoveringSoundTimeline, hoveringLaunchButton;
		bool hoveringParticleSystemScene, hoveringJointsDrawScene;

		void addTimelineObject(int typeOfObject);


		deque <TimelineGraphicalObject> timelineObjects;
		deque <SoundFile> soundFiles;


		ofImage particleSystemImage, jointsDrawImage, particleSystemImageDraggable, jointsDrawImageDraggable;
		ofFbo particleSystemScene, jointsDrawScene, particleSystemDraggable, jointsDrawDraggable;

		bool draggingParticleSystemScene, draggingJointsDrawScene;
		bool noScenesOnTimeline, noSoundOnTimeline;
		

		bool darkTheme;
		ofColor backgroundColor, primaryColor, secondaryColor, detailColor;

		bool hoveringAddButton, hoveringDeleteButton, hoveringPlayPause, hoveringSkipLeft, hoveringSkipRight, hoveringExplorePS, hoveringExploreJD, hoveringAddSoundButton, hoveringPasteButton;
		bool anySelected ;

		int buttonSize;			//'Add' and 'Remove' buttons size (Parameters Panel)
		ofImage junkImage;
		ofFbo deleteButton;

		ofImage exploreIcon_PS;
		ofFbo exploreButton_PS;
		
		ofImage exploreIcon_JD;
		ofFbo exploreButton_JD;

		float previewPanelWidth, previewPanelHeight;
		PreviewPlayer previewPlayer;

		bool exploringPS, exploringJD, exploringAudio;
		bool draggingAudioFile;

		
		ofxSecondWindow projectorWindow, controlWindow;
		bool projectingSequence;
		Projection sequenceProjection;

		//Kinect Scenes
		KinectAudioScene interactiveAudioKinect;
		KinectGraphicalScene particleSystemKinectPreview, jointsDrawKinectPreview;
		KinectGraphicalScene particleSystemKinect, jointsDrawKinect;
};
