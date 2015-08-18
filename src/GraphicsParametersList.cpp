#include "GraphicsParametersList.h"

const float itemHeight = 20;
string timestampSelected;

void GraphicsParametersList::setup(int sceneType, float beginning, float ending){
	typeOfScene = sceneType;

	//Set GUI for drop down list
	ddl_gui = new ofxUICanvas();	
    ddl_gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	ddl_gui->setPosition(18 + 10, 18 + 30);
	ddl_gui->addLabel("TIMESTAMPS LIST:", OFX_UI_FONT_SMALL);
	ddl_gui->addLabel("");
	
	ddl = ddl_gui->addDropDownList("Click to select", timestamps);
    ddl->setAllowMultiple(false);
    ddl->setAutoClose(true);
	ddl->setShowCurrentSelected(true); 

    ddl_gui->autoSizeToFitWidgets(); 
	ofAddListener(ddl_gui->newGUIEvent, this, &GraphicsParametersList::guiEvent);

	timestampSelected = "";
	canAddTimestamp = true;
}

void GraphicsParametersList::update(bool isSelected, float beginning, float ending, bool showScenesPalette, bool showSoundsPanel){
	selected = isSelected;
	
	showSelectedParametersGUI(showScenesPalette, showSoundsPanel);
	if(!showScenesPalette && !showSoundsPanel){
		ddl_gui->setVisible(selected);
	}else{
		ddl_gui->setVisible(false);
	}
	//Update timestamps vector (for DDL) according to the values in the parameters vector
	if(beginning != parameters[0][0] || ending != parameters[parameters.size() - 1][0]){
		printf("\nUpdating DDL ...\n\n");
		
		ddl->clearToggles();
		
		//if(beginning != parameters[0][0]){
			parameters[0][0] = beginning;
			ostringstream buffer1; 
			buffer1 << parameters[0][0]; 
			timestamps[0] = buffer1.str() + " s (Beginning)";
			printf("Updated Beginning DDL item ! \n");
		//}

		if(ending != parameters[parameters.size()-1][0]){
			parameters[parameters.size()-1][0] = ending;
			ostringstream buffer2; 
			buffer2 << parameters[parameters.size()-1][0]; 
			timestamps[timestamps.size()-1] = buffer2.str() + " s (Ending)";
		}

		if(parameters.size() > 2)
			for (int i = 1; i < parameters.size() - 1; i++){
				ostringstream buff; 
				buff << parameters[i][0]; 
				timestamps[i] = buff.str() + " s";
			}
		
		for(int i = 0; i<timestamps.size();i++)
			ddl->addToggle(timestamps[i]);
	}
}

void GraphicsParametersList::draw(float maxTime){
	
}

//------------------------------------------------
void GraphicsParametersList::addTimestamp(float timestamp, float force, float size, float lifeTime, float history, float rotation, float eRad, float bornRate, float velRad, float sizeBrush, float lifeTimeBrush, float speed){
	for(int i = 0; i < parameters.size(); i++){
		if(parameters[i][0] == timestamp)
			canAddTimestamp = false;
	}

	if(canAddTimestamp){
		switch(typeOfScene){
		case 0:
			parameters.push_back(newTimestamp_ParticleSystem(timestamp, force, size, lifeTime, history, rotation, eRad, bornRate, velRad));
			//guis.push_back(createParametersGUI(parameters.size() - 1));
			break;
		case 1:
			parameters.push_back(newTimestamp_JointsDraw(timestamp, sizeBrush, lifeTimeBrush, speed));
			//guis.push_back(createParametersGUI(parameters.size() - 1));
			break;
		}
		ostringstream buff; 
		buff << timestamp; 
		timestamps.push_back(buff.str() + " s");

		parameters = selectionSort(parameters);
		
		//Recreate GUIS so that they correctly point to the corresponding timestamp
		guis.clear();
		for(int i = 0; i < parameters.size(); i++)
			guis.push_back(createParametersGUI(i));

		ddl->clearToggles();
		for(int i = 0; i<timestamps.size();i++)
			ddl->addToggle(timestamps[i]);
		ddl->open();
	}
	
	canAddTimestamp = true;
}

