
#include "ofMain.h"
#define _USE_4k_SCREEN

class photo{
    
public:
    enum PHOTO_TYPE{
        display,
        seleced
    };
    
    enum PHOTO_ANIMATION{
        zoomout_1,
        zoomout_2,
        zoomin_1,
        zoomin_2,
        stop,
        initial
    };
    
    void init(int x, int y);
    void update();
    void draw();
    void anim();
    void mousePressed(int x, int y, ofPoint centerPos, ofPoint targetPos);

    ofImage *pic;
    ofImage *closeButton;
    ofPoint pos;
    PHOTO_TYPE condition;
    PHOTO_ANIMATION animation;
    
    ofRectangle closeButtonRect;
    
    float angle;
    float sScale, oldScale;
    float sScale_Goal_1,sScale_Goal_2;
    int picW, picH;
    
};

