


#ifndef _BASE_SCENE
#define _BASE_SCENE


//-- SMART OBJECT THAT HOLD DATA
//-- DUMB SCENES



#include "ofMain.h"


class baseScene {
	

	public: 
	
	virtual void setup(){};
	virtual void update(){
    
        printf ("hello from baseScene \n");
    };
	virtual void draw(){};
    
    
    
    virtual void mousePressed( int x, int y ){};
    //ofGetMouseX();
    
	
    
};





#endif