//
//  photo.cpp
//  Kiehls_GlobalVideoWall_06
//
//  Created by Peng Cheng on 8/19/14.
//
//

#include "photo.h"

photo::photo(){
    
    xSpeed = ofRandom(0.95, 1.05);
    level = 0;
}

void photo::setup(ofImage &img, int x, int y, int Angle){
    
    photoBg = &img;
    pos.set(x, y);
    photoW = photoBg->getWidth()/5;
    photoH = photoBg->getHeight()/5;
    rect.setFromCenter(pos.x,pos.y, photoW, photoH);
    angle = Angle;
    orgY = y;
    startAngle = ofRandom(-10, 10);
    endAngle = ofRandom(-10, 10);
}

//--------------------------------------------------------------
void photo::update(){
    
}

//--------------------------------------------------------------
void photo::draw(){
    
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofSetColor(255);
    photoBg->draw(-photoW*0.5, -photoH*0.5,photoW, photoH);
    ofPopMatrix();
  
}