#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    camW = 640;
    camH = 480;
    setNum = 0;
    
    video.setDeviceID(0);
	video.setDesiredFrameRate(30);
	video.initGrabber(camW,camH);
    
    
    ofSetVerticalSync(false);
    ofEnableAlphaBlending();
    flipImage.allocate(camW, camH, OF_IMAGE_COLOR);
    
   
    bot_banner.loadImage("banner.png");
    
    ofDirectory dir;
    int nFiles = dir.listDir("foreground");
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) {
            
            // add the image to the vector
            string filePath = dir.getPath(i);
            foreground.push_back(ofImage());
            foreground.back().loadImage(filePath);
        }
        
    }
    
    setNum = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    ofBackground(100,100,100);

    video.update();
    
    
    if (video.isFrameNew()){
        //flipImage.setFromPixels(video.getPixelsRef());
        //flipImage.mirror(false, true);
        //flipImage.update();
    }
    
}

//----------------z----------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    video.draw(video.width/4*3, 0, -video.width, video.height);
    foreground[setNum].draw(0, 0);
    bot_banner.draw(0, 410);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ' ) {
        setNum ++;
        if (setNum>foreground.size()-1) setNum = 0;
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
