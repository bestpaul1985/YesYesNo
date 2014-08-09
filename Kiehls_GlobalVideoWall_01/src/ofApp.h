#pragma once

#include "ofMain.h"
#include "photo.h"
class ofApp : public ofBaseApp{

	public:
    
    enum ACTION{
    
        CHOOSE_PHOTO,
        MORE_PHOTO,
        MAKE_PHOTO
    };
    
    enum MOUSE_ACTION{
        PRESS,
        DRAG,
        MOVE,
        RELESE,
        NONE
    };
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void reset();
    
    ofImage         frame;
    ofImage         closeIcon;
    ofImage         moreMoto;
    ofImage         createOwn;

    
    int             screenScale;
    vector<photo>   photos;
    bool            bSelected;
    bool            bDrag;
    float           zoomTimer;
    ofPoint         centerPos;
    ofPoint         targetPos;
    ofPoint         lastMouse;
    ofPoint         dragPoint;
    ACTION          action;
    MOUSE_ACTION    mouseAction;
};
