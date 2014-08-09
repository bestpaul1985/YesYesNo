
#include "ofMain.h"

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

    
    float angle;
    float sScale, oldScale;
    int picW, picH;
    
};

