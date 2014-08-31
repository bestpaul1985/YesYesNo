#pragma once

#include "ofMain.h"

class baseScene {

public:
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};

    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    virtual void mousePressed( int x, int y ){};
    virtual void mouseMoved( int x, int y ){};
    virtual void mouseDragged( int x, int y ){};
    virtual void mouseReleased( int x, int y ){};
    virtual void windowResized(int w, int h){};
    virtual void gotMessage(ofMessage msg){};
    virtual void dragEvent(ofDragInfo dragInfo){};

    //ofGetMouseX();

};