//
//  scene01.cpp
//  Kiehls_GlobalVideoWall_01
//
//  Created by Peng Cheng on 8/9/14.
//
//

#include "scene01.h"
//--------------------------------------------------------------
void scene01::setup(){
    
    ofEnableAlphaBlending();
    
    ofBackground(230, 231, 232);
    frame.loadImage("images/frame.png");
    closeIcon.loadImage("closeImg.png");
    moreMoto.loadImage("moreMoto.png");
    createOwn.loadImage("createOwn.png");
    
    bSelected = false;
    bPressed = false;
    bDrag = false;
    zoomTimer = ofGetElapsedTimeMillis() - 3000;
    screenZ = -200;
    
    centerPos = ofPoint(2160/8,3840/8);
    targetPos = ofPoint(2160/8,3840/8);
    dragPoint = targetPos;
    
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            photo temPhoto;
            photos.push_back(temPhoto);
            photos.back().init(140*j + (i%2)*ofRandom(50,60),140*i);
            photos.back().pic = &frame;
            photos.back().closeButton = &closeIcon;
        }
    }
    
    action = CHOOSE_PHOTO;
    mouseAction = NONE;
}

//--------------------------------------------------------------
void scene01::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for (int i=0; i<photos.size(); i++) {
        photos[i].update();
        if(photos[i].condition == photo::seleced){
            bSelected = true;
            break;
        }else{
            bSelected = false;
        }
    }
}

//--------------------------------------------------------------

void scene01::draw(){
    
    bool bAnySelected = false;
    ofPoint selectionPoint;
    //------------------------------------------------targetPos
    for (int i=0; i<photos.size();i++){
        if (photos[i].condition == photo::seleced) {
            bAnySelected = true;
            selectionPoint =photos[i].pos;
            dragPoint = photos[i].pos;
        }
    }
    
    if (bAnySelected){
        targetPos = 0.92 * targetPos + 0.08 *selectionPoint;
    }else{
        targetPos = 0.70 * targetPos + 0.30 *dragPoint;
    }
    
    ofPushMatrix();
    //------------------------------------------------zoom in and out
    if (bPressed) {
        screenZ = 0.70 * screenZ + 0.30 * 0;
    }else{
        if (ofGetElapsedTimeMillis()-zoomTimer > 2000) {
            screenZ = 0.92 * screenZ + 0.08 * -200;
        }
    }
    
    if (bSelected) {
        screenZ = 0.70 * screenZ + 0.30 * 0;
        zoomTimer = ofGetElapsedTimeMillis();
    }
    
    //------------------------------------------------darg
    ofTranslate(-targetPos.x,-targetPos.y,screenZ);
    ofTranslate(centerPos.x,centerPos.y, 0);
    
    for (int i=0; i<photos.size(); i++) {
        if (photos[i].condition == photo::display) {
            photos[i].draw();
        }
    }
    
    for (int i=0; i<photos.size(); i++) {
        if (photos[i].condition == photo::seleced) {
            photos[i].draw();
        }
    }
    
    ofPopMatrix();
    
    //------------------------------------------------buttons
    for (int i=0; i<photos.size(); i++) {
        if (photos[i].animation == photo::stop) {
            ofSetColor(255);
            createOwn.draw(70, 700);
            moreMoto.draw(290, 700);
            break;
        }
    }
    
}

//--------------------------------------------------------------
void scene01::keyPressed(int key){
    
    if (key == OF_KEY_LEFT) {
        
        targetPos.x+=10;
        
    }
    
    if (key == OF_KEY_RIGHT) {
       	
        targetPos.x-=10;
        
    }
    
}

//--------------------------------------------------------------
void scene01::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void scene01::mouseMoved(int x, int y ){
    
    
}

//--------------------------------------------------------------
void scene01::mouseDragged(int x, int y, int button){
    
    ofPoint currentMouse;
    ofPoint diff;
    currentMouse.set(x, y);
    diff = (currentMouse - lastMouse)*3;
    if (diff.length() >0) {
        bDrag = true;
    }
    dragPoint = targetPos - diff;
    lastMouse = currentMouse;
    mouseAction = DRAG;
    
}

//--------------------------------------------------------------
void scene01::mousePressed(int x, int y, int button){
    
    lastMouse.set(x, y);
    mouseAction = PRESS;
    bPressed = true;
    
}

//--------------------------------------------------------------
void scene01::mouseReleased(int x, int y, int button){
    
    
    if(!bDrag){
        
        //------------------------------------------------select photo and close photo
        for (int i=0; i<photos.size(); i++) {
            if (bSelected) {
                for (int i=0; i<photos.size(); i++) {
                    if (photos[i].condition == photo::seleced) {
                        photos[i].mousePressed(x, y, centerPos, targetPos);
                    }
                }
            }else{
                photos[i].mousePressed(x, y, centerPos, targetPos);
                
            }
        }
        
        //------------------------------------------------buttons to next step
        for (int i=0; i<photos.size(); i++) {
            if (photos[i].animation == photo::stop) {
                
                ofRectangle rectMoreMoto;
                ofRectangle rectCreateOwn;
                rectMoreMoto.set(70, 700,moreMoto.getWidth(), moreMoto.getHeight());
                rectCreateOwn.set(290, 700, createOwn.getWidth(), createOwn.getHeight());
                
                if (rectMoreMoto.inside(x, y)) {
                    action = MORE_PHOTO;
                    reset();
                }
                if (rectCreateOwn.inside(x, y)) {
                    action = MAKE_PHOTO;
                    reset();
                }
                
                break;
            }
        }
    }
    
    zoomTimer = ofGetElapsedTimeMillis();
    mouseAction = RELESE;
    bDrag = false;
    bPressed = false;
    zoomTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void scene01::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void scene01::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void scene01::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void scene01::reset(){
    
    for (int i=0; i<photos.size(); i++) {
        if (photos[i].animation == photo::stop) {
            photos[i].animation = photo::zoomin_1;
        }
    }
    
}











