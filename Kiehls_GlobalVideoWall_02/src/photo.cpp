

#include "photo.h"


void photo::init(int x, int y){
    pos.set(x,y);
    angle = ofRandom(-5,5);
    condition = display;
    #ifdef _USE_4k_SCREEN
    sScale = ofRandom(3,4);
    sScale_Goal_1= 0.8;
    sScale_Goal_2= 1.0;
    #else
    sScale = ofRandom(11,13);
    sScale_Goal_1= 3.0;
    sScale_Goal_2= 4.0;
    #endif
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

    #ifdef _USE_4k_SCREEN
    closeButtonRect.setFromCenter(600,-700,closeButton->getWidth(), closeButton->getHeight());
    #else
    closeButtonRect.setFromCenter(600,-700,closeButton->getWidth(), closeButton->getHeight());
    #endif
    
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofSetColor(255);
    pic->draw(-picW/2, -picH/2, picW, picH);
    if(animation == stop){
        ofSetColor(255);
        closeButton->draw(closeButtonRect);
    }
    
   
    ofPopMatrix();
    ofSetColor(255,0,220);
    ofCircle(closeButtonRect.getCenter(), 100 );
   
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
        rect.set(posX+closeButtonRect.getPosition().x, posY+closeButtonRect.getPosition().y, closeButton->getWidth(), closeButton->getHeight());
        float dis = rect.getCenter().distance(mousePos);
        if ( dis < closeButton->getWidth()/2) {
            animation = zoomin_1;
        }
        
        cout<<dis<<endl;
    }
}

//--------------------------------------------------------------
void photo::anim(){
    
    switch(animation){
        case zoomout_1:{
            sScale = 0.80 * sScale + 0.20 *sScale_Goal_1;
            if (sScale < sScale_Goal_1*1.05f) {
                sScale = sScale_Goal_1;
                animation = zoomout_2;
            }
        }break;
            
        case zoomout_2:{
            sScale = 0.80 * sScale + 0.20 *sScale_Goal_2;
            if (sScale > sScale_Goal_2*0.90f) {
                sScale = sScale_Goal_2;
                animation = stop;
            }
        }break;
            
        case zoomin_1:{
            sScale = 0.90 * sScale + 0.10 *oldScale;
            if (oldScale - sScale < oldScale*0.050f) {
                sScale = oldScale;
                condition = display;
            }
        }break;
    }
    
    picW = pic->getWidth()/sScale;
    picH = pic->getHeight()/sScale;
    
}






