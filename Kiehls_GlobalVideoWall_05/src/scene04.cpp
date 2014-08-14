#include "scene04.h"

//--------------------------------------------------------------
void scene04::setup(){
    
#ifdef _USE_4k_SCREEN
    frame.setFromCenter(0,0,1700,1850);
    photoWidth = 1500;
    photoHeight = 1500;
    
    buttonImg01.loadImage("images/skip.png");
    buttonRect01.setFromCenter(ofGetWidth()/2-500,ofGetHeight()/2+1250, buttonImg01.getWidth(), buttonImg01.getHeight());
    buttonImg02.loadImage("images/ok.png");
    buttonRect02.setFromCenter(ofGetWidth()/2+500,ofGetHeight()/2+1250, buttonImg02.getWidth(), buttonImg02.getHeight());
    buttonImg03.loadImage("images/dress_03.png");
    buttonRect03.setFromCenter(ofGetWidth()/2,ofGetHeight()/2-20, buttonImg03.getWidth(), buttonImg03.getHeight());
    buttonImg04.loadImage("images/dress_04.png");
    buttonRect04.setFromCenter(ofGetWidth()/2,ofGetHeight()/2-20, buttonImg04.getWidth(), buttonImg04.getHeight());
    
    propImage.loadImage("helmet.png");
    propRect.setFromCenter(500, 500, propImage.getWidth(), propImage.getHeight());
    propTraget = propRect.getCenter();
#else
    frame.setFromCenter(0,0,400,450);
    photoWidth = 350;
    photoHeight = 350;
    
    buttonImg01.loadImage("dress_01.png");
    buttonRect01.setFromCenter(ofGetWidth()/2-120,ofGetHeight()/2+280, buttonImg01.getWidth(), buttonImg01.getHeight());
    buttonImg02.loadImage("dress_02.png");
    buttonRect02.setFromCenter(ofGetWidth()/2+120,ofGetHeight()/2+280, buttonImg02.getWidth(), buttonImg02.getHeight());
    buttonImg03.loadImage("dress_03.png");
    buttonRect03.setFromCenter(ofGetWidth()/2,ofGetHeight()/2-20, buttonImg03.getWidth(), buttonImg03.getHeight());
    buttonImg04.loadImage("dress_04.png");
    buttonRect04.setFromCenter(ofGetWidth()/2,ofGetHeight()/2-20, buttonImg04.getWidth(), buttonImg04.getHeight());
    
    propImage.loadImage("helmet.png");
    propRect.setFromCenter(100, 100, propImage.getWidth()/5, propImage.getHeight()/5);
    propTraget = propRect.getCenter();
#endif
  
}

//--------------------------------------------------------------
void scene04::update(){
    switch (action) {
        case DRASS_UP:{
            propRect.position.x = 0.9 * propRect.position.x + 0.10 * (propTraget.x-propRect.getWidth()/2);
            propRect.position.y = 0.9 * propRect.position.y + 0.10 * (propTraget.y-propRect.getHeight()/2);
        } break;
            
        case SOCIAL_PROP:{
            
            ofSetColor(255);
            buttonImg03.draw(buttonRect03);
            propImage.draw(propRect);
            
            
        } break;
        case SOCIAL_NO_PROP:{
            
            ofSetColor(255);
            buttonImg03.draw(buttonRect03);
            
        } break;
        case SIGN_UP:{
            
            ofSetColor(255);
            buttonImg04.draw(buttonRect04);
            
        } break;
            
    }

    
    
}

//--------------------------------------------------------------
void scene04::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255);
    ofRect(frame);
    ofPopMatrix();
    
    ofPushMatrix();
#ifdef _USE_4k_SCREEN
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2-75);
#else
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2-25);
#endif
    ofSetColor(255);
    photo.draw(-photoWidth*0.5f, -photoHeight*0.5f,photoWidth,photoHeight);
    ofPopMatrix();
    drawMesh();
    
    switch (action) {
        case DRASS_UP:{
            ofSetColor(255);
            buttonImg01.draw(buttonRect01);
            buttonImg02.draw(buttonRect02);
            propImage.draw(propRect);
        } break;
        
        case SOCIAL_PROP:{
            
            ofSetColor(255);
            buttonImg03.draw(buttonRect03);


        } break;
        case SOCIAL_NO_PROP:{
            
            ofSetColor(255);
            buttonImg03.draw(buttonRect03);
            
        } break;
        case SIGN_UP:{
            
            ofSetColor(255);
            buttonImg04.draw(buttonRect04);

        } break;
    
    }
   

   
    

    
}

//--------------------------------------------------------------
void scene04::keyPressed(int key){
    
}

//--------------------------------------------------------------
void scene04::keyReleased(int key){
    
}

//--------------------------------------------------------------
void scene04::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void scene04::mouseDragged(int x, int y, int button){

    switch (action) {
        case DRASS_UP:{
            if (bSelected) {
                propTraget.set(x, y);
            }
        } break;
    }
}

//--------------------------------------------------------------
void scene04::mousePressed(int x, int y, int button){
    
   
    switch (action) {
        case DRASS_UP:{
            if (propRect.inside(x, y)) {
                propTraget.set(x, y);
                bSelected = true;
            }
        } break;
    }
}

//--------------------------------------------------------------
void scene04::mouseReleased(int x, int y, int button){
    
    
    switch (action) {
        case DRASS_UP:{
            if (buttonRect01.inside(x, y)) {
                action = SOCIAL_NO_PROP;
            }
            
            if (buttonRect02.inside(x, y)) {
                action = SOCIAL_PROP;
            }
            
            if (propRect.inside(x, y)) {
                propTraget.set(x, y);
                bSelected = false;
            }

        } break;
            
        case SOCIAL_PROP:{
            
            if (buttonRect03.inside(x, y)) {
                action = SIGN_UP;
            }
            
            
        } break;
        case SOCIAL_NO_PROP:{
            
            if (buttonRect03.inside(x, y)) {
                action = SIGN_UP;
            }
        } break;
        case SIGN_UP:{
            
            if (buttonRect04.inside(x, y)) {
                action = DONE;
            }
            
        } break;
            
    }
    

}

//--------------------------------------------------------------
void scene04::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void scene04::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void scene04::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void scene04::reset(){
    
    action = DRASS_UP;
    
}
//--------------------------------------------------------------
void scene04::drawMesh(){
    for (int i=0; i<meshes.size(); i++) {
        ofSetColor(30,30,30);
        ofFill();
        meshes[i].draw();
    }
}




