#pragma once

#include "ofMain.h"

//Each parameter should be accessible by all the particles, and global variables can do that.
//But, it is better not to use many global variables, and hence we combine all the parameters in this separate class and declare just one global variable.

class BrushParams{
	public:
		void setup();			

		float size;				
		float speed;			
		bool drawing;			//Is joint drawing

		ofColor color;
};