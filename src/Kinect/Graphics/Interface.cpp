#include "Interface.h"

void Interface::setup(int typeOfScene, bool isExplore){
	sceneType = typeOfScene;
	exploreVersion = isExplore;

	if(exploreVersion)
			exploring = true;


	switch(sceneType){
	case 0:		//Particle System
		/*
		gui1->loadSettings("gui1Settings.xml");
		gui2->loadSettings("gui2Settings.xml");
		gui3->loadSettings("gui3Settings.xml");	
		*/
		guiInfo->loadSettings("guiInfoSettings.xml");
		guiFPS->loadSettings("guiFPSSettings.xml");
		gui_Head->loadSettings("gui_HeadSettings.xml");
		gui_Neck->loadSettings("gui_NeckSettings.xml");
		gui_ShoulderL->loadSettings("gui_ShoulderLSettings.xml");     
		gui_ShoulderR->loadSettings("gui_ShoulderRSettings.xml"); 
		gui_ElbowL->loadSettings("gui_ElbowLSettings.xml");     
		gui_ElbowR->loadSettings("gui_ElbowRSettings.xml"); 
		gui_HandL->loadSettings("gui_HandLSettings.xml");     
		gui_HandR->loadSettings("gui_HandRSettings.xml"); 
		gui_Torso->loadSettings("gui_TorsoSettings.xml");     
		gui_HipL->loadSettings("gui_HipLSettings.xml"); 
		gui_HipR->loadSettings("gui_HipRSettings.xml");     
		gui_KneeL->loadSettings("gui_KneeLSettings.xml"); 
		gui_KneeR->loadSettings("gui_KneeRSettings.xml");     
		gui_FootL->loadSettings("gui_FootLSettings.xml"); 
		gui_FootR->loadSettings("gui_FootRSettings.xml"); 
	
		jointsVisible = true;
		break;
	case 1:		//Joints Draw
		guiInfo->loadSettings("guiInfoSettings.xml");
		guiFPS->loadSettings("guiFPSSettings.xml");
		gui_Head->loadSettings("gui_HeadSettings.xml");
		gui_Neck->loadSettings("gui_NeckSettings.xml");
		gui_ShoulderL->loadSettings("gui_ShoulderLSettings.xml");     
		gui_ShoulderR->loadSettings("gui_ShoulderRSettings.xml"); 
		gui_ElbowL->loadSettings("gui_ElbowLSettings.xml");     
		gui_ElbowR->loadSettings("gui_ElbowRSettings.xml"); 
		gui_HandL->loadSettings("gui_HandLSettings.xml");     
		gui_HandR->loadSettings("gui_HandRSettings.xml"); 
		gui_Torso->loadSettings("gui_TorsoSettings.xml");     
		gui_HipL->loadSettings("gui_HipLSettings.xml"); 
		gui_HipR->loadSettings("gui_HipRSettings.xml");     
		gui_KneeL->loadSettings("gui_KneeLSettings.xml"); 
		gui_KneeR->loadSettings("gui_KneeRSettings.xml");     
		gui_FootL->loadSettings("gui_FootLSettings.xml"); 
		gui_FootR->loadSettings("gui_FootRSettings.xml"); 
	
		jointsVisible = true;
		break;
	}
	
}

void Interface::update(int jointSelected){
	switch(sceneType){
	case 0:		//Particle System
		selectedJoint = jointSelected;
		showJointPanel(jointsVisible);
		break;
	case 1:		//Joints Draw
		selectedJoint = jointSelected;
		showJointPanel(jointsVisible);
		break;
	}
}

