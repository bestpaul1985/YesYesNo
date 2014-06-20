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
        void loadImages();
   
        ofVideoGrabber vidGrabber;
        PHOTO_ACTION action;
        ofTrueTypeFont font;

        ofDirectory dir;
        ofImage logoImg;
        ofImage lutImg;
        ofImage frameImg;
        ofImage photo;

        int dirLoadIndex;
        int takePhotoIndex;
    
        float timer;
    
        ofColor buttonColor;
        ofTexture grabPhoto;
        vector<ofTexture> savePhoto;

    
        ofPoint lutPos;
        ofPoint photoPos;
        ofPoint thumbPos;
        ofVec3f lut[32][32][32];

        bool doLUT;
        bool LUTloaded;
    
};
