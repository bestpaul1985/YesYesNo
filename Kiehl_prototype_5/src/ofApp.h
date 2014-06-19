#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
    
    enum PHOTO_ACTION{
    
        COUNTDOWN,
        TAKE_PHOTO,
        STAND_BY
        
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
    void takePhoto();
    void loadLUT(string path);
	void applyLUT(ofPixelsRef pix);
    
    int dirLoadIndex;
	ofDirectory dir;
    ofImage logoImg;
    ofImage frameImg;
    ofVideoGrabber vidGrabber;
	ofPoint thumbPos;
    
    ofPoint lutPos;
	ofVec3f lut[32][32][32];
    ofImage lutImg;
    bool doLUT;
    bool LUTloaded;
    
    ofPoint buttonPos;
    float buttonRadius;
    ofColor buttonColor;

    float timer;
    ofTrueTypeFont font;
    int takePhotoCounter;
    
    PHOTO_ACTION action;
    ofImage photo;
    ofPoint photoPos;
};
