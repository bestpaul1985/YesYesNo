#include "ofMain.h"
#include "ofApp.h"
#define _USE_4k_SCREEN

//========================================================================
int main( ){
	ofSetupOpenGL(2160,3840,OF_WINDOW);			// <-------- setup the GL context
    #ifdef _USE_4k_SCREEN
        ofSetupOpenGL(2160,3840,OF_WINDOW);		
    #else
        ofSetupOpenGL(2160/4,3840/4,OF_WINDOW);
    #endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:540X960
	ofRunApp(new ofApp());

}
