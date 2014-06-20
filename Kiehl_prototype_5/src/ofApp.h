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
        void setupLUT();

    
    int                 dirLoadIndex;
    int                 takePhotoIndex;
    ofVideoGrabber      vidGrabber;

    float buttonRadius;
    float timer;

    ofTrueTypeFont      font;
	ofDirectory         dir;
    PHOTO_ACTION        action;

    ofImage             logoImg;
    ofImage             frameImg;
    ofImage             lutImg;

    ofTexture           grabPhoto;
	
    ofColor             buttonColor;
    ofVec3f             lut[32][32][32];
    ofPoint             thumbPos;
    ofPoint             lutPos;
    ofPoint             buttonPos;
    ofPoint             photoPos;

    bool doLUT;
    bool LUTloaded;
};
