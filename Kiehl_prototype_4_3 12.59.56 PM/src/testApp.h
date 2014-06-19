#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "Polaroidframe.h"

class frameSorter{
public:
    Polaroidframe frame;
    int number;
    bool bSelected;
};

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
        void loadPicture();
        void loadShadows();
        void setupPicture();
        void sortPicture();
        void sortSelectPicture();
        bool isAnimation();
    
        vector <ofImage> images;
        vector <ofImage> shadows;

        ofImage shadow;
        ofImage banner;
        ofTrueTypeFont font;
    
        vector<Polaroidframe> frames;
        vector<frameSorter> sorter;
    
        ofXml XML;
        int Angle;
        int frameWidth ;
        int frameStyle;
        int shadowNum;
    
        bool bTransition;
        bool enable_Debug_Mode;
};