vector<float> GraphicsParametersList::newTimestamp_ParticleSystem(float timestamp, float force, float size, float lifeTime, float history, float rotation, float eRad, float bornRate, float velRad){
	vector<float> newTimestamp (9);
	newTimestamp[0] = timestamp;
	newTimestamp[1] = force;
	newTimestamp[2] = size;
	newTimestamp[3] = lifeTime;
	newTimestamp[4] = history;
	newTimestamp[5] = rotation;
	newTimestamp[6] = eRad;
	newTimestamp[7] = bornRate;
	newTimestamp[8] = velRad;


	return newTimestamp;
}

vector<float> GraphicsParametersList::newTimestamp_JointsDraw(float timestamp, float size, float lifeTime, float speed){
	vector<float> newTimestamp (4);
	newTimestamp[0] = timestamp;
	newTimestamp[1] = size;
	newTimestamp[2] = lifeTime;
	newTimestamp[3] = speed;

	return newTimestamp;
}

ofxUICanvas* GraphicsParametersList::createParametersGUI(int index){
	gui = new ofxUICanvas();
    gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui->setPosition(18 + 10 + 220, 18 + 30);
	gui->setVisible(false);

	cout << "\nSetting up sliders for parameters[" << index << "][]\n" << endl;

	ostringstream buff;
	buff << parameters[index][0];

	switch(typeOfScene){
	case 0:
		gui->addLabel("PARTICLES SYSTEM");
		gui->addSpacer();
		//gui->addLabel("Timestamp: " + buff.str() + " s", OFX_UI_FONT_SMALL);
		gui->addLabel("");

		gui->addLabel("PARTICLES:");
		gui->addSlider("Attraction Force", 0.0, 0.5, &parameters[index][1])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Size", 0.0, 30.0, &parameters[index][2])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Life Time", 0.0, 120.0, &parameters[index][3])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Motion Blur", 0.0, 1.0, &parameters[index][4])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Rotation", -500, 500, &parameters[index][5])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addLabel("");

		gui->addLabel("EMITTER:");
		gui->addSlider("Radius", 0.0, 500.0, &parameters[index][6])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Particles Rate", 0.0, 500.0, &parameters[index][7])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Initial Velocity", 0.0, 400.0, &parameters[index][8])->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	
	case 1:
		gui->addLabel("JOINTS DRAW");
		gui->addSpacer();
		//gui->addLabel("Timestamp: " + buff.str() + " s", OFX_UI_FONT_SMALL);
		gui->addLabel("");

		gui->addLabel("BRUSH:");
		gui->addSlider("Size", 0.0, 100.0, &parameters[index][1])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Trail", 0.0, 1.0, &parameters[index][2])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addSlider("Drawing Speed", 0, 10, &parameters[index][3])->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui->addLabel("");
		break;
	}
	
	gui->autoSizeToFitWidgets(); 
	ofAddListener(gui->newGUIEvent, this, &GraphicsParametersList::guiEvent); 
	return gui;
}


void GraphicsParametersList::showSelectedParametersGUI(bool showScenesPalette, bool showSoundsPanel){
	if(!showScenesPalette && !showSoundsPanel){
		for(int i = 0; i < guis.size(); i++)
			guis[i]->setVisible(false);
		
		ostringstream buff;
		for(int i = 0; i < parameters.size(); i++){
			buff << parameters[i][0];
			if(buff.str() + " s" == timestampSelected || buff.str() + " s (Beginning)" == timestampSelected|| buff.str() + " s (Ending)" == timestampSelected){
				guis[i]->setVisible(selected);
			}
			//else
			//	guis[i]->setVisible(false);
		
			buff.str("");
			buff.clear();
		}
	}
	else
		for(int i = 0; i < guis.size(); i++)
			guis[i]->setVisible(false);
}

