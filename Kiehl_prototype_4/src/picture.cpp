//
//  picture.cpp
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 5/27/14.
//
//

#include "picture.h"


//----------------------------------------------------------------
void picture::init(int x, int y, int w, int h){

    offSet = 8;
    curOffSet = offSet;
    
    frameW = w;
    frameH = h;
    curFrameW = frameW;
    curFrameH = frameH;
    
    center.set(x+w/2,y+h/2);
    currentCenter = center;
    screenCenter.set(ofGetWidth()/2,ofGetHeight()/2);
    speed = 0.07f;
    pct = 0;
    
    frameColor.set(255);
    picColor.set(225);
    darker.set(0);
    
    bSelected = false;
    bFixed = false;

}

//----------------------------------------------------------------
void picture::update(){

    shaW = shadow->width/2;
    shaH = shadow->height/2;
    curShaW = shaW;
    curShaH = shaH;
    
    if (bSelected) {
        pct = pct + speed;
        if (pct > 1) pct = 1;
    }else{
        pct = pct - speed;
        if (pct < 0) pct = 0;
    }
    
    float curPct = powf(pct, 0.7);
    currentCenter.x = center.x*(1-curPct) + screenCenter.x*curPct;
    currentCenter.y = center.y*(1-curPct) + screenCenter.y*curPct;
    curFrameW = frameW*(1-curPct) + (frameW*4)*curPct;
    curFrameH = frameH*(1-curPct) + (frameH*4)*curPct;
    curOffSet = offSet*(1-curPct) + (offSet*4)*curPct;
    curShaW = shaW*(1-curPct) + (shaW*4)*curPct;
    curShaH = shaH*(1-curPct) + (shaH*4)*curPct;
    
    frame.setFromCenter(currentCenter.x, currentCenter.y, curFrameW, curFrameH);
    pic.setFromCenter(currentCenter.x, currentCenter.y-(curFrameH-curFrameW)/2, curFrameW-curOffSet*2, curFrameW-curOffSet*2);
    
}

//----------------------------------------------------------------
void picture::draw(){
    
    ofSetColor(frameColor-darker);
    ofRect(frame);
    ofSetColor(picColor-darker);
    picture->draw(pic);
    ofSetColor(frameColor-darker);
    shadow->draw(frame.x,frame.y, curShaW,curShaH);

}

//----------------------------------------------------------------
void picture::mousePressed(int x, int y){
    
    if(frame.inside(x, y) && !bFixed){
       darker.set(0);
       bSelected = true;
    }
    
    if (bSelected) {
        if (!frame.inside(x, y)) {
            bSelected = false;
        }
    }
    
}

//----------------------------------------------------------------
void picture::mouseMoved(int x, int y){
    
    if(frame.inside(x, y) && !bFixed){
        darker.set(60);
    }
    else{
        darker.set(0);
    }
    
}

//----------------------------------------------------------------
void picture::mouseReleased(int x, int y){
    
    if(frame.inside(x, y) && !bFixed)darker.set(0);
    
}