//
//  standardFrame.cpp
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 6/9/14.
//
//

#include "standardFrame.h"

void standarFrame::init(int x, int y, int W){

    imgW = W;
    imgH = W/4*3;
    pos.set(x,y);
    angle = 0;
    
}
//------------------------------------------------------------
void standarFrame::draw(){

    frame.setFromCenter(0,0, w, h);

    
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    
    if (img) {
        ofSetColor(255);
        img->draw(0, 0,imgW,imgH);

    }
    ofPopMatrix();
}

//------------------------------------------------------------
void standarFrame::setPos(int x, int y){

    pos.set(x, y);
    
}

//------------------------------------------------------------
void standarFrame::setScale(float scale){
    
    
}
//------------------------------------------------------------
void standarFrame::setAngle(int degree){

    angle = degree;

}

//------------------------------------------------------------
void standarFrame::loadPic(ofImage &IMG){

    img = &IMG;
    imgH = ofMap(imgW, 0, img->getWidth(), 0, ofGetHeight());

}

//------------------------------------------------------------
void standarFrame::loadFont(ofTrueTypeFont &Font){


}