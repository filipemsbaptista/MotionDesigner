#include "ParamsDemo.h"

void ParamsDemo::setup(int x, int y){
	eCenter = ofPoint(x, y, 1);
	cout << "eCenter: (" << eCenter.x << ", " << eCenter.y << ")" << endl;

	eRad = 15;
	bornRate = 10;
	bornCount = 0;
	
	velRad = 150;
	lifeTime = 5.0;
	rotate = 30;
	size = 2;
	force = 0.2;
	tracking = true;
}