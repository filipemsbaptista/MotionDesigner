#include "KinectGraphicalScene.h"


#define MAX_USERS 10
bool g_visibleUsers[MAX_USERS] = {false};
nite::SkeletonState g_skeletonStates[MAX_USERS] = {nite::SKELETON_NONE};

#define USER_MESSAGE(msg) \
	{printf("[%08llu] User #%d:\t%s\n",ts, user.getId(),msg);}

#define GL_WIN_SIZE_X	1280
#define GL_WIN_SIZE_Y	1024
int g_nXRes = 0, g_nYRes = 0;


/* -------------------------------------------------------------------
		 _____       _             ______ _      _             
		/  __ \     | |            | ___ (_)    | |            
		| /  \/ ___ | | ___  _ __  | |_/ /_  ___| | _____ _ __ 
		| |    / _ \| |/ _ \| '__| |  __/| |/ __| |/ / _ \ '__|
		| \__/\ (_) | | (_) | |    | |   | | (__|   <  __/ |   
		 \____/\___/|_|\___/|_|    \_|   |_|\___|_|\_\___|_|   
                                                       
----------------------------------------------------------------------*/
class ColorPicker : public ofBaseApp {
public:
		int pickerType;	// 0 - Three colors (Particle System); 1 - Two colors (Joints Draw)
		void setup(int typeOfPicker);
		void draw();
		void mouseReleased(int x, int y);
		void mouseDragged(int x, int y);
		

		ofColor getColor1(), getColor2(), getColor3();

		ofFbo cP_fbo;				//Buffer to draw color picker
		float rectHeight;			//Height of the color shower
		float margin;				//Margin between color shower and color picker

		ofImage img;				//Image object for color picker
		
		ofColor color1, color2, color3, textColor;	

		float colorPickerIndex;		//0 - Left picker, 1 - Right picker, 2 - Middle picker
};

void ColorPicker::setup(int typeOfPicker){
	pickerType = typeOfPicker;

	img.loadImage("color-picker.png");

	rectHeight = 25;
	margin = 5;

	cP_fbo.allocate(img.width, img.height + rectHeight + margin, GL_RGB32F_ARB);

	color1 = ofColor(15,10,15);
	switch(pickerType){
	case 0:
		color2 = ofColor(ofColor::red);
		color3 = ofColor(ofColor::blue);
		textColor = ofColor(ofColor::black);
		break;
	case 1: 
		color2 = ofColor(ofColor::blue);
		textColor = ofColor(ofColor::black);
		break;
	}
	

	colorPickerIndex = 0;
}

void ColorPicker::draw(){
	cP_fbo.begin();
	ofEnableAlphaBlending();  
		
	//Draw color gradient image
	ofSetColor(255,255,255);
	img.draw(0, rectHeight + margin);
		
	//Draw left picker
	ofSetColor(color1);
	ofFill();
	ofRect(2, 2, img.getWidth()/3, rectHeight);
		
	//Draw right picker
	ofSetColor(color2);
	ofFill();
	ofRect(img.getWidth() - (img.getWidth()/3) - 2, 2, img.getWidth()/3, rectHeight);

	if(pickerType == 1){
		//Draw middle picker
		ofSetColor(color3);
		ofFill();
		ofRect(4 + img.getWidth()/3, 2, img.getWidth()/3, rectHeight);
	}


	ofDisableAlphaBlending();
	cP_fbo.end();

	glEnable(GL_BLEND);  
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

	ofSetColor(255,255,255);

	cP_fbo.draw(ofGetWidth() - cP_fbo.getWidth() - 20, ofGetHeight() - cP_fbo.getHeight() - 20);

	//Draw color picker text
	if(color1.r < 90 && color1.g < 90 && color1.b < 90)
			textColor = ofColor(255, 255, 255);
		else 
			textColor = ofColor(0, 0, 0);
	
	//Check picker text alpha value
	if(colorPickerIndex == 0)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Background", ofGetWidth() - 20 - cP_fbo.getWidth(), ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );
		
	switch(pickerType){
	case 0:
		if(colorPickerIndex == 1)
			ofSetColor(textColor);
		else
			ofSetColor(textColor.r, textColor.g, textColor.b, 85);
		ofDrawBitmapString( "Death", ofGetWidth() - 20 - cP_fbo.getWidth()/3, ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );

		if(colorPickerIndex == 2)
			ofSetColor(textColor);
		else
			ofSetColor(textColor.r, textColor.g, textColor.b, 85);
		ofDrawBitmapString( "Birth", ofGetWidth() - 20 - cP_fbo.getWidth() + img.getWidth()/3, ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );
		break;
	case 1:
		if(colorPickerIndex == 1)
			ofSetColor(textColor);
		else
			ofSetColor(textColor.r, textColor.g, textColor.b, 85);
		ofDrawBitmapString( "Brush", ofGetWidth() - 20 - cP_fbo.getWidth()/3, ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );
		break;
	}
}

