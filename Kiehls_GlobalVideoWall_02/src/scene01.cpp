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
    narrow.loadImage("narrow.png");
    
    #ifdef _USE_4k_SCREEN
        createOwnRect.setFromCenter(2160/2+500,3840/2+900, createOwn.getWidth()*2, createOwn.getHeight()*2);
        moreMotoRect.setFromCenter(2160/2-500,3840/2+900, moreMotoRect.getWidth()*2, moreMotoRect.getHeight()*2);
        closeIconRect.setFromCenter(2160/2-500,3840/2-700, moreMotoRect.getWidth()*2, moreMotoRect.getHeight()*2);

        zoomTimer = ofGetElapsedTimeMillis() - 3000;
        screenZ = -1000;
        centerPos = ofPoint(2160/2,3840/2);
        targetPos = ofPoint(2160/2,3840/2);
        dragPoint = targetPos;
        for (int i=0; i<80; i++) {
            for (int j=0; j<20; j++) {
                photo temPhoto;
                photos.push_back(temPhoto);
                photos.back().init(540*j + (i%2)*ofRandom(40,60),540*i);
                photos.back().pic = &frame;
            }
        }

    #else
        createOwnRect.setFromCenter(2160/2+500,3840/2+500, createOwn.getWidth(), createOwn.getHeight());
        zoomTimer = ofGetElapsedTimeMillis() - 3000;
        screenZ = -2000;
        centerPos = ofPoint(2160/8,3840/8);
        targetPos = ofPoint(2160/8,3840/8);
        dragPoint = targetPos;
        for (int i=0; i<80; i++) {
            for (int j=0; j<20; j++) {
                photo temPhoto;
                photos.push_back(temPhoto);
                photos.back().init(130*j + (i%2)*ofRandom(40,60),130*i);
                photos.back().pic = &frame;
            }
        }
    #endif

    
   
    
    action = STAND_BY;
    bFixed = false;
    bDrag = false;
    bNarrow = false;
}

//--------------------------------------------------------------
void scene01::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for (int i=0; i<photos.size(); i++) {
        photos[i].update();
    }
    
    switch (action) {
        case STAND_BY:{
        }break;
        case ACTIVED:{
            if (ofGetElapsedTimeMillis()-zoomTimer > 2000) {
                screenZ = 0.92 * screenZ + 0.08 * -1000;
                bFixed = false;
                bDrag = false;
                bNarrow = false;
                if (screenZ < -957) {
                    action = STAND_BY;
                    screenZ = -1000;
                }
            }else{
                screenZ = 0.90 * screenZ + 0.10 * 0;
            }
            
            for (int i=0; i<photos.size(); i++) {
                if (photos[i].condition == photo::seleced) {
                    action = SELECTED;
                    bNarrow = false;
                }
            }
        }break;
        case SELECTED:{
            for (int i=0; i<photos.size(); i++) {
                if (photos[i].animation == photo::zoomin_1 && photos[i].condition == photo::display) {
                    action = ACTIVED;
                    photos[i].animation = photo::initial;
                }
            }
            zoomTimer = ofGetElapsedTimeMillis();
        }break;
        
            
    }
    
    
    
}

//--------------------------------------------------------------

void scene01::draw(){
    
    bool bAnySelected = false;
    ofPoint selectionPoint;

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
    
    //------------------------------------------------darg

    ofPushMatrix();
    
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
            createOwn.draw(createOwnRect);
            moreMoto.draw(moreMotoRect);
            closeIcon.draw(closeIconRect);
            break;
        }
    }
    
    if (bNarrow) {
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        int w = narrow.getWidth()/6;
        int h = narrow.getHeight()/6;
        narrow.draw(-w/2,-h/2, w,h);
        ofPopMatrix();
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
    
    switch (action) {
      
        case ACTIVED:{
            ofPoint mousePos(x,y);
            ofPoint diff = mousePos - lastMouse;
            dragPoint = targetPos - diff*2;
            if (diff.length() > 0) {
                bDrag = true;
                bNarrow = false;
                zoomTimer = ofGetElapsedTimeMillis();
            }
            lastMouse = mousePos;
            
        }break;

    }
}

//--------------------------------------------------------------
void scene01::mousePressed(int x, int y, int button){
    
        switch (action) {
        case STAND_BY:{
            action = ACTIVED;
            lastMouse.set(x, y);
            zoomTimer = ofGetElapsedTimeMillis();
            bNarrow = true;
        }break;
        case ACTIVED:{
            lastMouse.set(x, y);
            
        }break;
        case SELECTED:{
            
        }break;
    }
}

//--------------------------------------------------------------
void scene01::mouseReleased(int x, int y, int button){
    
    switch (action) {
        case ACTIVED:{
            
            if(bFixed){
                if (!bDrag) {
                    for (int i=0; i<photos.size(); i++) {
                        photos[i].mousePressed(x, y, centerPos, targetPos);
                    }
                }
            }
            bFixed = true;
            bDrag = false;
            
        }break;
        case SELECTED:{
            
            for (int i=0; i<photos.size(); i++) {
                if (photos[i].animation == photo::stop) {
                    
                    photos[i].mousePressed(x, y, centerPos, targetPos);
                   
                    if (moreMotoRect.inside(x, y)) {
                        action = MORE_PHOTO;
                        photos[i].animation = photo::zoomin_1;
                    }
                    if (createOwnRect.inside(x, y)) {
                        action = MAKE_PHOTO;
                        photos[i].animation = photo::zoomin_1;
                    }
                
                    break;
                }
            }
            
        }break;
    }





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
    zoomTimer = ofGetElapsedTimeMillis() - 3000;
    screenZ = -200;
    action = STAND_BY;
    bFixed = false;
    bDrag = false;
    bNarrow = false;
}