void GraphicsParametersList::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
 
    if(name == "Click to select")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selectedItem = ddlist->getSelected(); 
		for(int i = 0; i < selectedItem.size(); i++){
			timestampSelected = selectedItem[i]->getName();
			cout << "TIMESTAMP SELECTED: " << timestampSelected << endl; 
		}
	}
}

void GraphicsParametersList::deleteTimestamp(){
	ostringstream buff;
	for(int i = 0; i < parameters.size(); i++){
		buff << parameters[i][0];
		if(buff.str() + " s" == timestampSelected){
			parameters.erase(parameters.begin() + i);
			guis[i]->setVisible(false);
			guis.erase(guis.begin() + i);
			ddl->removeToggle(timestamps[i]);
			timestamps.erase(timestamps.begin() + i);
			ddl->open();
		}
		buff.str("");
		buff.clear();
	}
}


void GraphicsParametersList::exit()
{
    delete ddl_gui; 
	for(int i = 0; i < guis.size(); i++)
		delete guis[i];
}
//------------------------------------------------

void GraphicsParametersList::mouseDragged(int x, int y){

}

void GraphicsParametersList::mousePressed(int x, int y){

}

void GraphicsParametersList::mouseReleased(int x, int y, float beginning, float ending){
	if(beginning != parameters[0][0])
		guis[0] = createParametersGUI(0);
	if(ending != parameters[parameters.size()-1][0])
		guis[guis.size()-1] = createParametersGUI(parameters.size()-1);
	

	//Print parameters vector (for debugging)
	ostringstream buff;
	for(int i = 0; i < parameters.size(); i++){
		printf("\n___________________\n");
		cout << "[" << i << "]" << endl;
		for(int j = 0; j < parameters[i].size(); j++){
			buff << parameters[i][j];
			cout << buff.str() << endl;
			buff.str("");
			buff.clear();
		}
		printf("___________________\n");
	}
	printf("___________________\n");
	cout << "\n guis.size() = " << guis.size() << "\n\n";
}

void GraphicsParametersList::mouseMoved(int x, int y ){

}

void GraphicsParametersList::windowResized(int w, int h){

}

void GraphicsParametersList::pasteSettings(){
	ostringstream buff;
	switch(typeOfScene){
	case 0:	//Particle System
		printf("Paste settings for Particle System scene!\n");

		for(int i = 0; i < parameters.size(); i++){
			buff << parameters[i][0];
			if(buff.str() + " s" == timestampSelected || buff.str() + " s (Beginning)" == timestampSelected|| buff.str() + " s (Ending)" == timestampSelected){
				guis[i]->loadSettings("particleSystem_clipboard.xml");
			}
			buff.str("");
			buff.clear();
		}
		break;
	case 1:	//Joints Draw
		printf("Paste settings for Joints Draw scene!\n");

		for(int i = 0; i < parameters.size(); i++){
			buff << parameters[i][0];
			if(buff.str() + " s" == timestampSelected || buff.str() + " s (Beginning)" == timestampSelected|| buff.str() + " s (Ending)" == timestampSelected){
				guis[i]->loadSettings("jointsDraw_clipboard.xml");
			}
			buff.str("");
			buff.clear();
		}
		break;
	}
}

vector<vector<float>> GraphicsParametersList::selectionSort(vector<vector<float>> parameters){
	vector<vector<float>> sortedParameters = parameters;
	
	int i,j;
	int iMin;

	for (j = 0; j < sortedParameters.size()-1; j++) {
		iMin = j;
		for ( i = j+1; i < sortedParameters.size(); i++) {
			if (sortedParameters[i][0] < sortedParameters[iMin][0]) {
				iMin = i;
			}
		}
		if(iMin != j) {
			swap(sortedParameters[j], sortedParameters[iMin]);
			//Consequently change GUI and timestamps vectors order
			//swap(guis[j], guis[iMin]);
			swap(timestamps[j], timestamps[iMin]);	
		}
	}
	return sortedParameters;
}