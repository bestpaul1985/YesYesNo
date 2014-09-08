#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "button.h"

class startScene : public baseScene {

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
    void loadXML();
    bool isButtonSelected();
    bool isMouseDragged();
    
    ofImage             bgImage;
    vector<ofImage>     dogImages;
    vector<button>      buttons;
    bool                bFix;
    bool                bDragged;
    ofXml               XML;
    int                 width;
    int                 height;
    ofPoint             preMouse,currentMouse;
};