void ColorPicker::mouseReleased(int mouseX, int mouseY){
	//Check click on color gradient
	if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
		cP_fbo.begin();
		GLubyte RGB[3];
		float x = cP_fbo.getWidth() - (ofGetWidth() - mouseX - 20);
		float y = cP_fbo.getHeight() - (ofGetHeight() - mouseY - 20);

		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
		if(colorPickerIndex == 0)
			color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		else
			if(colorPickerIndex == 1)
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	

		cP_fbo.end();
	}

	//Check click on left picker
	if(mouseX < (ofGetWidth() - 20 - img.getWidth() + 2) + img.getWidth()/3 &&
		mouseX > ofGetWidth() - 20 - img.getWidth() + 2 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 0;
			cout << "Clicked on left picker!" << endl;
	}

	//Check click on right picker
	if(mouseX < ofGetWidth() - 20 - 2 &&
		mouseX > ofGetWidth() - 20 - 2 - img.getWidth()/3 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 1;
			cout << "Clicked on rigth picker!" << endl;
	}

	if(pickerType == 1){
		//Check click on middle picker
		if(mouseX < ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 + img.getWidth()/3 &&
			mouseX > ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 &&
			mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
			mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
				colorPickerIndex = 2;
				cout << "Clicked on middle picker!" << endl;
		}
	}
}

void ColorPicker::mouseDragged(int mouseX, int mouseY){
	//Check drag on color gradient
	if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
		cP_fbo.begin();
		GLubyte RGB[3];
		float x = cP_fbo.getWidth() - (ofGetWidth() - mouseX - 20);
		float y = cP_fbo.getHeight() - (ofGetHeight() - mouseY - 20);

		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
		if(colorPickerIndex == 0)
			color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		else
			if(colorPickerIndex == 1)
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	

		cP_fbo.end();
	}
}

ofColor ColorPicker::getColor1(){
	return color1;
}

ofColor ColorPicker::getColor2(){
	return color2;
}

ofColor ColorPicker::getColor3(){
	return color3;
}


/* ----------------------------------------------------------
		 _____         _      ___              
		|_   _|       | |    / _ \             
		  | | ___  ___| |_  / /_\ \_ __  _ __  
		  | |/ _ \/ __| __| |  _  | '_ \| '_ \ 
		  | |  __/\__ \ |_  | | | | |_) | |_) |
		  \_/\___||___/\__| \_| |_/ .__/| .__/ 
								  | |   | |    
								  |_|   |_|    
--------------------------------------------------------------*/
ColorPicker _colorPicker;	//Definition of a global variable for color picker
ofFbo _fbo;					//Offscreen buffer for trails
float _time0;				//Time value for computing dt

// PARTICLE SYSTEM
float trail;				//Control parameter for trails between [0, 1] --> 0.0 - trails disappear immediately; 1.0 - trails are infinite.
Params param;				
deque<Particle> particles;	//Particles


// JOINTS DRAW
float _lifeTime;
Params param_General, param_Head, param_Neck, param_ShoulderL, param_ShoulderR, param_ElbowL, param_ElbowR, param_HandL, param_HandR,
	param_Torso, param_HipL, param_HipR, param_KneeL, param_KneeR, param_FootL, param_FootR;				
deque<Brush> _brushes;

