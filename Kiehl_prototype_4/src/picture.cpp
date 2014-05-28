//
//  picture.cpp
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 5/27/14.
//
//

#include "picture.h"

void picture::init(int x, int y, int w, int h){

    rect.set(x, y, w, h);
    color.set(255);
}

//----------------------------------------------------------------
void picture::draw(){

    ofSetColor(color);
    ofRect(rect);
}

//----------------------------------------------------------------
void picture::mousePressed(int x, int y){
    
    if(rect.inside(x, y))color.set(30);
    
}

//----------------------------------------------------------------
void picture::mouseMoved(int x, int y){
    
    if(rect.inside(x, y)){
        color.set(100);}
    else{
        color.set(255);
    }
    
}

//----------------------------------------------------------------
void picture::mouseReleased(int x, int y){
    
    if(rect.inside(x, y))color.set(255);
    
}