#pragma once

#include "ofMain.h"
#include "scene01.h"
#include "scene02.h"
#include "scene03.h"
#include "scene04.h"

enum STATUS{
    
    DISPLAY_PHOTO,
    TAKE_PHOTO,
    SIGN_IT,
    DRESS_PHOTO,
};


class ofApp : public ofBaseApp{

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
        void reset();
    
        scene01             myScene01;
        scene02             myScene02;
        scene03             myScene03;
        scene04             myScene04;
        STATUS              status;

};
