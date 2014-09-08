#pragma once

#include "ofMain.h"

class button {
    
public:
    
    button();
    void setup(ofImage &img, int x, int y, int Angle);
    void update();
    void draw();
  
    float           angle;
    float           xSpeed;
    float           width;
    float           height;
    ofPoint         pos;
    ofPoint         orgPos;
    
    ofImage         *image;
    ofRectangle     rect;
    bool            bMousePressed;
  
    float dragDx;
};
