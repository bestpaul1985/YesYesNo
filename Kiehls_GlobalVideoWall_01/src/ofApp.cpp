#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableAlphaBlending();
    
    ofBackground(230, 231, 232);
    frame.loadImage("images/frame.png");
    closeIcon.loadImage("closeImg.png");
    moreMoto.loadImage("moreMoto.png");
    createOwn.loadImage("createOwn.png");

    bSelected = false;
    bDrag = false;
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
void ofApp::update(){
    
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

void ofApp::draw(){
    
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
    
    ofPushMatrix();
    
    ofTranslate(-targetPos.x,-targetPos.y,0);
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
void ofApp::keyPressed(int key){

    if (key == OF_KEY_LEFT) {
       
           targetPos.x+=10;
        
    }
    
    if (key == OF_KEY_RIGHT) {
       	
            targetPos.x-=10;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
void ofApp::mousePressed(int x, int y, int button){
    
    lastMouse.set(x, y);
    bDrag = false;
    mouseAction = PRESS;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
  
    if(!bDrag){
        
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

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::reset(){

    for (int i=0; i<photos.size(); i++) {
        if (photos[i].animation == photo::stop) {
            photos[i].animation = photo::zoomin_1;
        }
    }

}











