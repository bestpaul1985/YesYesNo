#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "earthLine.h"
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
        ofImage     rockImage;
        ofShader    shader;
};
