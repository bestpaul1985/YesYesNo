#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "earthLine.h"
#include "ofxGui.h"
typedef struct {
	string name;
	float latitude;
	float longitude;
} City;


class testApp : public ofBaseApp{

	public:
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
        void loadCity();
        void drawCity();

        ofImage bot_banner;
        ofImage texture;
    
        ofSpherePrimitive sphere;
        ofMaterial material;
    
        ofImage                 image;
        ofxCvColorImage         colorImage;
        ofxCvGrayscaleImage 	grayImage;
        ofxCvContourFinder      contourFinder;
        
        int                     threshold;
        int                     earthSize;
        
        vector<earthLine> lines;
    
    
        ofFbo       lineFbo;
        ofFbo       flagFbo;

        ofImage     rockImage;
        ofShader    shader;
    
        ofEasyCam cam;
    
        vector<City> cities;
        vector<ofImage> flags;
        vector<ofPoint> angle;

    
        ofxPanel gui;
        ofxIntSlider x;
        ofxIntSlider y;
        ofxIntSlider z;
    
    

};
