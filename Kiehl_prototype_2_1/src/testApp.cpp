#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    screenWidth   =   1080;
    screenHeight  =   1920;
    
    myFbo.allocate(screenWidth, screenHeight, GL_RGBA, 4);

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
    uvcControl.setAutoExposure(true);
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
    
     //shader
    loadShader();
    bShader = false;
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
    
    myFbo.begin();
        ofClear(0,0,0,255);
        ofPushMatrix();
        ofTranslate(1080,0);
        ofRotateZ(90);
        tex.draw(0, 1080, 1920, -1080);
        ofPopMatrix();
    myFbo.end();
    
    
    
    if(bShader) shader.begin();
        if(bShader)shader.setUniform2f("mouse", mouseX, mouseY);
        ofSetColor(255);
        myFbo.draw(0, 0);
    if(bShader) shader.end();
    
    
    
    foreground[setNum].draw(0,0,screenWidth,screenHeight);

}

void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'S'){
        loadShader();
    }
    if (key == 'z'){
        
        ofSaveScreen(ofGetTimestampString() + ".png");
        shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );

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
        if (setNum >= 3) {
            bShader = true;
        }else{
            bShader = false;
        }
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

//--------------------------------------------------------------
void testApp::loadShader(){
    
    #ifdef TARGET_OPENGLES
        shader.load("shaders_gles/noise.vert","shaders_gles/noise.frag");
    #else
        if(ofGetGLProgrammableRenderer()){
            shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
        }else{
            shader.load("shaders/noise.vert", "shaders/noise.frag");
        }
    #endif
    
    mask.loadImage("img_mask.png");

    
}