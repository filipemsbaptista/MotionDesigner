#include "AudioParametersList.h"

string selectedTimestamp;

void AudioParametersList::setup(float beginning, float ending){
	printf(" > Setting up GUI for drop down list...\n");
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
	ofAddListener(ddl_gui->newGUIEvent, this, &AudioParametersList::guiEvent);

	selectedTimestamp = "";
	canAddTimestamp = true;
}

void AudioParametersList::update(bool isSelected, float beginning, float ending, bool showScenesPalette, bool showSoundsPanel){
	selected = isSelected;
	showSelectedParametersGUI(showScenesPalette, showSoundsPanel);
	if(!showScenesPalette && !showSoundsPanel){
		ddl_gui->setVisible(selected);
	}else{
		ddl_gui->setVisible(false);
	}
	//Update timestamps vector (for DDL) according to the values in the parameters vector
	if(beginning != parameters[0][0] || ending != parameters[parameters.size()-1][0]){
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


//------------------------------------------------
void AudioParametersList::addTimestamp(float timestamp, float speedJoint, float speedRef, float volumeJoint, float volumeRef, float panningJoint, float panningRef){
	for(int i = 0; i < parameters.size(); i++){
		if(parameters[i][0] == timestamp)
			canAddTimestamp = false;
	}

	if(canAddTimestamp){
		parameters.push_back(newTimestamp(timestamp, speedJoint, speedRef, volumeJoint, volumeRef, panningJoint, panningRef));
		guis.push_back(createParametersGUI(parameters.size() - 1));
		
		ostringstream buff; 
		buff << timestamp; 
		timestamps.push_back(buff.str() + " s");
		
		parameters = selectionSort(parameters);
		
		ddl->clearToggles();
		for(int i = 0; i<timestamps.size();i++)
			ddl->addToggle(timestamps[i]);
		ddl->open();
	}
	
	canAddTimestamp = true;
}

vector<float> AudioParametersList::newTimestamp(float timestamp, float speedJoint, float speedRef, float volumeJoint, float volumeRef, float panningJoint, float panningRef){
	vector<float> newTimestamp (7);
	newTimestamp[0] = timestamp;
	newTimestamp[1] = speedJoint;
	newTimestamp[2] = speedRef;
	newTimestamp[3] = volumeJoint;
	newTimestamp[4] = volumeRef;
	newTimestamp[5] = panningJoint;
	newTimestamp[6] = panningRef;

	return newTimestamp;
}

ofxUICanvas* AudioParametersList::createParametersGUI(int index){
	gui = new ofxUICanvas();
    gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui->setPosition(18 + 10 + 220, 18 + 30);
	gui->setDrawWidgetPadding(false);
	gui->setVisible(false);

	cout << "\nSetting up sliders for parameters[" << index << "][]\n" << endl;

	ostringstream buff;
	buff << parameters[index][0];

	gui->addLabel("SOUND CONTROL");
	gui->addSpacer();
	gui->addLabel("");

	controllers.push_back("X-axis");
	controllers.push_back("Y-axis");
	controllers.push_back("Distance to Marker");
	controllers.push_back("Distance to Mouse");

	joints.push_back("Head");
	joints.push_back("Neck");
	joints.push_back("Left Shoulder");
	joints.push_back("Right Shoulder");
	joints.push_back("Left Elbow");
	joints.push_back("Right Elbow");
	joints.push_back("Left Hand");
	joints.push_back("Right Hand");
	joints.push_back("Torso");
	joints.push_back("Left Hip");
	joints.push_back("Right Hip");
	joints.push_back("Left Knee");
	joints.push_back("Right Knee");
	joints.push_back("Left Foot");
	joints.push_back("Right Foot");
	
	gui->addLabel("SPEED");
	gui->addLabel("Joint:", OFX_UI_FONT_SMALL);
	ddl_joints_speed = gui->addDropDownList("Select joint for speed", joints);
	ddl_joints_speed->setAllowMultiple(false);
    ddl_joints_speed->setAutoClose(true);
	ddl_joints_speed->setShowCurrentSelected(true);
	gui->addLabel("Controller:", OFX_UI_FONT_SMALL);
	ddl_speed = gui->addDropDownList("Select speed controller", controllers);
	ddl_speed->setAllowMultiple(false);
    ddl_speed->setAutoClose(true);
	ddl_speed->setShowCurrentSelected(true);
	gui->addLabel("");

	gui->addLabel("VOLUME");
	gui->addLabel("Joint:", OFX_UI_FONT_SMALL);
	ddl_joints_volume = gui->addDropDownList("Select joint for volume", joints);
	ddl_joints_volume->setAllowMultiple(false);
    ddl_joints_volume->setAutoClose(true);
	ddl_joints_volume->setShowCurrentSelected(true);
	gui->addLabel("Controller:", OFX_UI_FONT_SMALL);
	ddl_volume = gui->addDropDownList("Select volume controller", controllers);
	ddl_volume->setAllowMultiple(false);
    ddl_volume->setAutoClose(true);
	ddl_volume->setShowCurrentSelected(true);
	gui->addLabel("");

	gui->addLabel("PANNING");
	gui->addLabel("Joint:", OFX_UI_FONT_SMALL);
	ddl_joints_pan = gui->addDropDownList("Select joint for panning", joints);
	ddl_joints_pan->setAllowMultiple(false);
    ddl_joints_pan->setAutoClose(true);
	ddl_joints_pan->setShowCurrentSelected(true);
	gui->addLabel("Controller:", OFX_UI_FONT_SMALL);
	ddl_pan = gui->addDropDownList("Select panning controller", controllers);
	ddl_pan->setAllowMultiple(false);
    ddl_pan->setAutoClose(true);
	ddl_pan->setShowCurrentSelected(true);
    
	gui->autoSizeToFitWidgets(); 
	ofAddListener(gui->newGUIEvent, this, &AudioParametersList::guiEvent); 
	return gui;
}

void AudioParametersList::showSelectedParametersGUI(bool showScenesPalette, bool showSoundsPanel){
	if(!showScenesPalette && !showSoundsPanel){
		ostringstream buff;
		for(int i = 0; i < parameters.size(); i++){
			buff << parameters[i][0];
			if(buff.str() + " s" == selectedTimestamp || buff.str() + " s (Beginning)" == selectedTimestamp|| buff.str() + " s (Ending)" == selectedTimestamp){
				guis[i]->setVisible(selected);
			}
			else
				guis[i]->setVisible(false);
		
			buff.str("");
			buff.clear();
		}
	}
	else
		for(int i = 0; i < guis.size(); i++)
			guis[i]->setVisible(false);
}

void AudioParametersList::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
 
    if(name == "Click to select")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selectedItem = ddlist->getSelected(); 
		for(int i = 0; i < selectedItem.size(); i++){
			selectedTimestamp = selectedItem[i]->getName();
			cout << "TIMESTAMP SELECTED: " << selectedTimestamp << endl; 
		}
	}
	else
	{
		if(name == "Select speed controller")
		{
			ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
			vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
			for(int i = 0; i < selected.size(); i++){
				cout << "SPEED CONTROL: " << selected[i]->getName() << endl;
			
				if(selected[i]->getName() == "X-axis")
					trackingReference_Speed = 0;
				else
					if(selected[i]->getName() == "Y-axis")
						trackingReference_Speed = 1;
					else
						if(selected[i]->getName() == "Distance to Marker")
							trackingReference_Speed = 2;
						else
							trackingReference_Speed = 3;
			}
		}
		else
			if(name == "Select volume controller")
			{
				ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
				vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
				for(int i = 0; i < selected.size(); i++){
					cout << "VOLUME CONTROL: " << selected[i]->getName() << endl;
			
					if(selected[i]->getName() == "X-axis")
						trackingReference_Volume = 0;
					else
						if(selected[i]->getName() == "Y-axis")
							trackingReference_Volume = 1;
						else
							if(selected[i]->getName() == "Distance to Marker")
								trackingReference_Volume = 2;
							else
								trackingReference_Volume = 3;
				}
			}
			else
				if(name == "Select pan controller")
				{
					ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
					vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
					for(int i = 0; i < selected.size(); i++){
						cout << "PAN CONTROL: " << selected[i]->getName() << endl;
			
						if(selected[i]->getName() == "X-axis")
							trackingReference_Pan = 0;
						else
							if(selected[i]->getName() == "Y-axis")
								trackingReference_Pan = 1;
							else
								if(selected[i]->getName() == "Distance to Marker")
									trackingReference_Pan = 2;
								else
									trackingReference_Pan = 3;
					}
				}
				else
					if(name == "Select joint for speed"){
						ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
						vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
						for(int i = 0; i < selected.size(); i++){
							cout << "SPEED JOINT: " << selected[i]->getName() << endl;
			
							if(selected[i]->getName() == "Head")
								joint_Speed = 0;
							else
								if(selected[i]->getName() == "Neck")
									joint_Speed = 1;
								else
									if(selected[i]->getName() == "Left Shoulder")
										joint_Speed = 2;
									else
										if(selected[i]->getName() == "Right Shoulder")
											joint_Speed = 3;
										else
											if(selected[i]->getName() == "Left Elbow")
												joint_Speed = 4;
											else
												if(selected[i]->getName() == "Right Elbow")
													joint_Speed = 5;
												else
													if(selected[i]->getName() == "Left Hand")
														joint_Speed = 6;
													else
														if(selected[i]->getName() == "Right Hand")
															joint_Speed = 7;
														else
															if(selected[i]->getName() == "Torso")
																joint_Speed = 8;
															else
																if(selected[i]->getName() == "Left Hip")
																	joint_Speed = 9;
																else
																	if(selected[i]->getName() == "Right Hip")
																		joint_Speed = 10;
																	else
																		if(selected[i]->getName() == "Left Knee")
																			joint_Speed = 11;
																		else
																			if(selected[i]->getName() == "Right Knee")
																				joint_Speed = 12;
																			else
																				if(selected[i]->getName() == "Left Foot")
																					joint_Speed = 13;
																				else
																					if(selected[i]->getName() == "Right Foot")
																						joint_Speed = 14;
						}
					} else
						if(name == "Select joint for volume"){
							ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
							vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
							for(int i = 0; i < selected.size(); i++){
								cout << "VOLUME JOINT: " << selected[i]->getName() << endl;
			
								if(selected[i]->getName() == "Head")
									joint_Volume = 0;
								else
									if(selected[i]->getName() == "Neck")
										joint_Volume = 1;
									else
										if(selected[i]->getName() == "Left Shoulder")
											joint_Volume = 2;
										else
											if(selected[i]->getName() == "Right Shoulder")
												joint_Volume = 3;
											else
												if(selected[i]->getName() == "Left Elbow")
													joint_Volume = 4;
												else
													if(selected[i]->getName() == "Right Elbow")
														joint_Volume = 5;
													else
														if(selected[i]->getName() == "Left Hand")
															joint_Volume = 6;
														else
															if(selected[i]->getName() == "Right Hand")
																joint_Volume = 7;
															else
																if(selected[i]->getName() == "Torso")
																	joint_Volume = 8;
																else
																	if(selected[i]->getName() == "Left Hip")
																		joint_Volume = 9;
																	else
																		if(selected[i]->getName() == "Right Hip")
																			joint_Volume = 10;
																		else
																			if(selected[i]->getName() == "Left Knee")
																				joint_Volume = 11;
																			else
																				if(selected[i]->getName() == "Right Knee")
																					joint_Volume = 12;
																				else
																					if(selected[i]->getName() == "Left Foot")
																						joint_Volume = 13;
																					else
																						if(selected[i]->getName() == "Right Foot")
																							joint_Volume = 14;
							}
						} else
							if(name == "Select joint for panning"){
								ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
								vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
								for(int i = 0; i < selected.size(); i++){
									cout << "PANNING JOINT: " << selected[i]->getName() << endl;
			
									if(selected[i]->getName() == "Head")
										joint_Pan = 0;
									else
										if(selected[i]->getName() == "Neck")
											joint_Pan = 1;
										else
											if(selected[i]->getName() == "Left Shoulder")
												joint_Pan = 2;
											else
												if(selected[i]->getName() == "Right Shoulder")
													joint_Pan = 3;
												else
													if(selected[i]->getName() == "Left Elbow")
														joint_Pan = 4;
													else
														if(selected[i]->getName() == "Right Elbow")
															joint_Pan = 5;
														else
															if(selected[i]->getName() == "Left Hand")
																joint_Pan = 6;
															else
																if(selected[i]->getName() == "Right Hand")
																	joint_Pan = 7;
																else
																	if(selected[i]->getName() == "Torso")
																		joint_Pan = 8;
																	else
																		if(selected[i]->getName() == "Left Hip")
																			joint_Pan = 9;
																		else
																			if(selected[i]->getName() == "Right Hip")
																				joint_Pan = 10;
																			else
																				if(selected[i]->getName() == "Left Knee")
																					joint_Pan = 11;
																				else
																					if(selected[i]->getName() == "Right Knee")
																						joint_Pan = 12;
																					else
																						if(selected[i]->getName() == "Left Foot")
																							joint_Pan = 13;
																						else
																							if(selected[i]->getName() == "Right Foot")
																								joint_Pan = 14;
								}
							}

	}
}

