

#include "photo.h"


void photo::init(int x, int y){
    pos.set(x,y);
    angle = ofRandom(-5,5);
    condition = display;
    sScale = ofRandom(3,4);
    oldScale = sScale;
    animation = initial;
    
}

//--------------------------------------------------------------
void photo::update(){

    switch (condition) {
        case display:{
            picW = pic->getWidth()/sScale;
            picH = pic->getHeight()/sScale;
        } break;
        case seleced:{
            
            anim();
            
            
           
        }break;
    }
    
}

//--------------------------------------------------------------
void photo::draw(){

    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofSetColor(255);
    pic->draw(-picW/2, -picH/2, picW, picH);
    if(animation == stop){
        ofSetColor(255);
        closeButton->draw(300,-300);
    }
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void photo::mousePressed(int x, int y, ofPoint centerPos, ofPoint targetPos){
    ofPoint mousePos(x,y);
    ofRectangle rect;
    int posX,posY;
    posX = pos.x +(centerPos.x - targetPos.x);
    posY = pos.y +(centerPos.y - targetPos.y);
    
    if (condition == display) {
        rect.setFromCenter(posX, posY, picW, picH);
        if (rect.inside(x, y)) {
            condition = seleced;
            animation = zoomout_1;
        }
    }
    
    
    if (condition == seleced) {
        rect.set(posX+130, posY-170, closeButton->getWidth(), closeButton->getHeight());
        float dis = rect.getCenter().distance(mousePos);
        if ( dis < closeButton->getWidth()/2) {
            animation = zoomin_1;
        }
    }
}

//--------------------------------------------------------------
void photo::anim(){
    
    switch(animation){
        case zoomout_1:{
            sScale = 0.80 * sScale + 0.20 *0.8;
            if (sScale < 0.85) {
                sScale = 0.80;
                animation = zoomout_2;
            }
        }break;
            
        case zoomout_2:{
            sScale = 0.80 * sScale + 0.20 *1;
            if (sScale > 0.95) {
                sScale = 1;
                animation = stop;
            }
        }break;
            
        case zoomin_1:{
            sScale = 0.90 * sScale + 0.10 *oldScale;
            if (oldScale - sScale < 0.5) {
                sScale = oldScale;
                condition = display;
            }
        }break;
    }
    
    picW = pic->getWidth()/sScale;
    picH = pic->getHeight()/sScale;
    
}






