#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(false);
    ofEnableAlphaBlending();
    ofBackground(230, 231, 232);
    myScene01.setup();
    myScene02.setup();

    status =DISPLAY_PHOTO;
    //--------------------------------------
  
}

//--------------------------------------------------------------
void ofApp::update(){
    
    switch (status) {

        case DISPLAY_PHOTO:{
            myScene01.update();
            if (myScene01.action == scene01::MAKE_PHOTO) {
                status = TAKE_PHOTO;
                myScene02.photoTimer = ofGetElapsedTimeMillis();
                myScene02.photoAction = scene02::COUNT_DOWN;
            }
        }break;
            
        case TAKE_PHOTO:{
            myScene02.update();
            cout<<myScene02.photoAction<<endl;
            if (myScene02.photoAction == scene02::DONE) {
                status = SIGN_IT;
                myScene02.reset();
            }
        }break;
    }
    
    cout<<status<<endl;

}

//--------------------------------------------------------------

void ofApp::draw(){
    
    switch (status) {
        case DISPLAY_PHOTO:{
            myScene01.draw();
         
        }break;
            
        case TAKE_PHOTO:{
            myScene02.draw();
        }break;
    }
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (status) {
        case DISPLAY_PHOTO:{
            myScene01.keyPressed(key);

        }break;
            
        case TAKE_PHOTO:{
            myScene02.keyPressed(key);

        }break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


    switch (status) {
        case DISPLAY_PHOTO:{
            myScene01.mouseDragged(x,y,button);
            
        }break;
            
        case TAKE_PHOTO:{
            myScene02.mouseDragged(x,y,button);

        }break;
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    switch (status) {
        case DISPLAY_PHOTO:{
            myScene01.mousePressed(x,y,button);
            
        }break;
            
        case TAKE_PHOTO:{
            myScene02.mousePressed(x,y,button);

        }break;
    }

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
  
    switch (status) {
        case DISPLAY_PHOTO:{
            myScene01.mouseReleased(x,y,button);
            
        }break;
            
        case TAKE_PHOTO:{
            myScene02.mouseReleased(x,y,button);

        }break;
    }

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::reset(){


}










