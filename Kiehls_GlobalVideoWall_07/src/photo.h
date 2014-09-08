#pragma once

#include "ofMain.h"

enum ACTION{
    POP_OUT,
    POP_BACK,
    DEFAULT
};

class photo {
    
public:
    
    photo();
    void setup(ofImage &img, int x, int y, int Angle);
    void update();
    void draw();
    float map(float in, float inMin,float inMax, float outMin, float outMax, float shaper);
    
    float           angle;
    float           xSpeed;
    float           width;
    float           height;
    ofPoint         scale;
    ofPoint         pos;
    ofPoint         orgPos;
    ofPoint         currentPos;
    
    ofImage         *image;
    ofRectangle     rect;
    bool            bMousePressed;
    float           dragDx;
    float           offX,offY;
    float           timer;
    ACTION          myAction;
    
    ofRectangle     targetRect;
};
