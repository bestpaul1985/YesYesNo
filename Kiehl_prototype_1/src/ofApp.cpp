#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    camWidth 		= 320;
	camHeight 		= 240;
	
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetVerticalSync(true);
    
    //GUI
    gui.setup();
    gui.add(skinColor.setup("skinColor",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    gui.add(offSet.setup("offSet",15, 0, 50));

    gui.add(skinBrightness.setup("skinBrightness",189, 100, 255));
    gui.add(HairBrightness.setup("HairBrightness",25, 0, 50));

}

//--------------------------------------------------------------
void ofApp::update(){

  	ofBackground(100,100,100);
	
	vidGrabber.update();

    ofColor skinColor(247,187,224);
    ofColor hairColor(231,210,21);
    
    
	if (vidGrabber.isFrameNew()){
        
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i+=3){
            ofColor color(pixels[i],pixels[i+1],pixels[i+2]);
            float b =color.getBrightness();
            
            if (b < skinBrightness + offSet && b > skinBrightness - offSet) {
                videoInverted[i] = skinColor.r;
                videoInverted[i+1] = skinColor.g;
                videoInverted[i+2] = skinColor.b;
            }
            else if(b < HairBrightness + offSet && b > HairBrightness - offSet){
            
                videoInverted[i] = hairColor.r;
                videoInverted[i+1] = hairColor.g;
                videoInverted[i+2] = hairColor.b;

            }
            
            else{
                videoInverted[i] = 200;
                videoInverted[i+1] = 100;
                videoInverted[i+2] = 50;
            }
            
            int bri = b > mouseX ? 0 : 255;
            if (bri == 255){
                videoInverted[i] = 0;
                videoInverted[i] = 0;
                videoInverted[i] = 0;
                
            }
            
		}
        
        
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
        
	}
    

    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
	vidGrabber.draw(20,20);
	videoTexture.draw(20,20+camHeight,camWidth,camHeight);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