void Interface::draw(){

}
//------------------------------------
void Interface::setGUI1(float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity){
	gui1 = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui1->setDrawWidgetPadding(true);
	gui1->setPosition(5, 5);
	
	//Add widgets
	gui1->addSpacer();
    gui1->addLabel("Press 'ENTER' to Hide GUIs", OFX_UI_FONT_SMALL);
	gui1->addLabel("Press 'r' to reset GUI position", OFX_UI_FONT_SMALL);

	gui1->addLabel("");
	gui1->addLabel("PARTICLES");
	
	sP.force = force;
	sP.size_PS = size;
	sP.lifeTime_PS = lifeTime;
	sP.history = history;
	sP.rotate = rotate;
	sP.eRad = eRad;
	sP.bornRate = bornRate;
	sP.velRad = velRad;
	sP.Zintesity = Zintensity;
	
	gui1->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addLabel("");
	gui1->addSlider("Z Intesity", 0, 5, *sP.Zintesity)->setTriggerType(OFX_UI_TRIGGER_ALL);

	gui1->addLabel("");
	gui1->addLabel("");

    gui1->addLabel("EMITTER");
	gui1->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addLabel("");
	gui1->addLabel("");

    gui1->addLabelButton("COPY SETTINGS", false);
	gui1->addLabel("");
	if(exploreVersion)
		gui1->addLabelButton("RETURN TO EDITING", false);

	gui1->autoSizeToFitWidgets(); 
	ofAddListener(gui1->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI2(){
	gui2 = new ofxUISuperCanvas("SHORTCUT KEYS:");		//Creates a canvas at (0,0) using the default width	
	gui2->setDrawWidgetPadding(true);
	gui2->setPosition(5, ofGetHeight() - 170 - 5);

	gui2->addSpacer();
	gui2->addLabel("CTRL - Tracking On/Off", OFX_UI_FONT_SMALL);
	gui2->addLabel("",1);
	string textString = "SPACE - Randomly reset particles position\n";
	gui2->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
		gui2->addLabel("",1);
	gui2->addLabel("H - Show skeletonr", OFX_UI_FONT_SMALL);
	gui2->addLabel("",1);
	gui2->addLabel("F1 - Printscreen", OFX_UI_FONT_SMALL);

	gui2->autoSizeToFitWidgets(); 
	ofAddListener(gui2->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI3(){
	gui3 = new ofxUISuperCanvas("");		//Creates a canvas at (0,0) using the default width	
	gui3->setDrawWidgetPadding(true);
	gui3->setPosition(ofGetWidth() - gui3->getGlobalCanvasWidth() - 5, 5);

	gui3->addSpacer();
    gui3->addFPS();

	gui3->autoSizeToFitWidgets(); 
	ofAddListener(gui3->newGUIEvent, this, &Interface::guiEvent); 
}
//------------------------------------
void Interface::setGUI_Head(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_Head = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_Head->setDrawWidgetPadding(true);
	gui_Head->setPosition(5, 5);
	gui_Head->setVisible(true);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_Head->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_Head->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_Head->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_Head->addLabel("");

	gui_Head->addLabel("1. HEAD:");
	gui_Head->addLabel("");

	gui_Head->addToggle(" ACTIVE", isActive_Head);
	gui_Head->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_Head->addLabel("PARTICLES");
		gui_Head->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);

		gui_Head->addLabel("");
		gui_Head->addLabel("");

		gui_Head->addLabel("EMITTER");
		gui_Head->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_Head->addLabel("BRUSH");
		gui_Head->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Head->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_Head->addLabel("");
	gui_Head->addLabel("");
    gui_Head->addLabelButton("COPY SETTINGS", false);
	gui_Head->addLabel("");
	if(exploreVersion)
		gui_Head->addLabelButton("RETURN TO EDITING", false);

	gui_Head->autoSizeToFitWidgets(); 
	ofAddListener(gui_Head->newGUIEvent,	 this, &Interface::guiEvent); 
}

void Interface::setGUI_Neck(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_Neck = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_Neck->setDrawWidgetPadding(true);
	gui_Neck->setPosition(5, 5);
	gui_Neck->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_Neck->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_Neck->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_Neck->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_Neck->addLabel("");

	gui_Neck->addLabel("2. NECK:");
	gui_Neck->addLabel("");

	gui_Neck->addToggle(" ACTIVE", isActive_Neck);
	gui_Neck->addLabel("");


	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_Neck->addLabel("PARTICLES");
		gui_Neck->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);

		gui_Neck->addLabel("");
		gui_Neck->addLabel("");

		gui_Neck->addLabel("EMITTER");
		gui_Neck->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_Neck->addLabel("BRUSH");
		gui_Neck->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Neck->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_Neck->addLabel("");
	gui_Neck->addLabel("");
    gui_Neck->addLabelButton("COPY SETTINGS", false);
	gui_Neck->addLabel("");
	if(exploreVersion)
		gui_Neck->addLabelButton("RETURN TO EDITING", false);

	gui_Neck->autoSizeToFitWidgets(); 
	ofAddListener(gui_Neck->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_ShoulderL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_ShoulderL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_ShoulderL->setDrawWidgetPadding(true);
	gui_ShoulderL->setPosition(5, 5);
	gui_ShoulderL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_ShoulderL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_ShoulderL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_ShoulderL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_ShoulderL->addLabel("");

	gui_ShoulderL->addLabel("3. LEFT SHOULDER:");
	gui_ShoulderL->addLabel("");

	gui_ShoulderL->addToggle(" ACTIVE", isActive_ShoulderL);
	gui_ShoulderL->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_ShoulderL->addLabel("PARTICLES");
		gui_ShoulderL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);

		gui_ShoulderL->addLabel("");
		gui_ShoulderL->addLabel("");

		gui_ShoulderL->addLabel("EMITTER");
		gui_ShoulderL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_ShoulderL->addLabel("BRUSH");
		gui_ShoulderL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_ShoulderL->addLabel("");
	gui_ShoulderL->addLabel("");
    gui_ShoulderL->addLabelButton("COPY SETTINGS", false);
	gui_ShoulderL->addLabel("");
	if(exploreVersion)
		gui_ShoulderL->addLabelButton("RETURN TO EDITING", false);

	gui_ShoulderL->autoSizeToFitWidgets(); 
	ofAddListener(gui_ShoulderL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_ShoulderR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_ShoulderR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_ShoulderR->setDrawWidgetPadding(true);
	gui_ShoulderR->setPosition(5, 5);
	gui_ShoulderR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_ShoulderR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_ShoulderR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_ShoulderR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_ShoulderR->addLabel("");

	gui_ShoulderR->addLabel("4. RIGHT SHOULDER:");
	gui_ShoulderR->addLabel("");

	gui_ShoulderR->addToggle(" ACTIVE", isActive_ShoulderR);
	gui_ShoulderR->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_ShoulderR->addLabel("PARTICLES");
		gui_ShoulderR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addLabel("");
		gui_ShoulderR->addLabel("");
		gui_ShoulderR->addLabel("EMITTER");
		gui_ShoulderR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_ShoulderR->addLabel("BRUSH");
		gui_ShoulderR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ShoulderR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_ShoulderR->addLabel("");
	gui_ShoulderR->addLabel("");
    gui_ShoulderR->addLabelButton("COPY SETTINGS", false);
	gui_ShoulderR->addLabel("");
	if(exploreVersion)
		gui_ShoulderR->addLabelButton("RETURN TO EDITING", false);

	gui_ShoulderR->autoSizeToFitWidgets(); 
	ofAddListener(gui_ShoulderR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_ElbowL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_ElbowL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_ElbowL->setDrawWidgetPadding(true);
	gui_ElbowL->setPosition(5, 5);
	gui_ElbowL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_ElbowL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_ElbowL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_ElbowL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_ElbowL->addLabel("");

	gui_ElbowL->addLabel("5. LEFT ELBOW:");
	gui_ElbowL->addLabel("");

	gui_ElbowL->addToggle(" ACTIVE", isActive_ElbowL);
	gui_ElbowL->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_ElbowL->addLabel("PARTICLES");
		gui_ElbowL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addLabel("");
		gui_ElbowL->addLabel("");
		gui_ElbowL->addLabel("EMITTER");
		gui_ElbowL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_ElbowL->addLabel("BRUSH");
		gui_ElbowL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_ElbowL->addLabel("");
	gui_ElbowL->addLabel("");
    gui_ElbowL->addLabelButton("COPY SETTINGS", false);
	gui_ElbowL->addLabel("");
	if(exploreVersion)
		gui_ElbowL->addLabelButton("RETURN TO EDITING", false);

	gui_ElbowL->autoSizeToFitWidgets(); 
	ofAddListener(gui_ElbowL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_ElbowR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_ElbowR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_ElbowR->setDrawWidgetPadding(true);
	gui_ElbowR->setPosition(5, 5);
	gui_ElbowR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_ElbowR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_ElbowR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_ElbowR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_ElbowR->addLabel("");

	gui_ElbowR->addLabel("6. RIGHT ELBOW:");
	gui_ElbowR->addLabel("");

	gui_ElbowR->addToggle(" ACTIVE", isActive_ElbowR);
	gui_ElbowR->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_ElbowR->addLabel("PARTICLES");
		gui_ElbowR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addLabel("");
		gui_ElbowR->addLabel("");
		gui_ElbowR->addLabel("EMITTER");
		gui_ElbowR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_ElbowR->addLabel("BRUSH");
		gui_ElbowR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_ElbowR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_ElbowR->addLabel("");
	gui_ElbowR->addLabel("");
    gui_ElbowR->addLabelButton("COPY SETTINGS", false);
	gui_ElbowR->addLabel("");
	if(exploreVersion)
		gui_ElbowR->addLabelButton("RETURN TO EDITING", false);

	gui_ElbowR->autoSizeToFitWidgets(); 
	ofAddListener(gui_ElbowR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_HandL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_HandL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_HandL->setDrawWidgetPadding(true);
	gui_HandL->setPosition(5, 5);
	gui_HandL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_HandL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_HandL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_HandL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_HandL->addLabel("");

	gui_HandL->addLabel("7. LEFT HAND:");
	gui_HandL->addLabel("");

	gui_HandL->addToggle(" ACTIVE", isActive_HandL);
	gui_HandL->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_HandL->addLabel("PARTICLES");
		gui_HandL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addLabel("");
		gui_HandL->addLabel("");
		gui_HandL->addLabel("EMITTER");
		gui_HandL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_HandL->addLabel("BRUSH");
		gui_HandL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_HandL->addLabel("");
	gui_HandL->addLabel("");
    gui_HandL->addLabelButton("COPY SETTINGS", false);
	gui_HandL->addLabel("");
	if(exploreVersion)
		gui_HandL->addLabelButton("RETURN TO EDITING", false);

	gui_HandL->autoSizeToFitWidgets(); 
	ofAddListener(gui_HandL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_HandR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_HandR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_HandR->setDrawWidgetPadding(true);
	gui_HandR->setPosition(5, 5);
	gui_HandR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_HandR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_HandR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_HandR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_HandR->addLabel("");

	gui_HandR->addLabel("8. LEFT HAND:");
	gui_HandR->addLabel("");
	
	gui_HandR->addToggle(" ACTIVE", isActive_HandR);
	gui_HandR->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_HandR->addLabel("PARTICLES");
		gui_HandR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addLabel("");
		gui_HandR->addLabel("");
		gui_HandR->addLabel("EMITTER");
		gui_HandR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_HandR->addLabel("BRUSH");
		gui_HandR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HandR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_HandR->addLabel("");
	gui_HandR->addLabel("");
    gui_HandR->addLabelButton("COPY SETTINGS", false);
	gui_HandR->addLabel("");
	if(exploreVersion)
		gui_HandR->addLabelButton("RETURN TO EDITING", false);

	gui_HandR->autoSizeToFitWidgets(); 
	ofAddListener(gui_HandR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_Torso(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_Torso = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_Torso->setDrawWidgetPadding(true);
	gui_Torso->setPosition(5, 5);
	gui_Torso->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_Torso->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_Torso->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_Torso->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_Torso->addLabel("");

	gui_Torso->addLabel("9. TORSO:");
	gui_Torso->addLabel("");

	gui_Torso->addToggle(" ACTIVE", isActive_Torso);
	gui_Torso->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_Torso->addLabel("PARTICLES");
		gui_Torso->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addLabel("");
		gui_Torso->addLabel("");
		gui_Torso->addLabel("EMITTER");
		gui_Torso->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_Torso->addLabel("BRUSH");
		gui_Torso->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_Torso->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_Torso->addLabel("");
	gui_Torso->addLabel("");
    gui_Torso->addLabelButton("COPY SETTINGS", false);
	gui_Torso->addLabel("");
	if(exploreVersion)
		gui_Torso->addLabelButton("RETURN TO EDITING", false);

	gui_Torso->autoSizeToFitWidgets(); 
	ofAddListener(gui_Torso->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_HipL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_HipL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_HipL->setDrawWidgetPadding(true);
	gui_HipL->setPosition(5, 5);
	gui_HipL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_HipL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_HipL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_HipL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_HipL->addLabel("");

	gui_HipL->addLabel("10. LEFT HIP:");
	gui_HipL->addLabel("");

	gui_HipL->addToggle(" ACTIVE", isActive_HipL);
	gui_HipL->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_HipL->addLabel("PARTICLES");
		gui_HipL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addLabel("");
		gui_HipL->addLabel("");
		gui_HipL->addLabel("EMITTER");
		gui_HipL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_HipL->addLabel("BRUSH");
		gui_HipL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_HipL->addLabel("");
	gui_HipL->addLabel("");
    gui_HipL->addLabelButton("COPY SETTINGS", false);
	gui_HipL->addLabel("");
	if(exploreVersion)
		gui_HipL->addLabelButton("RETURN TO EDITING", false);

	gui_HipL->autoSizeToFitWidgets(); 
	ofAddListener(gui_HipL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_HipR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_HipR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_HipR->setDrawWidgetPadding(true);
	gui_HipR->setPosition(5, 5);
	gui_HipR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_HipR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_HipR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_HipR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_HipR->addLabel("");

	gui_HipR->addLabel("11. RIGHT HIP:");
	gui_HipR->addLabel("");

	gui_HipR->addToggle(" ACTIVE", isActive_HipR);
	gui_HipR->addLabel("");

		switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_HipR->addLabel("PARTICLES");
		gui_HipR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addLabel("");
		gui_HipR->addLabel("");
		gui_HipR->addLabel("EMITTER");
		gui_HipR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_HipR->addLabel("BRUSH");
		gui_HipR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_HipR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_HipR->addLabel("");
	gui_HipR->addLabel("");
    gui_HipR->addLabelButton("COPY SETTINGS", false);
	gui_HipR->addLabel("");
	if(exploreVersion)
		gui_HipR->addLabelButton("RETURN TO EDITING", false);

	gui_HipR->autoSizeToFitWidgets(); 
	ofAddListener(gui_HipR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_KneeL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_KneeL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_KneeL->setDrawWidgetPadding(true);
	gui_KneeL->setPosition(5, 5);
	gui_KneeL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_KneeL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_KneeL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_KneeL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_KneeL->addLabel("");

	gui_KneeL->addLabel("12. LEFT KNEE:");
	gui_KneeL->addLabel("");

	gui_KneeL->addToggle(" ACTIVE", isActive_KneeL);
	gui_KneeL->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_KneeL->addLabel("PARTICLES");
		gui_KneeL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addLabel("");
		gui_KneeL->addLabel("");
		gui_KneeL->addLabel("EMITTER");
		gui_KneeL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_KneeL->addLabel("BRUSH");
		gui_KneeL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_KneeL->addLabel("");
	gui_KneeL->addLabel("");
    gui_KneeL->addLabelButton("COPY SETTINGS", false);
	gui_KneeL->addLabel("");
	if(exploreVersion)
		gui_KneeL->addLabelButton("RETURN TO EDITING", false);

	gui_KneeL->autoSizeToFitWidgets(); 
	ofAddListener(gui_KneeL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_KneeR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_KneeR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_KneeR->setDrawWidgetPadding(true);
	gui_KneeR->setPosition(5, 5);
	gui_KneeR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_KneeR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_KneeR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_KneeR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_KneeR->addLabel("");

	gui_KneeR->addLabel("13. RIGHT KNEE:");
	gui_KneeR->addLabel("");

	gui_KneeR->addToggle(" ACTIVE", isActive_KneeR);
	gui_KneeR->addLabel("");
	
	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_KneeR->addLabel("PARTICLES");
		gui_KneeR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addLabel("");
		gui_KneeR->addLabel("");
		gui_KneeR->addLabel("EMITTER");
		gui_KneeR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_KneeR->addLabel("BRUSH");
		gui_KneeR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_KneeR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_KneeR->addLabel("");
	gui_KneeR->addLabel("");
    gui_KneeR->addLabelButton("COPY SETTINGS", false);
	gui_KneeR->addLabel("");
	if(exploreVersion)
		gui_KneeR->addLabelButton("RETURN TO EDITING", false);

	gui_KneeR->autoSizeToFitWidgets(); 
	ofAddListener(gui_KneeR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_FootL(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_FootL = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_FootL->setDrawWidgetPadding(true);
	gui_FootL->setPosition(5, 5);
	gui_FootL->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_FootL->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_FootL->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_FootL->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_FootL->addLabel("");

	gui_FootL->addLabel("14. LEFT FOOT:");
	gui_FootL->addLabel("");

	gui_FootL->addToggle(" ACTIVE", isActive_FootL);
	gui_FootL->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_FootL->addLabel("PARTICLES");
		gui_FootL->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addLabel("");
		gui_FootL->addLabel("");
		gui_FootL->addLabel("EMITTER");
		gui_FootL->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_FootL->addLabel("BRUSH");
		gui_FootL->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootL->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_FootL->addLabel("");
	gui_FootL->addLabel("");
    gui_FootL->addLabelButton("COPY SETTINGS", false);
	gui_FootL->addLabel("");
	if(exploreVersion)
		gui_FootL->addLabelButton("RETURN TO EDITING", false);

	gui_FootL->autoSizeToFitWidgets(); 
	ofAddListener(gui_FootL->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI_FootR(int sceneType, float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity, float *sizeJD, float *lifeTimeJD, float *speedJD){
	gui_FootR = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui_FootR->setDrawWidgetPadding(true);
	gui_FootR->setPosition(5, 5);
	gui_FootR->setVisible(false);		//When showJointPanel() method is called it will assign true if this is the GUI refering the joint selected
	
	//Add widgets
	gui_FootR->addSpacer();
    string textString = " - Double-click to collapse\n";
	gui_FootR->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	string textString2 = " - Drag to reposition\n";
	gui_FootR->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	gui_FootR->addLabel("");

	gui_FootR->addLabel("15. RIGHT FOOT:");
	gui_FootR->addLabel("");

	gui_FootR->addToggle(" ACTIVE", isActive_FootR);
	gui_FootR->addLabel("");

	switch(sceneType){
	case 0:		//Particle System
		sP.force = force;
		sP.size_PS = size;
		sP.lifeTime_PS = lifeTime;
		sP.history = history;
		sP.rotate = rotate;
		sP.eRad = eRad;
		sP.bornRate = bornRate;
		sP.velRad = velRad;
		sP.Zintesity = Zintensity;

		gui_FootR->addLabel("PARTICLES");
		gui_FootR->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Size", 0.0, 30.0, *sP.size_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime_PS)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Motion Blur", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addLabel("");
		gui_FootR->addLabel("");
		gui_FootR->addLabel("EMITTER");
		gui_FootR->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);

		break;
	case 1:		//Joints Draw
		sP_Head.size_JD = sizeJD;
		sP_Head.lifeTime_JD = lifeTimeJD;
		sP_Head.speed = speedJD;
		
		gui_FootR->addLabel("BRUSH");
		gui_FootR->addSlider("Size", 0.0, 100.0, *sP_Head.size_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Trail", 0.0, 1.0, *sP_Head.lifeTime_JD)->setTriggerType(OFX_UI_TRIGGER_ALL);
		gui_FootR->addSlider("Drawing Speed", 0.0, 1.0, *sP_Head.speed)->setTriggerType(OFX_UI_TRIGGER_ALL);
		break;
	}

	gui_FootR->addLabel("");
	gui_FootR->addLabel("");
    gui_FootR->addLabelButton("COPY SETTINGS", false);
	gui_FootR->addLabel("");
	if(exploreVersion)
		gui_FootR->addLabelButton("RETURN TO EDITING", false);

	gui_FootR->autoSizeToFitWidgets(); 
	ofAddListener(gui_FootR->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUIInfo(){
	guiInfo = new ofxUISuperCanvas("INFO:");		//Creates a canvas at (0,0) using the default width	
	guiInfo->setDrawWidgetPadding(true);
	guiInfo->setPosition(5, ofGetHeight() - 200 - 5);

	guiInfo->addSpacer();
	string textString = "Press 'I' to hide/show this panel\n";
	guiInfo->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);

	string textString2 = "SHORTCUT KEYS:\n";
	guiInfo->addTextArea("textarea", textString2, OFX_UI_FONT_SMALL);
	guiInfo->addLabel("",1);
	switch(sceneType){
	case 0:
		guiInfo->addLabel("CTRL - Tracking On/Off", OFX_UI_FONT_SMALL);
		guiInfo->addLabel("",1);
		textString = "SPACE - Randomly reset particles position\n";
		guiInfo->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
		guiInfo->addLabel("",1);
		guiInfo->addLabel("H - Show skeletonr", OFX_UI_FONT_SMALL);
		break;
	case 1:
		guiInfo->addLabel("   ENTER - Hide GUIs", OFX_UI_FONT_SMALL);
		guiInfo->addLabel("",1);
		guiInfo->addLabel("   R - Reset GUI positions", OFX_UI_FONT_SMALL);
		break;
	}

	guiInfo->addLabel("",1);
	guiInfo->addLabel("   F1 - Printscreen", OFX_UI_FONT_SMALL);

	guiInfo->autoSizeToFitWidgets(); 
	ofAddListener(guiInfo->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUIFPS(){
	guiFPS = new ofxUISuperCanvas("");		//Creates a canvas at (0,0) using the default width	
	guiFPS->setDrawWidgetPadding(true);
	guiFPS->setPosition(ofGetWidth() - guiFPS->getGlobalCanvasWidth() - 170, 5);

	guiFPS->addSpacer();
    guiFPS->addFPS();

	guiFPS->autoSizeToFitWidgets(); 
	ofAddListener(guiFPS->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::showJointPanel(bool visible){
	switch (selectedJoint){
	case 0:
		gui_Head->setVisible(visible);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 1:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(visible);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 2:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(visible);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 3:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(visible);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 4:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(visible);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 5:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(visible);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 6:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(visible);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 7:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(visible);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 8: 
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(visible);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 9:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(visible);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 10:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(visible);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 11:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(visible);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 12:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(visible);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(false);
		break;
	case 13:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(visible);
		gui_FootR->setVisible(false);
		break;
	case 14:
		gui_Head->setVisible(false);
		gui_Neck->setVisible(false);
		gui_ShoulderL->setVisible(false);
		gui_ShoulderR->setVisible(false);
		gui_ElbowL->setVisible(false);
		gui_ElbowR->setVisible(false);
		gui_HandL->setVisible(false);
		gui_HandR->setVisible(false);
		gui_Torso->setVisible(false);
		gui_HipL->setVisible(false);
		gui_HipR->setVisible(false);
		gui_KneeL->setVisible(false);
		gui_KneeR->setVisible(false);
		gui_FootL->setVisible(false);
		gui_FootR->setVisible(visible);
		break;

	}
}


void Interface::exit(){
	switch(sceneType){
	case 0:			//Particle System
		gui1->saveSettings("gui1Settings.xml");     
		gui2->saveSettings("gui2Settings.xml");     
		gui3->saveSettings("gui3Settings.xml");  
	
		delete gui1;
		delete gui2;
		delete gui3;
		break;
	
	case 1:			//Joints Draw
		gui_Head->saveSettings("gui_HeadSettings.xml");     
		gui_Neck->saveSettings("gui_NeckSettings.xml"); 
		gui_ShoulderL->saveSettings("gui_ShoulderLSettings.xml");     
		gui_ShoulderR->saveSettings("gui_ShoulderRSettings.xml"); 
		gui_ElbowL->saveSettings("gui_ElbowLSettings.xml");     
		gui_ElbowR->saveSettings("gui_ElbowRSettings.xml"); 
		gui_HandL->saveSettings("gui_HandLSettings.xml");     
		gui_HandR->saveSettings("gui_handRSettings.xml"); 
		gui_Torso->saveSettings("gui_TorsoSettings.xml");     
		gui_HipL->saveSettings("gui_HipLSettings.xml"); 
		gui_HipR->saveSettings("gui_HipRSettings.xml");     
		gui_KneeL->saveSettings("gui_KneeLSettings.xml"); 
		gui_KneeR->saveSettings("gui_KneeRSettings.xml");     
		gui_FootL->saveSettings("gui_FootLSettings.xml"); 
		gui_FootR->saveSettings("gui_FootRSettings.xml");     

		guiInfo->saveSettings("guiInfoSettings.xml");     
		guiFPS->saveSettings("guiFPSSettings.xml");  

		delete gui_Head;
		delete gui_Neck;
		delete gui_ShoulderL;
		delete gui_ShoulderR;
		delete gui_ElbowL;
		delete gui_ElbowR;
		delete gui_HandL;
		delete gui_HandR;
		delete gui_Torso;
		delete gui_HipL;
		delete gui_HipR;
		delete gui_KneeL;
		delete gui_KneeR;
		delete gui_FootL;
		delete gui_FootR;
	
		delete guiInfo;
		delete guiFPS;
		break;
	}

}

void Interface::guiEvent(ofxUIEventArgs &e){
	string name = e.getName();
	cout << "got event from: " << name << endl;
	ofxUISlider *slider = e.getSlider();    
	
	switch(sceneType){
	case 0:			//Particle System
		if(name == "COPY SETTINGS"){
			gui1->saveSettings("particleSystem_clipboard.xml");
		}
		else
			if(name == "RETURN TO EDITING"){
				exploring = false;
			}
			else
			{
				if(slider->getName() == "Attraction Force"){
					*sP.force = slider->getScaledValue();
				}
				else
					if(slider->getName() == "Size"){
						*sP.size_PS= slider->getScaledValue();
					}
					else
						if(slider->getName() == "Life Time"){
							*sP.lifeTime_PS= slider->getScaledValue();
						}
						else
							if(slider->getName() == "History"){
								*sP.history = slider->getScaledValue();
							}
							else
								if(slider->getName() == "Rotation"){
									*sP.rotate = slider->getScaledValue();
								}
								else
									if(slider->getName() == "Radius"){
										*sP.eRad = slider->getScaledValue();
									}
									else
										if(slider->getName() == "Particles Rate"){
											*sP.bornRate = slider->getScaledValue();
										}
										else
											if(slider->getName() == "Initial Velocity"){
												*sP.velRad = slider->getScaledValue();
											}
			}
			break;

	case 1: 		//Joints Draw
		if(name == " ACTIVE"){
			switch(selectedJoint){
			case 0:
				isActive_Head = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 1:
				isActive_Neck = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 2:
				isActive_ShoulderL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 3:
				isActive_ShoulderR = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 4:
				isActive_ElbowL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 5:
				isActive_ElbowR = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 6:
				isActive_HandL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 7:
				isActive_HandR = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 8:
				isActive_Torso = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 9:
				isActive_HipL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 10:
				isActive_HipR = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 11:
				isActive_KneeL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 12:
				isActive_KneeR = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 13:
				isActive_FootL = (ofxUIButton *) e.getButton()->getValue();
				break;
			case 14:
				isActive_FootR = (ofxUIButton *) e.getButton()->getValue();
				break;
			}
		}
		else
			if(name == "COPY SETTINGS"){
				switch(selectedJoint){
					case 0:
						gui_Head->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 1:
						gui_Neck->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 2:
						gui_ShoulderL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 3:
						gui_ShoulderR->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 4:
						gui_ElbowL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 5:
						gui_ElbowR->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 6:
						gui_HandL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 7:
						gui_HandR->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 8:
						gui_Torso->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 9:
						gui_HipL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 10:
						gui_HipR->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 11:
						gui_KneeL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 12:
						gui_KneeR->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 13:
						gui_FootL->saveSettings("jointsDraw_clipboard.xml");
						break;
					case 14:
						gui_FootR->saveSettings("jointsDraw_clipboard.xml");
						break;
				}
			}
			else{
				if(name == "RETURN TO EDITING"){
					exploring = false;
				}
				else{
					printf("Updating slider ... \n");
					updateSliders(slider, selectedJoint);
				}
			}
		break;
	}
}

void Interface::updateSliders(ofxUISlider *slider, int selectedJoint){
	switch (selectedJoint){
	case 0:
		if(slider->getName() == "Size"){
			*sP_Head.size_JD = slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_Head.lifeTime_JD = slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_Head.speed = slider->getScaledValue();
				}
		break;

	case 1:
		if(slider->getName() == "Size"){
			*sP_Neck.size_JD = slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_Neck.lifeTime_JD = slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_Neck.speed = slider->getScaledValue();
				}
		break;

	case 2:
		if(slider->getName() == "Size"){
			*sP_ShoulderL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_ShoulderL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_ShoulderL.speed = slider->getScaledValue();
				}
		break;

	case 3: 
		if(slider->getName() == "Size"){
			*sP_ShoulderR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_ShoulderR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_ShoulderR.speed = slider->getScaledValue();
				}
		break;

	case 4:
		if(slider->getName() == "Size"){
			*sP_ElbowL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_ElbowL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_ElbowL.speed = slider->getScaledValue();
				}
		break;

	case 5:
		if(slider->getName() == "Size"){
			*sP_ElbowR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_ElbowR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_ElbowR.speed = slider->getScaledValue();
				}
		break;

	case 6:
		if(slider->getName() == "Size"){
			*sP_HandL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_HandL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_HandL.speed = slider->getScaledValue();
				}
		break;

	case 7:
		if(slider->getName() == "Size"){
			*sP_HandR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_HandR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_HandR.speed = slider->getScaledValue();
				}
		break;

	case 8:
		if(slider->getName() == "Size"){
			*sP_Torso.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_Torso.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_Torso.speed = slider->getScaledValue();
				}
		break;

	case 9:
		if(slider->getName() == "Size"){
			*sP_HipL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_HipL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_HipL.speed = slider->getScaledValue();
				}
		break;

	case 10:
		if(slider->getName() == "Size"){
			*sP_HipR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_HipR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_HipR.speed = slider->getScaledValue();
				}
		break;

	case 11:
		if(slider->getName() == "Size"){
			*sP_KneeL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_KneeL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_KneeL.speed = slider->getScaledValue();
				}
		break;

	case 12:
		if(slider->getName() == "Size"){
			*sP_KneeR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_KneeR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_KneeR.speed = slider->getScaledValue();
				}
		break;

	case 13: 
		if(slider->getName() == "Size"){
			*sP_FootL.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_FootL.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_FootL.speed = slider->getScaledValue();
				}
		break;

	case 14:
		if(slider->getName() == "Size"){
			*sP_FootR.size_JD= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Trail"){
				*sP_FootR.lifeTime_JD= slider->getScaledValue();
			}
			else
				if(slider->getName() == "Drawing Speed"){
					*sP_FootR.speed = slider->getScaledValue();
				}
		break;
	}
}

void Interface::keyPressed(int key){
	switch(sceneType){
	case 0:		//Particle System
		switch (key){
		case OF_KEY_RETURN:
			gui1->toggleVisible();
			gui2->toggleVisible();
			gui3->toggleVisible();
			break;

		case 'r':
			gui1->setPosition(5, 5);
			gui2->setPosition(5, ofGetHeight() - 170 - 5);
			gui3->setPosition(ofGetWidth() - gui3->getGlobalCanvasWidth() - 5, 5);
			break;

		case '1':
			gui1->toggleVisible();
			break;
            
		case '2':
			gui2->toggleVisible();
			break;

		case '3':
			gui3->toggleVisible();
			break;

		default:
			break;
		}
		break;

	case 1:		//Joints Draw
		switch (key){
		case OF_KEY_RETURN:
			jointsVisible = !jointsVisible;
			guiFPS->toggleVisible();
			break;

		case 'r':
			gui_Head->setPosition(5, 5);
			gui_Neck->setPosition(5, 5);
			gui_ShoulderL->setPosition(5, 5);
			gui_ShoulderR->setPosition(5, 5);
			gui_ElbowL->setPosition(5, 5);
			gui_ElbowR->setPosition(5, 5);
			gui_HandL->setPosition(5, 5);
			gui_HandR->setPosition(5, 5);
			gui_Torso->setPosition(5, 5);
			gui_HipL->setPosition(5, 5);
			gui_HipR->setPosition(5, 5);
			gui_KneeL->setPosition(5, 5);
			gui_KneeR->setPosition(5, 5);
			gui_FootL->setPosition(5, 5);
			gui_FootR->setPosition(5, 5);

			guiInfo->setPosition(5, ofGetHeight() - 170 - 5);
			guiFPS->setPosition(ofGetWidth() - guiFPS->getGlobalCanvasWidth() - 170, 5);
			break;

		case 'i':
			guiInfo->toggleVisible();
			break;

		case 'f':
			guiFPS->toggleVisible();
			break;

		default:
			break;
		}
		break;
	}
}