void AudioParametersList::deleteTimestamp(){
	ostringstream buff;
	for(int i = 0; i < parameters.size(); i++){
		buff << parameters[i][0];
		if(buff.str() + " s" == selectedTimestamp){
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


void AudioParametersList::exit()
{
    delete ddl_gui; 
	for(int i = 0; i < guis.size(); i++)
		delete guis[i];
}
//------------------------------------------------

void AudioParametersList::mouseReleased(int x, int y, float beginning, float ending){
	if(beginning != parameters[0][0])
		guis[0] = createParametersGUI(0);
	if(ending != parameters[parameters.size() - 1][0])
		guis[guis.size()-1] = createParametersGUI(parameters.size() - 1);
	

	//Print parameters vector (for debugging)
	ostringstream buff;
	for(int i = 0; i < parameters.size(); i++){
		printf("\n____	AUDIO	____\n");
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
}

void AudioParametersList::pasteSettings(){
	ostringstream buff;
	
	printf("Paste settings for Interactive Audio scene!\n");

	for(int i = 0; i < parameters.size(); i++){
		buff << parameters[i][0];
		if(buff.str() + " s" == selectedTimestamp || buff.str() + " s (Beginning)" == selectedTimestamp || buff.str() + " s (Ending)" == selectedTimestamp){
			guis[i]->loadSettings("interactiveAudio_clipboard.xml");
		}
		buff.str("");
		buff.clear();
	}
}

vector<vector<float>> AudioParametersList::selectionSort(vector<vector<float>> parameters){
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
			swap(guis[j], guis[iMin]);
			swap(timestamps[j], timestamps[iMin]);
		}
	}
	return sortedParameters;
}