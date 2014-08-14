
#include "ofMain.h"
#include "baseScene.h"


class displayScene : public baseScene {
	
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

    
    ofImage         frame;
    ofImage         closeIcon;
    ofImage         moreMoto;
    ofImage         createOwn;
    ofImage         narrow;
    
    ofRectangle     createOwnRect;
    ofRectangle     moreMotoRect;
    ofRectangle     closeIconRect;
    
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

