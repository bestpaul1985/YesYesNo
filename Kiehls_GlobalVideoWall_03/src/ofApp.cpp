#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(false);
    ofEnableAlphaBlending();
    ofBackground(230, 231, 232);
    myScene01.setup();
    myScene02.setup();
    myScene03.setup();
    myScene04.setup();
    status = DISPLAY_PHOTO;
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
                myScene02.photoAction = scene02::STAND_BY;
                myScene01.reset();
            }
            
            if (myScene01.action == scene01::MORE_PHOTO) {
                myScene01.reset();
            }
            
        }break;
           
        case TAKE_PHOTO:{
            myScene02.update();
            if (myScene02.photoAction == scene02::DONE) {
                status = SIGN_IT;
                myScene03.photo = myScene02.grabTexture;
                myScene02.reset();
            }
        }break;
            
        case SIGN_IT:{
            myScene03.update();
            if (myScene03.bRetake) {
                
                myScene02.kinect.open();
                
                status = TAKE_PHOTO;
                myScene03.reset();
            }
            if (myScene03.bSign) {
                
                
                myScene02.kinect.close();
                
                status = DRESS_PHOTO;
                for (int i=0; i<myScene03.meshes.size(); i++) {
                  myScene04.meshes.push_back(myScene03.meshes[i]);
                }
                myScene04.photo = myScene03.photo;
                myScene03.reset();
            }
        }break;
            
        case DRESS_PHOTO:{
            myScene04.update();
            if(myScene04.action == scene04::DONE){
                status = DISPLAY_PHOTO;
                myScene04.reset();
            }
            
        }break;
    }

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
            
        case SIGN_IT:{
            
            myScene03.draw();

        }break;
            
        case DRESS_PHOTO:{
            myScene04.draw();

        }break;
    }
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 100,100);
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
            
        case SIGN_IT:{
            
        }break;
            
        case DRESS_PHOTO:{
            
            
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
            
        case SIGN_IT:{
            myScene03.mouseDragged(x, y, button);

        }break;
        case DRESS_PHOTO:{
            
            myScene04.mouseDragged(x, y, button);

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
            
        case SIGN_IT:{
            
            myScene03.mousePressed(x, y, button);
            
            
        }break;
        case DRESS_PHOTO:{
            
            myScene04.mousePressed(x, y, button);

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
            
        case SIGN_IT:{
            myScene03.mouseReleased(x,y,button);

        }break;
        case DRESS_PHOTO:{
            
            myScene04.mouseReleased(x, y, button);

            
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




