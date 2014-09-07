#include "button.h"


button::button(){
    xSpeed = ofRandom(0.95, 1.05);
}
//--------------------------------------------------------------
void button::setup(ofImage &img, int x, int y, int Angle){
    
    pos.set(x,y);
    orgPos = pos;
    angle = Angle;
    image = &img;
    width = image->getWidth()/5;
    height = image->getHeight()/5;
}

//--------------------------------------------------------------
void button::update(){
    
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
void button::draw(){
   
    ofPushMatrix();
    ofTranslate(pos);
//    ofRotateZ(angle);
    ofSetColor(255);
    image->draw(-width*0.5, -height*0.5,width, height);
//    ofSetColor(255,120);
//    ofRect(-width*0.5, -height*0.5,width, height);
    ofPopMatrix();
}

//--------------------------------------------------------------
void button::keyPressed(int key){
    
}

//--------------------------------------------------------------
void button::keyReleased(int key){
    
}

//--------------------------------------------------------------
void button::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void button::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void button::mousePressed(int x, int y, int button){
    
    rect.setFromCenter(pos, width, height);
    if (rect.inside(x,y)) {
        cout<<"mousePressed"<<endl;
    }
}

//--------------------------------------------------------------
void button::mouseReleased(int x, int y, int button){
    
}










