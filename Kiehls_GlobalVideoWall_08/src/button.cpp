#include "button.h"


button::button(){
    xSpeed = ofRandom(0.95, 1.05);
    bMousePressed = false;
    dragDx = 0;
}
//--------------------------------------------------------------
void button::setup(ofImage &img, int x, int y, int Angle){
    
    pos.set(x,y);
    orgPos = pos;
    
    angle = Angle;
    image = &img;
    width = image->getWidth()/5;
    height = image->getHeight()/5;
    rect.setFromCenter(0,0,width, height);
    
    dragDx *= 0.97;
    pos.x += dragDx* xSpeed;
    
    if (pos.x < -width*0.5f) {
        pos.x = ofGetWidth()+width*0.5f;
    }
    else if (pos.x > ofGetWidth()+width*0.5f) {
        pos.x = -width*0.5f;
    }
    
    float xPct = ofMap(pos.x, 0, ofGetWidth(), 0, 1, true);
    float xPctShaped = powf(xPct, 3.0);
    pos.y = ofMap(xPctShaped, 0, 1, orgPos.y, ofGetHeight()/3 + 2*orgPos.y/3.0);
 
}

//--------------------------------------------------------------
void button::update(){
    
    dragDx *= 0.97;
    pos.x += dragDx* xSpeed;
    
    if (pos.x < -width*0.5f) {
        pos.x = ofGetWidth()+width*0.5f;
    }
    else if (pos.x > ofGetWidth()+width*0.5f) {
        pos.x = -width*0.5f;
    }
    
    float xPct = ofMap(pos.x, 0, ofGetWidth(), 0, 1, true);
    float xPctShaped = powf(xPct, 3.0);
    pos.y = ofMap(xPctShaped, 0, 1, orgPos.y, ofGetHeight()/3 + 2*orgPos.y/3.0);
   
   
    if (bMousePressed) {
        
    }
    
}

//--------------------------------------------------------------
void button::draw(){
   
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofSetColor(255);
    image->draw(rect);
    ofPopMatrix();
    
    ofMatrix4x4 matrix;
    matrix.glTranslate( pos.x, pos.y, 0 );
	matrix.glRotate( angle, 0, 0, 1 );
    ofPushMatrix();
    ofMultMatrix(matrix);
    ofSetColor(0,255,0,100);
    ofRect(rect);
    ofPopMatrix();
    
    
}











