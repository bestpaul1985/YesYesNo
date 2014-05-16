//
//  Skeleton.cpp
//  Kiehl_prototype_2
//
//  Created by Peng Cheng on 5/15/14.
//
//

#include "Skeleton.h"


void Skeleton::setup(){
    
    imgThinner.loadImage("skeThinner.png");
    imgHeavier.loadImage("skeHeavier.png");
    imgHeavier.setAnchorPoint(imgHeavier.getWidth()/2, imgHeavier.getHeight());
    imgThinner.setAnchorPoint(imgHeavier.getWidth()/2, imgHeavier.getHeight());
    
    bAnimation = false;
    timer = ofGetElapsedTimeMillis();
    angle = -180;
}


void Skeleton::update(){
    
    
    if (bAnimation) {
        int timeDiff = 300;
    
        float pct = ofMap (ofGetElapsedTimeMillis()-timer, 0, timeDiff, 0, 1, true);
        pct = powf(pct, 0.7);
        angle = ofMap(pct, 0,1, -180, 0, true);
        if (ofGetElapsedTimeMillis()-timer > timeDiff) bAnimation = false;
    
    }else{
        timer = ofGetElapsedTimeMillis();
    }

    
}
void Skeleton::draw(){
    
    ofPushMatrix();
    ofTranslate(250, 460);
    ofRotateZ(angle);
    ofSetColor(255,255,255,120);
    imgHeavier.draw(0,0);
    ofSetColor(255);
    imgThinner.draw(0,0);
    ofPopMatrix();


//    cout<<bAnimation<<endl;

}