void KinectGraphicalScene::setup(int typeOfScene, bool isExplore){
	sceneType = typeOfScene;
	exploreVersion = isExplore;

	// ---- COMMON ----
	ofSetFrameRate(60);

    int w = ofGetWindowWidth(); 
    int h = ofGetWindowHeight();
	_fbo.allocate(w, h, GL_RGB32F_ARB);

	//Fill buffer with background color
	_fbo.begin();
	ofBackgroundGradient(ofColor::gray,ofColor(_colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);
	_fbo.end();	

	_time0 = ofGetElapsedTimef();
	destX = ofGetWidth()/2;
	destY = -ofGetHeight()/2;
	destZ = 1;

	float nBrushes = 15;
	// ---- SPECIFIC ----
	switch(sceneType)
	{
	case 0:		//Particle System
		_colorPicker.setup(0);

		param_General.setup(0);
		param_Head.setup(0);
		param_ShoulderL.setup(0);
		param_ShoulderR.setup(0);
		param_ElbowL.setup(0);
		param_ElbowR.setup(0);
		param_HandL.setup(0);
		param_HandR.setup(0);
		param_Torso.setup(0);
		param_HipL.setup(0);
		param_HipR.setup(0);
		param_KneeL.setup(0);
		param_KneeR.setup(0);
		param_FootL.setup(0);
		param_FootR.setup(0);

		trail = 0.7;

		//Set up interface
		jointsSelector.setup();
	
		interf.setGUI_Head(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_Neck(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ShoulderL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ShoulderR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ElbowL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ElbowR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HandL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HandR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_Torso(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HipL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HipR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_KneeL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_KneeR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_FootL(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_FootR(0, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
	
		interf.setGUIInfo();
		interf.setGUIFPS();
	
		interf.setup(0, exploreVersion);
		break;
	case 1:		//Joints Draw
		_colorPicker.setup(1);

		param_General.setup(1);
		param_Head.setup(1);
		param_ShoulderL.setup(1);
		param_ShoulderR.setup(1);
		param_ElbowL.setup(1);
		param_ElbowR.setup(1);
		param_HandL.setup(1);
		param_HandR.setup(1);
		param_Torso.setup(1);
		param_HipL.setup(1);
		param_HipR.setup(1);
		param_KneeL.setup(1);
		param_KneeR.setup(1);
		param_FootL.setup(1);
		param_FootR.setup(1);

		_lifeTime = 0.9;
		
		//Set up interface
		jointsSelector.setup();
	
		interf.setGUI_Head(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_Neck(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ShoulderL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ShoulderR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ElbowL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_ElbowR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HandL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HandR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_Torso(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HipL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_HipR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_KneeL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_KneeR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_FootL(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
		interf.setGUI_FootR(1, &param.force, &param.size_PS, &param.lifeTime_PS, &trail, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity, &param_Head.size_JD, &_lifeTime, &param_Head.speed);
	
		interf.setGUIInfo();
		interf.setGUIFPS();
	
		interf.setup(1, exploreVersion);


		//Set up brushes
		for (int i = 0; i< nBrushes; i++){
			Brush newB;
			newB.setup(interf.isActive_Head, interf.isActive_Neck, interf.isActive_ShoulderL, interf.isActive_ShoulderR, interf.isActive_ElbowL, interf.isActive_ElbowR, interf.isActive_HandL, interf.isActive_HandR,
							interf.isActive_Torso, interf.isActive_HipL, interf.isActive_HipR, interf.isActive_KneeL, interf.isActive_KneeR, interf.isActive_FootL, interf.isActive_FootR);
			_brushes.push_back(newB);
			cout << "Created brush no. " << i << "\n";
		}

		break;
	}

	// ----------------------------------------

	//NiTE
	niteRc = nite::NiTE::initialize();
	if (niteRc != nite::STATUS_OK)	{
		printf("NiTE initialization failed\n");
	}

	niteRc = userTracker.create();
	if (niteRc != nite::STATUS_OK)	{
		printf("Couldn't create user tracker\n");
	}
	printf("\nStart moving around to get detected...\n");

	drawSkeleton = false;
	drawInterface = interf.guiFPS->isVisible();
}

void KinectGraphicalScene::update(){
	printf ("\nStarting Kinect Scene update()\n");
	 //Compute dt
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time - _time0, 0, 0.1);
	_time0 = time;

	int i = 0;
	int bornN = 0;

	switch(sceneType){
	case 0:		//Particle System
		//Delete inactive particles
		while(i < particles.size()){
			if (!particles[i].live){
				particles.erase(particles.begin()+i);
			}
			else
				i++;
		}

		//Born new particles
		param.bornCount += dt * param.bornRate;		//Update bornCount value
		if(param.bornCount >= 1){
			bornN = int (param.bornCount);		//How many particles born
			param.bornCount -= bornN;				//Correct bornCount value
			for (int i = 0; i < bornN; i++)
			{
				Particle newP;
				newP.setup();
				particles.push_back(newP);
			}
		}
		break;

	case 1:		//Joints Draw
		printf ("\nUpdating brushes (nothing really)\n");

		break;
	}

	//------------------------------------------------
	
	//NiTE
	printf ("\nUpdating Kinect data ...\n");
	
	niteRc = userTracker.readFrame(&userTrackerFrame);
	if(niteRc != nite::STATUS_OK)
		printf("Get next frame failed\n");

	const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
	for (int i = 0; i < users.getSize(); i++)
	{
		const nite::UserData& user = users[i];
		updateUserState(user,userTrackerFrame.getTimestamp());
		
		if (user.isNew())
			userTracker.startSkeletonTracking(user.getId());
		else
			switch(sceneType){
			case 0:
			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
			{
				const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
				const nite::SkeletonJoint& neck = user.getSkeleton().getJoint(nite::JOINT_NECK);
				const nite::SkeletonJoint& handL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND);
				const nite::SkeletonJoint& elbowL = user.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW);
				const nite::SkeletonJoint& handR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND);
				const nite::SkeletonJoint& elbowR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW);
				const nite::SkeletonJoint& shoulderL = user.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER);
				const nite::SkeletonJoint& shoulderR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER);
				const nite::SkeletonJoint& torso = user.getSkeleton().getJoint(nite::JOINT_TORSO);
				const nite::SkeletonJoint& hipL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HIP);
				const nite::SkeletonJoint& hipR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP);
				const nite::SkeletonJoint& kneeL = user.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE);
				const nite::SkeletonJoint& kneeR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE);
				const nite::SkeletonJoint& footL = user.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT);
				const nite::SkeletonJoint& footR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT);
				
				const nite::Point3f center = user.getCenterOfMass();

		/*0*/	headPos = ofPoint((head.getPosition().x - ofGetWidth()/3)*-1, -(head.getPosition().y - ofGetHeight()/2), -head.getPosition().z/param.Zintensity);
		/*1*/	neckPos = ofPoint((neck.getPosition().x - ofGetWidth()/3)*-1, -(neck.getPosition().y - ofGetHeight()/2), -neck.getPosition().z/param.Zintensity);
		/*2*/	handLPos = ofPoint((handL.getPosition().x - ofGetWidth()/3)*-1, -(handL.getPosition().y - ofGetHeight()/2), -handL.getPosition().z/param.Zintensity);
		/*3*/	elbowLPos = ofPoint((elbowL.getPosition().x - ofGetWidth()/3)*-1, -(elbowL.getPosition().y - ofGetHeight()/2), -elbowL.getPosition().z/param.Zintensity);
		/*4*/	handRPos = ofPoint((handR.getPosition().x - ofGetWidth()/3)*-1, -(handR.getPosition().y - ofGetHeight()/2), -handR.getPosition().z/param.Zintensity);
		/*5*/	elbowRPos = ofPoint((elbowR.getPosition().x - ofGetWidth()/3)*-1, -(elbowR.getPosition().y - ofGetHeight()/2), -elbowR.getPosition().z/param.Zintensity);
		/*6*/	shoulderLPos = ofPoint((shoulderL.getPosition().x - ofGetWidth()/3)*-1, -(shoulderL.getPosition().y - ofGetHeight()/2), -shoulderL.getPosition().z/param.Zintensity);
		/*7*/	shoulderRPos = ofPoint((shoulderR.getPosition().x - ofGetWidth()/3)*-1, -(shoulderR.getPosition().y - ofGetHeight()/2), -shoulderR.getPosition().z/param.Zintensity);
		/*8*/	torsoPos = ofPoint((torso.getPosition().x - ofGetWidth()/3)*-1, -(torso.getPosition().y - ofGetHeight()/2), -torso.getPosition().z/param.Zintensity);
		/*9*/	hipLPos = ofPoint((hipL.getPosition().x - ofGetWidth()/3)*-1, -(hipL.getPosition().y - ofGetHeight()/2), -hipL.getPosition().z/param.Zintensity);
		/*10*/	hipRPos = ofPoint((hipR.getPosition().x - ofGetWidth()/3)*-1, -(hipR.getPosition().y - ofGetHeight()/2), -hipR.getPosition().z/param.Zintensity);
		/*11*/	kneeLPos = ofPoint((kneeL.getPosition().x - ofGetWidth()/3)*-1, -(kneeL.getPosition().y - ofGetHeight()/2), -kneeL.getPosition().z/param.Zintensity);
		/*12*/	kneeRPos = ofPoint((kneeR.getPosition().x - ofGetWidth()/3)*-1, -(kneeR.getPosition().y - ofGetHeight()/2), -kneeR.getPosition().z/param.Zintensity);
		/*13*/	footLPos = ofPoint((footL.getPosition().x - ofGetWidth()/3)*-1, -(footL.getPosition().y - ofGetHeight()/2), -footL.getPosition().z/param.Zintensity);
		/*14*/	footRPos = ofPoint((footR.getPosition().x - ofGetWidth()/3)*-1, -(footR.getPosition().y - ofGetHeight()/2), -footR.getPosition().z/param.Zintensity);

				centerPos = ofPoint((center.x  - ofGetWidth()/3)*-1, -(center.y - ofGetHeight()/2), -center.z/param.Zintensity);

				param.eCenter = centerPos;

				//Update the particles
				for (int i = 0; i < particles.size(); i++){
					switch (particles[i].getTargetJoint()){
					case 0:
						destX = headPos.x;
						destY = -headPos.y ;
						destZ = headPos.z;
						break;
					case 1: 
						destX = neckPos.x;
						destY = -neckPos.y ;
						destZ = neckPos.z;
						break;
					case 2:
						destX = handLPos.x;
						destY = -handLPos.y;
						destZ = handLPos.z;
						break;
					case 3: 
						destX = elbowLPos.x;
						destY = -elbowLPos.y;
						destZ = elbowLPos.z;
						break;
					case 4:
						destX = handRPos.x;
						destY = -handRPos.y;
						destZ = handRPos.z;
						break;
					case 5: 
						destX = elbowRPos.x;
						destY = -elbowRPos.y;
						destZ = elbowRPos.z;
						break;
					case 6:
						destX = shoulderLPos.x;
						destY = -shoulderLPos.y;
						destZ = shoulderLPos.z;
						break;
					case 7: 
						destX = shoulderRPos.x;
						destY = -shoulderRPos.y;
						destZ = shoulderRPos.z;
						break;
					case 8:
						destX = torsoPos.x;
						destY = -torsoPos.y;
						destZ = torsoPos.z;
						break;
					case 9:
						destX = hipLPos.x;
						destY = -hipLPos.y;
						destZ = hipLPos.z;
						break;
					case 10:
						destX = hipRPos.x;
						destY = -hipRPos.y;
						destZ = hipRPos.z;
						break;
					case 11: 
						destX = kneeLPos.x;
						destY = -kneeLPos.y;
						destZ = kneeLPos.z;
						break;
					case 12:
						destX = kneeRPos.x;
						destY = -kneeRPos.y;
						destZ = kneeRPos.z;
						break;
					case 13: 
						destX = footLPos.x;
						destY = -footLPos.y;
						destZ = footLPos.z;
						break;
					case 14:
						destX = footRPos.x;
						destY = -footRPos.y;
						destZ = footRPos.z;
						break;
					}
					particles[i].update(dt, destX, destY, destZ);
				}
			}
			else
			{
				destX = 0;
				destY = 0;
				destZ = 0;
				particles[i].update(dt, destX, destY, destZ);
			}
			break;
			
		case 1:
			printf ("\nUpdating Kinect data for JOINTS DRAW...\n");

			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
			{
				const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
				const nite::SkeletonJoint& neck = user.getSkeleton().getJoint(nite::JOINT_NECK);
				const nite::SkeletonJoint& handL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND);
				const nite::SkeletonJoint& elbowL = user.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW);
				const nite::SkeletonJoint& handR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND);
				const nite::SkeletonJoint& elbowR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW);
				const nite::SkeletonJoint& shoulderL = user.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER);
				const nite::SkeletonJoint& shoulderR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER);
				const nite::SkeletonJoint& torso = user.getSkeleton().getJoint(nite::JOINT_TORSO);
				const nite::SkeletonJoint& hipL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HIP);
				const nite::SkeletonJoint& hipR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP);
				const nite::SkeletonJoint& kneeL = user.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE);
				const nite::SkeletonJoint& kneeR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE);
				const nite::SkeletonJoint& footL = user.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT);
				const nite::SkeletonJoint& footR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT);
				
				const nite::Point3f center = user.getCenterOfMass();
				float Zintensity = 2;

		/*0*/	headPos = ofPoint(-head.getPosition().x + ofGetWidth()/2, -(head.getPosition().y - ofGetHeight()/2), -head.getPosition().z/Zintensity);
		/*1*/	neckPos = ofPoint(-neck.getPosition().x + ofGetWidth()/2, -(neck.getPosition().y - ofGetHeight()/2), -neck.getPosition().z/Zintensity);
		/*2*/	handLPos = ofPoint(-handL.getPosition().x + ofGetWidth()/2, -(handL.getPosition().y - ofGetHeight()/2), -handL.getPosition().z/Zintensity);
		/*3*/	elbowLPos = ofPoint(-elbowL.getPosition().x + ofGetWidth()/2, -(elbowL.getPosition().y - ofGetHeight()/2), -elbowL.getPosition().z/Zintensity);
		/*4*/	handRPos = ofPoint(-handR.getPosition().x + ofGetWidth()/2, -(handR.getPosition().y - ofGetHeight()/2), -handR.getPosition().z/Zintensity);
		/*5*/	elbowRPos = ofPoint(-elbowR.getPosition().x + ofGetWidth()/2, -(elbowR.getPosition().y - ofGetHeight()/2), -elbowR.getPosition().z/Zintensity);
		/*6*/	shoulderLPos = ofPoint(-shoulderL.getPosition().x + ofGetWidth()/2, -(shoulderL.getPosition().y - ofGetHeight()/2), -shoulderL.getPosition().z/Zintensity);
		/*7*/	shoulderRPos = ofPoint(-shoulderR.getPosition().x + ofGetWidth()/2, -(shoulderR.getPosition().y - ofGetHeight()/2), -shoulderR.getPosition().z/Zintensity);
		/*8*/	torsoPos = ofPoint(-torso.getPosition().x + ofGetWidth()/2, -(torso.getPosition().y - ofGetHeight()/2), -torso.getPosition().z/Zintensity);
		/*9*/	hipLPos = ofPoint(-hipL.getPosition().x + ofGetWidth()/2, -(hipL.getPosition().y - ofGetHeight()/2), -hipL.getPosition().z/Zintensity);
		/*10*/	hipRPos = ofPoint(-hipR.getPosition().x + ofGetWidth()/2, -(hipR.getPosition().y - ofGetHeight()/2), -hipR.getPosition().z/Zintensity);
		/*11*/	kneeLPos = ofPoint(-kneeL.getPosition().x + ofGetWidth()/2, -(kneeL.getPosition().y - ofGetHeight()/2), -kneeL.getPosition().z/Zintensity);
		/*12*/	kneeRPos = ofPoint(-kneeR.getPosition().x + ofGetWidth()/2, -(kneeR.getPosition().y - ofGetHeight()/2), -kneeR.getPosition().z/Zintensity);
		/*13*/	footLPos = ofPoint(-footL.getPosition().x + ofGetWidth()/2, -(footL.getPosition().y - ofGetHeight()/2), -footL.getPosition().z/Zintensity);
		/*14*/	footRPos = ofPoint(-footR.getPosition().x + ofGetWidth()/2, -(footR.getPosition().y - ofGetHeight()/2), -footR.getPosition().z/Zintensity);

				centerPos = ofPoint(-center.x + ofGetWidth()/2, -(center.y - ofGetHeight()/2), center.z);

				
				for (int i = 0; i < _brushes.size(); i++){
					switch (_brushes[i].getTargetJoint()){
					case 0:
						destX = headPos.x;
						destY = -headPos.y ;
						destZ = headPos.z;
						break;
					case 1: 
						destX = neckPos.x;
						destY = -neckPos.y ;
						destZ = neckPos.z;
						break;
					case 2:
						destX = handLPos.x;
						destY = -handLPos.y;
						destZ = handLPos.z;
						break;
					case 3: 
						destX = elbowLPos.x;
						destY = -elbowLPos.y;
						destZ = elbowLPos.z;
						break;
					case 4:
						destX = handRPos.x;
						destY = -handRPos.y;
						destZ = handRPos.z;
						break;
					case 5: 
						destX = elbowRPos.x;
						destY = -elbowRPos.y;
						destZ = elbowRPos.z;
						break;
					case 6:
						destX = shoulderLPos.x;
						destY = -shoulderLPos.y;
						destZ = shoulderLPos.z;
						break;
					case 7: 
						destX = shoulderRPos.x;
						destY = -shoulderRPos.y;
						destZ = shoulderRPos.z;
						break;
					case 8:
						destX = torsoPos.x;
						destY = -torsoPos.y;
						destZ = torsoPos.z;
						break;
					case 9:
						destX = hipLPos.x;
						destY = -hipLPos.y;
						destZ = hipLPos.z;
						break;
					case 10:
						destX = hipRPos.x;
						destY = -hipRPos.y;
						destZ = hipRPos.z;
						break;
					case 11: 
						destX = kneeLPos.x;
						destY = -kneeLPos.y;
						destZ = kneeLPos.z;
						break;
					case 12:
						destX = kneeRPos.x;
						destY = -kneeRPos.y;
						destZ = kneeRPos.z;
						break;
					case 13: 
						destX = footLPos.x;
						destY = -footLPos.y;
						destZ = footLPos.z;
						break;
					case 14:
						destX = footRPos.x;
						destY = -footRPos.y;
						destZ = footRPos.z;
						break;
					}
					_brushes[i].update(dt, destX, destY, destZ);
				}
			}
			else
			{
				destX = 0;
				destY = 0;
				destZ = 0;
				_brushes[i].update(dt, destX, destY, destZ);
			}
			break;
		}
	}
	//------------------------------------------------

	//Update interface
	interf.update(jointsSelector.jointSelected);

	jointsSelector.update(interf.isActive_Head, interf.isActive_Neck, interf.isActive_ShoulderL, interf.isActive_ShoulderR, interf.isActive_ElbowL, interf.isActive_ElbowR, interf.isActive_HandL, interf.isActive_HandR,
		interf.isActive_Torso, interf.isActive_HipL, interf.isActive_HipR, interf.isActive_KneeL, interf.isActive_KneeR, interf.isActive_FootL, interf.isActive_FootR);
	
	_colorPicker.update();
}

