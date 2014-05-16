//
//  motorcycle.cpp
//  Kiehl_prototype_2
//
//  Created by Peng Cheng on 5/15/14.
//
//

#include "motorcycle.h"

void motocycle::setup(){

    imgHeavier.loadImage("motoHeavier.png");
    imgThinner.loadImage("motoThinner.png");
    imgHeavier.setAnchorPoint(imgHeavier.getWidth()/2, imgHeavier.getHeight());
    imgThinner.setAnchorPoint(imgHeavier.getWidth()/2, imgHeavier.getHeight());
    
}


void motocycle::update(){

    
}
void motocycle::draw(int x){

    ofPushMatrix();
    ofTranslate(185, 460);
    ofSetColor(255,255,255,x);
    imgHeavier.draw(0,0);
    ofSetColor(255);
    imgThinner.draw(0,0);
    ofPopMatrix();
    
    cout<<x<<endl;

}