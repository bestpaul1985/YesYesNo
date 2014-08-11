#include "scene04.h"

//--------------------------------------------------------------
void scene04::setup(){
    photoWidth = 350;
    photoHeight = 350;
    frame.setFromCenter(0,0,400,450);
    buttonImg.loadImage("dress_01.png");
    buttonRect.setFromCenter(ofGetWidth()/2,ofGetHeight()/2+250, buttonImg.getWidth(), buttonImg.getHeight());
    
}

//--------------------------------------------------------------
void scene04::update(){
    
}

//--------------------------------------------------------------
void scene04::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255);
    ofRect(frame);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2-25);
    ofRotateZ(90);
    ofSetColor(255);
    photo.draw(-photoWidth*0.5f, -photoHeight*0.5f,photoWidth,photoHeight);
    ofPopMatrix();
    drawMesh();
    
    ofSetColor(255);
    buttonImg.draw(buttonRect);
    
}

//--------------------------------------------------------------
void scene04::keyPressed(int key){
    
}

//--------------------------------------------------------------
void scene04::keyReleased(int key){
    
}

//--------------------------------------------------------------
void scene04::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void scene04::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void scene04::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void scene04::mouseReleased(int x, int y, int button){
    if (buttonRect.inside(x, y)) {
        cout<<"SKIP"<<endl;
    }
}

//--------------------------------------------------------------
void scene04::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void scene04::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void scene04::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void scene04::reset(){
    
}
//--------------------------------------------------------------
void scene04::drawMesh(){
    for (int i=0; i<meshes.size(); i++) {
        ofSetColor(30,30,30);
        ofFill();
        meshes[i].draw();
    }
}