void KinectGraphicalScene::draw(){
	float alpha = 0;
	switch(sceneType){
	case 0:		//Particle System
		printf("	>>  Drawing particles . . .");
		ofBackgroundGradient(ofColor::gray,ofColor(_colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);
		
		//1. Drawing to buffer
		_fbo.begin();
	
		//Draw semi-transparent white rectangle to slightly clearing a buffer (depends on history value)
		ofEnableAlphaBlending();		//Enbale transparency
		alpha = (1 - trail) * 255;
		//ofSetColor(255, 255, 255, alpha);
		ofSetColor(_colorPicker.getColor1().r, _colorPicker.getColor1().g, _colorPicker.getColor1().b, alpha);
		ofFill();
		ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
		ofDisableAlphaBlending();		//Disabale transparency

		//Draw the particles
		ofFill();
		for (int i = 0; i < particles.size(); i++){
			switch (particles[i].getTargetJoint())
			{
			case 0:
				if(jointsSelector.headActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 1: 
				if(jointsSelector.neckActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 2:
				if(jointsSelector.shoulderLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 3: 
				if(jointsSelector.shoulderRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 4:
				if(jointsSelector.elbowLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 5: 
				if(jointsSelector.elbowRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 6:
				if(jointsSelector.handLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 7: 
				if(jointsSelector.handRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 8:
				if(jointsSelector.torsoActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 9:
				if(jointsSelector.hipLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 10:
				if(jointsSelector.hipRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 11: 
				if(jointsSelector.kneeLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 12:
				if(jointsSelector.kneeRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 13: 
				if(jointsSelector.footLActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			case 14:
				if(jointsSelector.footRActivated)		
					particles[i].draw(_colorPicker.getColor3(), _colorPicker.getColor2());
				break;
			default:
				break;
			}
		}
		_fbo.end();
		printf("	>>  Finisehd drawing update!");
	break;
	
	case 1:
		ofBackgroundGradient(ofColor::gray,ofColor(_colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);

		//1. Drawing to buffer
		_fbo.begin();
		//ofBackgroundGradient(ofColor::gray,ofColor(_colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);
	
		//Draw semi-transparent white rectangle to slightly clearing a buffer (depends on history value)
		ofEnableAlphaBlending();		//Enbale transparency
		alpha = (1 - (_lifeTime*1.1)) * 255;
	
		if(alpha == 25)
			alpha = 0;
	
		//ofSetColor(255, 255, 255, alpha);
		ofSetColor(_colorPicker.getColor1().r, _colorPicker.getColor1().g, _colorPicker.getColor1().b, alpha);
		ofFill();
		ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
		ofDisableAlphaBlending();		//Disabale transparency

		//Draw the brushes
		ofFill();
		for (int i = 0; i < _brushes.size(); i++){
			switch (_brushes[i].getTargetJoint())
			{
			case 0:
				if(jointsSelector.headActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 1: 
				if(jointsSelector.neckActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 2:
				if(jointsSelector.shoulderLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 3: 
				if(jointsSelector.shoulderRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 4:
				if(jointsSelector.elbowLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 5: 
				if(jointsSelector.elbowRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 6:
				if(jointsSelector.handLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 7: 
				if(jointsSelector.handRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 8:
				if(jointsSelector.torsoActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 9:
				if(jointsSelector.hipLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 10:
				if(jointsSelector.hipRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 11: 
				if(jointsSelector.kneeLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 12:
				if(jointsSelector.kneeRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 13: 
				if(jointsSelector.footLActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			case 14:
				if(jointsSelector.footRActivated)		
					_brushes[i].draw(_colorPicker.getColor2());
				break;
			default:
				break;
			}
		}
		_fbo.end();
		break;
	}
	
	
	//2. Draw the buffer on the screen
	ofSetColor(255, 255, 255);
	_fbo.draw(0, 0);
	
	
	//3. Draw interface on the screen
	interf.draw();
	if ( drawInterface ) {	
		jointsSelector.draw();
		_colorPicker.draw();
		
	}

	if(drawSkeleton){
		ofSetColor(ofColor::green);
		ofRect(headPos.x, headPos.y, headPos.z, 10, 10);
		ofRect(neckPos.x, neckPos.y, neckPos.z, 10, 10);
		ofRect(handLPos.x, handLPos.y, handLPos.z, 10, 10);
		ofRect(elbowLPos.x, elbowLPos.y, elbowLPos.z, 10, 10);
		ofRect(handRPos.x, handRPos.y, handRPos.z, 10, 10);
		ofRect(elbowRPos.x, elbowRPos.y, elbowRPos.z, 10, 10);
		ofRect(shoulderLPos.x, shoulderLPos.y, shoulderLPos.z, 10, 10);
		ofRect(shoulderRPos.x, shoulderRPos.y, shoulderRPos.z, 10, 10);
		ofRect(torsoPos.x, torsoPos.y, torsoPos.z, 10, 10);
		ofRect(hipLPos.x, hipLPos.y, hipLPos.z, 10, 10);
		ofRect(hipRPos.x, hipRPos.y, hipRPos.z, 10, 10);
		ofRect(kneeLPos.x, kneeLPos.y, kneeLPos.z, 10, 10);
		ofRect(kneeRPos.x, kneeRPos.y, kneeRPos.z, 10, 10);
		ofRect(footLPos.x, footLPos.y, footLPos.z, 10, 10);
		ofRect(footRPos.x, footRPos.y, footRPos.z, 10, 10);

		ofSetColor(ofColor::green);
		ofLine(headPos, neckPos);
		ofLine(neckPos, shoulderLPos);
		ofLine(neckPos, shoulderRPos);
		ofLine(shoulderLPos, elbowLPos);
		ofLine(elbowLPos, handLPos);
		ofLine(shoulderRPos, elbowRPos);
		ofLine(elbowRPos, handRPos);
		ofLine(shoulderLPos, torsoPos);
		ofLine(shoulderRPos, torsoPos);
		ofLine(torsoPos, hipLPos);
		ofLine(torsoPos, hipRPos);
		ofLine(hipLPos, hipRPos);
		ofLine(hipLPos, kneeLPos);
		ofLine(hipRPos, kneeRPos);
		ofLine(kneeLPos, footLPos);
		ofLine(kneeRPos, footRPos);
	}
}

void KinectGraphicalScene::keyPressed(int key){
		interf.keyPressed(key);

	if ( key == OF_KEY_RETURN ){	//Hide/show GUI
		drawInterface = !drawInterface;
	}

	if ( key == OF_KEY_F1 ){		//Grab the screen image to file
		ofImage image;	
		image.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );	

		//Select random file name
		int n = ofRandom( 0, 1000 );
		string fileName = "screen" + ofToString( n ) + ".png";

		image.saveImage( "Screenshots/" + fileName );	
	}


	if(key == OF_KEY_ESC){
		nite::NiTE::shutdown();
		exit();
	}

	if(key == 'h')
		drawSkeleton = !drawSkeleton;

	
	if(key == OF_KEY_CONTROL){
		switch(sceneType){
		case 0:
			for (int i = 0; i < particles.size(); i++)
				if(!particles[i].tracking)
					particles[i].tracking = true;
				else
					particles[i].tracking = false;
			break;
		case 1:
			for (int i = 0; i < _brushes.size(); i++)
				if(!_brushes[i].drawing)
					_brushes[i].drawing = true;
				else
					_brushes[i].drawing = false;
			break;

		}
	}

	if(key == ' '){
		switch(sceneType){
		case 0:
			for (int i = 0; i < particles.size(); i++){
				particles[i].pos.x = ofRandom(ofGetWindowWidth());
				particles[i].pos.y = ofRandom(ofGetWindowHeight());
			}
		break;
		case 1: 
			break;
		}
	}
}

void KinectGraphicalScene::keyReleased(int key){
}

void KinectGraphicalScene::mouseMoved(int x, int y){
	if ( drawInterface ) {
		jointsSelector.mouseMoved(x, y);
	}
}

void KinectGraphicalScene::mouseDragged(int x, int y){
	if ( drawInterface ) {
		_colorPicker.mouseDragged(x, y);
	}
}

void KinectGraphicalScene::mousePressed(int x, int y){
}

void KinectGraphicalScene::mouseReleased(int x, int y){
	if ( drawInterface ) {
		_colorPicker.mouseReleased(x, y);
		jointsSelector.mouseReleased(x, y);
	}
}

void KinectGraphicalScene::windowResized(int w, int h){
	_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);
	switch(sceneType){
	case 0:
		param.eCenter = ofPoint(ofGetWidth()/2, ofGetHeight()/2, 1);
		break;
	case 1:
		break;
	}
}


void KinectGraphicalScene::gotMessage(ofMessage msg){

}

void KinectGraphicalScene::dragEvent(ofDragInfo dragInfo){ 

}

void KinectGraphicalScene::updateUserState(const nite::UserData& user, unsigned long long ts)
{
	if (user.isNew())
		USER_MESSAGE("New")
	else if (user.isVisible() && !g_visibleUsers[user.getId()])
		USER_MESSAGE("Visible")
	else if (!user.isVisible() && g_visibleUsers[user.getId()])
		USER_MESSAGE("Out of Scene")
	else if (user.isLost())
		USER_MESSAGE("Lost")

	g_visibleUsers[user.getId()] = user.isVisible();


	if(g_skeletonStates[user.getId()] != user.getSkeleton().getState())
	{
		switch(g_skeletonStates[user.getId()] = user.getSkeleton().getState())
		{
		case nite::SKELETON_NONE:
			USER_MESSAGE("Stopped tracking.")
			break;
		case nite::SKELETON_CALIBRATING:
			USER_MESSAGE("Calibrating...")
			break;
		case nite::SKELETON_TRACKED:
			USER_MESSAGE("Tracking!")
			break;
		case nite::SKELETON_CALIBRATION_ERROR_NOT_IN_POSE:
		case nite::SKELETON_CALIBRATION_ERROR_HANDS:
		case nite::SKELETON_CALIBRATION_ERROR_LEGS:
		case nite::SKELETON_CALIBRATION_ERROR_HEAD:
		case nite::SKELETON_CALIBRATION_ERROR_TORSO:
			USER_MESSAGE("Calibration Failed... :-|")
			break;
		}
	}
}

