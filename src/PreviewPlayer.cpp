#include "PreviewPlayer.h"

const int PLAYER_MARGIN = 10;

void PreviewPlayer::setup(int x, int y, float panelWidth, float panelHeight, deque <TimelineGraphicalObject> timelineObjs){
	previewPlayer.allocate(panelWidth - (PLAYER_MARGIN * 2) - 16, (((panelWidth - (PLAYER_MARGIN * 2) - 16)*9)/16), GL_RGB32F_ARB);
	cout << "Preview Player: " << previewPlayer.getWidth() << " x " << previewPlayer.getHeight() << endl;

	timelineObjects = timelineObjs;
	currentTime = 0;

	if(timelineObjects.size()>0){
		vector<vector<float>>parameters = timelineObjects[0].pL.parameters;
		for (int i = 0; i < timelineObjects.size(); i++){
				if(timelineObjects[i].beginning <= currentTime && timelineObjects[i].ending >= currentTime)
					parameters = timelineObjects[i].pL.parameters;
		}
		particleSystem_demo.setup(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
		jointsDraw_demo.setup(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
	}
	skeletonVisible = false;
}

//Only called by ofApp if the sequence is being played
void PreviewPlayer::update(float t){
	currentTime = t;

	//Check if there are objects in the timeline. If there is, check which should play in this instant, then get its type and call the corresponding 'update()' method
	if(timelineObjects.size()> 0){
		for (int i = 0; i < timelineObjects.size(); i++){
			if(timelineObjects[i].beginning <= currentTime && timelineObjects[i].ending >= currentTime)
				switch(timelineObjects[i].typeOfScene){
				case 0:
					printf("Updating Particles System scene ...\n");
					particleSystem_demo.updateParameters(timelineObjects[i].pL.parameters, currentTime);
					particleSystem_demo.update(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
					break;
				case 1: 
					printf("Updating Joints Draw scene ...\n");
					
					printf("Updating parameters ...\n");
					jointsDraw_demo.updateParameters(timelineObjects[i].pL.parameters, currentTime);
					printf("Updating bruses ...\n");
					jointsDraw_demo.update(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
					break;
			}
		}
	}
}

void PreviewPlayer::draw(int x, int y, float panelHeight){
	
	previewPlayer.begin();
	ofClearAlpha();
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
	
	//Check if there are objects in the timeline. If there is, check which should play in this instant, then get its type and call the corresponding 'draw()' method
	if(timelineObjects.size()> 0){
		ofBackground(particleSystem_demo.backgroundColor);

		for (int i = 0; i < timelineObjects.size(); i++){
			if(timelineObjects[i].beginning <= currentTime && timelineObjects[i].ending >= currentTime)
				switch(timelineObjects[i].typeOfScene){
				case 0: 
					particleSystem_demo.draw(skeletonVisible);
					break;
				case 1: 
					jointsDraw_demo.draw(skeletonVisible);
					break;
			}
		}
	}
	previewPlayer.end();
	previewPlayer.draw(x + 8 + PLAYER_MARGIN, y + 8 + panelHeight/2 - 25 - previewPlayer.getHeight()/2);
}

void PreviewPlayer::resetDemos(){
	particleSystem_demo.particles.clear();
	jointsDraw_demo.clearBrushes();

	particleSystem_demo.setup(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
	jointsDraw_demo.setup(0, 0, previewPlayer.getWidth(), previewPlayer.getHeight());
}

void PreviewPlayer::windowResized(int panelWidth){
	previewPlayer.allocate(panelWidth - (PLAYER_MARGIN * 2) - 16, (((panelWidth - (PLAYER_MARGIN * 2) - 16)*9)/16), GL_RGB32F_ARB);
	cout << "Preview Player: " << previewPlayer.getWidth() << " x " << previewPlayer.getHeight() << endl;

	particleSystem_demo.windowResized(ofGetWidth() / 2 + 15  + 8 + PLAYER_MARGIN, 30 + 8, previewPlayer.getWidth(), previewPlayer.getHeight());
	jointsDraw_demo.windowResized(ofGetWidth() / 2 + 15  + 8 + PLAYER_MARGIN, 30 + 8, previewPlayer.getWidth(), previewPlayer.getHeight());

	
}

void PreviewPlayer::updateTimelineObjects(deque<TimelineGraphicalObject> timelineObjs){
	timelineObjects = timelineObjs;
}