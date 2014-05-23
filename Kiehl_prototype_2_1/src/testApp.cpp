#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    screenHeight   = 1080;
    screenWidth     =  1920;
    
    yaml.load("camera_settings.yml");
    
    int cameraToUse;
    yaml.doc["cameraToUse"] >> cameraToUse;
    
    int vendorId, productId, interfaceNum;
    yaml.doc["cameras"][cameraToUse]["vendorId"] >> vendorId;
    yaml.doc["cameras"][cameraToUse]["productId"] >> productId;
    yaml.doc["cameras"][cameraToUse]["interfaceNum"] >> interfaceNum;
    yaml.doc["cameras"][cameraToUse]["name"] >> cameraName;
    yaml.doc["cameras"][cameraToUse]["width"] >> camWidth;
    yaml.doc["cameras"][cameraToUse]["height"] >> camHeight;
    cout<<camWidth<<"   "<<camHeight << endl;
    
    vidGrabber.initGrabber(camWidth, camHeight);
    
    int deviceId = 0;
    vector<string> availableCams = vidGrabber.listVideoDevices();
    
    for(int i = 0; i < availableCams.size(); i++){
        if(availableCams.at(i) == cameraName){
            deviceId = i;
        }
    }
    
    vidGrabber.setDeviceID(deviceId);
    
    focus = 0.5;
    
    uvcControl.useCamera(vendorId, productId, interfaceNum);
    uvcControl.setAutoExposure(false);
    controls = uvcControl.getCameraControls();
    
    //images
    setNum = 0;
    ofDirectory dir;
    int nFiles = dir.listDir("foreground");
    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            foreground.push_back(ofImage());
            foreground.back().loadImage(filePath);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    vidGrabber.update();
    if(vidGrabber.isFrameNew())
    {
        tex.loadData(vidGrabber.getPixelsRef());
    }
    controls = uvcControl.getCameraControls();
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void testApp::draw(){

    
    
    ofBackground(0);
    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(1080,0);
    ofRotateZ(90);
    tex.draw(0, 1080, 1920, -1080);
    ofPopMatrix();
    
    
    foreground[setNum].draw(0,0,1080,1920);

}

void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'z'){
        
        ofSaveScreen(ofGetTimestampString() + ".png");
        
    }
    
    if (key  =='s'){
        ofSetWindowShape(1080, 1920);
    }
    
    
    if(key == 'e'){
        uvcControl.setAutoExposure(!uvcControl.getAutoExposure());
    }
    
    if(key == 'f'){
        uvcControl.setAutoFocus(!uvcControl.getAutoFocus());
    }
    
    if(key == '='){
        focus += 0.1;
        uvcControl.setAbsoluteFocus(focus);
    }
    
    if(key == '-'){
        focus -= 0.1;
        uvcControl.setAbsoluteFocus(focus);
        
    }
    
    if (key == ' ' ) {
        setNum ++;
        if (setNum>foreground.size()-1) setNum = 0;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}