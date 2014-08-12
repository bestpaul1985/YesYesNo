
#include "ofMain.h"
#include "photo.h"
#define _USE_4k_SCREEN


class scene01 : public ofBaseApp {

public:
    enum ACTION{
        
        STAND_BY,
        ACTIVED,
        SELECTED,
        CHOOSE_PHOTO,
        MORE_PHOTO,
        MAKE_PHOTO
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
    ofImage         narrow;
    
    ofRectangle     createOwnRect;
    ofRectangle     moreMotoRect;
    ofRectangle     closeIconRext;


    vector<photo>   photos;
    float           zoomTimer;

    float           screenZ;
    bool            bFixed;
    bool            bDrag;
    bool            bNarrow;

    
    ofPoint         centerPos;
    ofPoint         targetPos;
    
    ofPoint         lastMouse;
    ofPoint         dragPoint;
    ACTION          action;
    

};


