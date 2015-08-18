#include "ParticleSystemDemo.h"

const int scaleFactor = 3;
const int jointsSize = 5;
const int movementSpeed = 2;

int counter = 0;

ParamsDemo paramsDemo;

ofFbo fbo;					//Offscreen buffer for trails

float history;				//Control parameter for trails between [0, 1] --> 0.0 - trails disappear immediately; 1.0 - trails are infinite.
float time0;				//Time value for computing dt

void ParticleSystemDemo::setup(int x, int y, int width, int height){
	fbo.allocate(width, height, GL_RGB32F_ARB);
	backgroundColor = ofColor(10,10,10);

	//Fill buffer with background color
	fbo.begin();
	ofBackground(backgroundColor);
	fbo.end();

	//Set up parameters
	paramsDemo.setup(x + width/2, y + width/3);
	
	history = 0.7;
	
	time0 = ofGetElapsedTimef();

	setupJoints(x + width/2, y + height/2);
}
 
void ParticleSystemDemo::update(int x, int y, int width, int height){
    //Compute dt
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time - time0, 0, 0.1);
	time0 = time;

	//Delete inactive particles
	int i = 0;
	while(i < particles.size()){
		if (!particles[i].live){
			particles.erase(particles.begin()+i);
		}
		else
			i++;
	}

	//Born new particles
	paramsDemo.bornCount += dt * paramsDemo.bornRate;		//Update bornCount value
	if(paramsDemo.bornCount >= 1){
		int bornN = int (paramsDemo.bornCount);		//How many particles born
		paramsDemo.bornCount -= bornN;				//Correct bornCount value
		for (int i = 0; i < bornN; i++)
		{
			ParticleDemo newP;
			newP.setup();
			particles.push_back(newP);
		}
	}


	//Update particles
	for(int i = 0; i < particles.size(); i++)
		particles[i].update(dt, joints);

	updateJoints();
}
 
void ParticleSystemDemo::draw(bool skeletonVisible){
	//1. Drawing to buffer
	fbo.begin();
	ofBackground(backgroundColor);


	ofSetColor(ofColor::black);
	ofNoFill();
	ofCircle(paramsDemo.eCenter, paramsDemo.eRad);
	
	ofClearAlpha();
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
	
	ofEnableAlphaBlending();
	
	//Draw semi-transparent white rectangle to slightly clearing a buffer (depends on history value)
	float alpha = (1 - history) * 255;
	//ofSetColor(255, 255, 255, alpha);
	ofSetColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, alpha);	//Replace by color valeus in the parameters
	//cout << "Background (rectangle) Alpha: " << alpha << endl;
	ofFill();
	ofRect(0, 0, fbo.getWidth(), fbo.getHeight());
	ofDisableAlphaBlending();		//Disabale transparency
	
	
	//Draw the particles
	ofFill();
	//cout << "Number of Particles: " << particles.size() << endl;
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw(ofColor::blue, ofColor::red);
	}

	if(skeletonVisible)
		drawJoints();

	fbo.end();

	
	//2. Draw the buffer on the screen
	ofSetColor(255, 255, 255);
	fbo.draw(0, 0);
	
}

void ParticleSystemDemo::windowResized(int x, int y, int w, int h){
	fbo.allocate(w, h, GL_RGB32F_ARB);
	paramsDemo.eCenter = ofPoint(x + w/2, y + h/2, 1);
	cout << "eCenter: (" << paramsDemo.eCenter.x << ", " << paramsDemo.eCenter.y << ")" << endl;

	setupJoints(x, y);
}

void ParticleSystemDemo::updateParameters(vector<vector<float>> parameters, float currentTime){
	vector<float> currentParams = parameters[0];
	vector<float> targetParams = parameters[1];

	//Check the current parameterization
	for(int i = 0; i < parameters.size(); i++)
		if(parameters[i][0] < currentTime)
			if(parameters[i][0] > currentParams[0]){
				currentParams = parameters[i];	
				targetParams = parameters[i+1];
			}
		
	
	paramsDemo.force = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[1], targetParams[1])/scaleFactor;
	paramsDemo.size = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[2], targetParams[2])/scaleFactor;
	paramsDemo.lifeTime = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[3], targetParams[3]);
	history = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[4], targetParams[4]);
	paramsDemo.rotate= ofMap(currentTime, currentParams[0], targetParams[0], currentParams[5], targetParams[5]);
	paramsDemo.eRad= ofMap(currentTime, currentParams[0], targetParams[0], currentParams[6], targetParams[6])/scaleFactor;
	paramsDemo.bornRate = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[7], targetParams[7])/10;
	paramsDemo.velRad = ofMap(currentTime, currentParams[0], targetParams[0], currentParams[8], targetParams[8])/scaleFactor;
}

