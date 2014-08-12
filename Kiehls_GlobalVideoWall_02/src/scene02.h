
#include "ofMain.h"
#define _USE_4k_SCREEN

class scene02 : public ofBaseApp {
public:
    enum PHOTO_ACTION{
        STAND_BY,
        COUNT_DOWN,
        TAKING,
        DONE
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
        void loadLUT(string path);
        void applyLUT(ofPixelsRef pix);
    
    
    int 				camWidth;
    int 				camHeight;
    int                 grabWidth;
    int                 grabHeight;
    
    unsigned char * 	photoData;
    
    
    PHOTO_ACTION        photoAction;
    ofVideoGrabber 		vidGrabber;
    ofTexture           grabTexture;

    int                 dirLoadIndex;
    ofDirectory         dir;
    ofPoint             lutPos;
    ofPoint             thumbPos;
	
    bool                LUTloaded;
    ofVec3f             lut[32][32][32];
	
    ofImage             lutImg;
    ofImage             motor;
    ofImage             countImage[3];
    float               photoTimer;
    int                 counter;
    
    ofColor             color;
    
    ofShader            shader;
    ofFbo               myFbo;
    ofFbo               shaderFbo;
};
