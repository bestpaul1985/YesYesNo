
#include "displayScene.h"

void displayScene::setup(){

    loadingAsset();
    
    createOwnRect.setFromCenter(2160/2+500,3840/2+1100, createOwn.getWidth(), createOwn.getHeight());
    moreMotoRect.setFromCenter(2160/2-500,3840/2+1100, moreMoto.getWidth(), moreMoto.getHeight());
    closeIconRect.setFromCenter(2160/2+700,3840/2-700, closeIcon.getWidth(), closeIcon.getHeight());
    
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
    
    action = STAND_BY;
    bFixed = false;
    bDrag = false;
    bNarrow = false;
}
//--------------------------------------------------------------
void displayScene::update(){
    
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
void displayScene::draw(){
    
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
void displayScene::loadingAsset(){
    
    frame.loadImage("images/frame.png");
    closeIcon.loadImage("images/closeImg.png");
    moreMoto.loadImage("images/more.png");
    createOwn.loadImage("images/make_your_own.png");
    narrow.loadImage("images/narrow.png");
    
}



