void ParticleSystemDemo::setupJoints(int screenCenterX, int screenCenterY){
	head = ofPoint(screenCenterX, screenCenterY - 105, 1);
	neck = ofPoint(screenCenterX, screenCenterY - 60, 1);
	shoulderL = ofPoint(screenCenterX - 40, screenCenterY - 60, 1);
	shoulderR = ofPoint(screenCenterX + 40, screenCenterY - 60, 1);
	elbowL = ofPoint(screenCenterX - 50, screenCenterY - 10, 1);
	elbowR = ofPoint(screenCenterX + 50, screenCenterY - 10, 1);
	handL = ofPoint(screenCenterX  - 60, screenCenterY + 40, 1);
	handR = ofPoint(screenCenterX  + 60, screenCenterY + 40, 1);
	torso = ofPoint(screenCenterX, screenCenterY - 20, 1);
	hipL = ofPoint(screenCenterX - 30, screenCenterY + 30, 1);
	hipR = ofPoint(screenCenterX + 30, screenCenterY + 30, 1);
	kneeL = ofPoint(screenCenterX - 30, screenCenterY + 90, 1);
	kneeR = ofPoint(screenCenterX + 30, screenCenterY + 90, 1);
	footL = ofPoint(screenCenterX - 30, screenCenterY + 150, 1);
	footR = ofPoint(screenCenterX + 30, screenCenterY + 150, 1);

	joints.push_back(head);
	joints.push_back(neck);
	joints.push_back(shoulderL);
	joints.push_back(shoulderR);
	joints.push_back(elbowL);
	joints.push_back(elbowR);
	joints.push_back(handL);
	joints.push_back(handR);
	joints.push_back(torso);
	joints.push_back(hipL);
	joints.push_back(hipR);
	joints.push_back(kneeL);
	joints.push_back(kneeR);
	joints.push_back(footL);
	joints.push_back(footR);
}

void ParticleSystemDemo::updateJoints(){
		//Elbows
	if(elbowL_goingLeft){
		elbowL.x--;
	}
	else
		elbowL.x++;
	
	if(elbowL_ascending){
		elbowL.y -= movementSpeed/2;
	}else{
		elbowL.y += movementSpeed/2;
	}
	
	cout << "\nElbow L: (" << elbowL.x << ", " << elbowL.y << ")\n";

	//Hands
	if(handL_goingLeft)
		handL.x--;
	else
		handL.x++;
	
	if(handL_ascending)
		handL.y -= movementSpeed * 2;
	else
		handL.y += movementSpeed * 2;
	
	cout << "Hand L: (" << handL.x << ", " << handL.y << ")\n\n";

	//Knees
	if(kneeR_goingLeft)
		kneeR.x--;
	else
		kneeR.x++;

	cout << "Knee R: (" << kneeR.x << ", " << kneeR.y << ")\n\n";

	joints[0] = head;
	joints[1] = neck;
	joints[2] = shoulderL;
	joints[3] = shoulderR;
	joints[4] = elbowL;
	joints[5] = elbowR;
	joints[6] = handL;
	joints[7] = handR;
	joints[8] = torso;
	joints[9] = hipL;
	joints[10] = hipR;
	joints[11] = kneeL;
	joints[12] = kneeR;
	joints[13] = footL;
	joints[14] = footR;


	//-----------------------------------------------------------
	
	//Elbows
	if(elbowL.x <= fbo.getWidth()/2 - 95)
		elbowL_goingLeft = false;
	else
		if(elbowL.x > (fbo.getWidth()/2 - 95) + 30)
			elbowL_goingLeft = true;

	if(elbowL.y <= (fbo.getHeight()/2 - 60))
		elbowL_ascending = false;
	else 
		if(elbowL.y > (fbo.getHeight()/2 - 60) + 40)
			elbowL_ascending = true;

	//Hands
	if(handL.x <= (fbo.getWidth()/2 - 120))
		handL_goingLeft = false;
	else
		if(handL.x > (fbo.getWidth()/2 - 120) + 50)
			handL_goingLeft = true;

	if(handL.y <= (fbo.getHeight()/2 - 130))
		handL_ascending = false;
	else
		if(handL.y > (fbo.getHeight()/2 - 130) + 160)
			handL_ascending = true;

	//Knees
	if(kneeR.x <= fbo.getWidth()/2 + 20)
		kneeR_goingLeft = false;
	else
		if(kneeR.x > (fbo.getWidth()/2 + 20) + 40)
			kneeR_goingLeft = true;

}

void ParticleSystemDemo::drawJoints(){
	ofFill();
	ofSetColor(ofColor::green);
	
	ofRect(head, jointsSize, jointsSize);
	ofRect(neck, jointsSize, jointsSize);
	ofRect(shoulderL, jointsSize, jointsSize);
	ofRect(shoulderR, jointsSize, jointsSize);
	ofRect(elbowL, jointsSize, jointsSize);
	ofRect(elbowR, jointsSize, jointsSize);
	ofRect(handL, jointsSize, jointsSize);
	ofRect(handR, jointsSize, jointsSize);
	ofRect(torso, jointsSize, jointsSize);
	ofRect(hipL, jointsSize, jointsSize);
	ofRect(hipR, jointsSize, jointsSize);
	ofRect(kneeL, jointsSize, jointsSize);
	ofRect(kneeR, jointsSize, jointsSize);
	ofRect(footL, jointsSize, jointsSize);
	ofRect(footR, jointsSize, jointsSize);

	ofLine(head, neck);
	ofLine(neck, shoulderL);
	ofLine(neck, shoulderR);
	ofLine(shoulderL, elbowL);
	ofLine(shoulderR, elbowR);
	ofLine(elbowL, handL);
	ofLine(elbowR, handR);
	ofLine(shoulderL, torso);
	ofLine(shoulderR, torso);
	ofLine(torso, hipL);
	ofLine(torso, hipR);
	ofLine(hipL, hipR);
	ofLine(hipL, kneeL);
	ofLine(hipR, kneeR);
	ofLine(kneeL, footL);
	ofLine(kneeR, footR);
}