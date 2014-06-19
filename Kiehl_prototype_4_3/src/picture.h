
#include "ofMain.h"

class picture{
    
public:
    void init(int x, int y, int w, int h, int FrameNum);
    void draw();
    void update();

    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    void mouseMoved(int x, int y);


    int frameW, frameH,curFrameW,curFrameH;
    int offSet, curOffSet;
    int shaW, shaH, curShaW, curShaH;
    ofColor frameColor;
    ofColor picColor;
    ofColor darker;

    ofPoint center,currentCenter, screenCenter;
    float speed,pct;
    
    ofRectangle frame,pic;
    ofImage *shadow;
    ofImage *picture;
    bool bSelected, bFixed;
    
    int frameNum;
};

