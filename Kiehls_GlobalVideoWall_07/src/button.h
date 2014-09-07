#pragma once

#include "ofMain.h"

class button {
    
public:
    
    button();
    void setup(ofImage &img, int x, int y, int Angle);
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    float           angle;
    float           xSpeed;
    float           width;
    float           height;
    ofPoint         pos;
    ofPoint         orgPos;
    ofImage         *image;
    ofRectangle     rect;
    
};
