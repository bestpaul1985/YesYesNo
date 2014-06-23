#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofEnableAlphaBlending();

    vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(640,480);
    loadImages();
    setupLUT();
    
    timer = ofGetElapsedTimeMillis();
    font.loadFont("verdana.ttf", 100);
    takePhotoIndex = -1;
    counterIndex = 0;
    action = STAND_BY;
    
    grabTexture.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(),GL_RGB);
    
    for(int i=0; i<6; i++){
        float scale = 1.3;
        photoFrame temFrame;
        frames.push_back(temFrame);
        frames.back().initial( 0, frameImg.getHeight()/3 *scale * (i%3-1), lutImg, frameImg, grabTexture, scale);
    }

}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    vidGrabber.update();
    if (vidGrabber.isFrameNew()){
        applyLUT(vidGrabber.getPixelsRef());
    }
    takePhoto();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0,0,0,255);
    ofPushMatrix();
    ofTranslate(lutPos);
    ofSetColor(255);
    lutImg.draw(lutImg.getWidth()/2,-lutImg.getHeight()/2,-lutImg.getWidth(),lutImg.getHeight());
    ofPopMatrix();
    
    int textureW = 360;
    int textureH = 480;
    grabTexture.loadScreenData(ofGetWidth()/2-textureW/2, ofGetHeight()/2-textureH/2, textureW, textureH);
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    //-------------------------frames
    
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2+50, ofGetHeight()/2+50);
        ofPushMatrix();
        ofTranslate(-110, 10);
        ofRotate(-10);
        for (int i=3; i<6; i++) {
            frames[i].draw();
        }
        ofPopMatrix();
    
        ofPushMatrix();
        ofTranslate(0, 0);
        ofRotate(0);
        for (int i=0; i<3; i++) {
            frames[i].draw();
        }
        ofPopMatrix();
    ofPopMatrix();
    
    //-------------------------logo
    ofSetColor(255);
    logoImg.draw(ofGetWidth()/2-logoImg.getWidth()/5, 50, logoImg.getWidth()/2.5, logoImg.getHeight()/2.5);
    
    if(action == COUNTDOWN) {
        ofSetColor(30,100);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }else if(action == TAKE_PHOTO) {
        ofSetColor(255,200);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    ofSetColor(255);
    string text;
    text = ofToString(counterIndex);
    float fontW = font.stringWidth(text);
    float fontH = font.stringHeight(text);
    if(action == COUNTDOWN && takePhotoIndex == -1) font.drawString(text, ofGetWidth()/2-fontW/2, ofGetHeight()/2+100);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_LEFT) {
        dirLoadIndex--;
        if (dirLoadIndex<0) {
            dirLoadIndex=dir.size()-1;
        }
        loadLUT(dir.getPath(dirLoadIndex));
    }
    
    if (key == OF_KEY_RIGHT) {
        dirLoadIndex++;
        if (dirLoadIndex>=(int)dir.size()) {
            dirLoadIndex=0;
        }
        loadLUT(dir.getPath(dirLoadIndex));
    }
    
    if(key == ' '){
        if (action == STAND_BY) {
            action = COUNTDOWN;
            for (int i=0; i<frames.size(); i++) {
                frames[i].reset();
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::takePhoto(){

    switch (action) {
        case COUNTDOWN:{
            if (takePhotoIndex  == -1 && ofGetElapsedTimeMillis() - timer > 1000 ) {
                counterIndex ++;
                timer = ofGetElapsedTimeMillis();
            }else if(takePhotoIndex  != -1 && ofGetElapsedTimeMillis() - timer > 200 ){
                counterIndex ++;
                timer = ofGetElapsedTimeMillis();
            }
            
            if (counterIndex > 3) {
                counterIndex = 0;
                action = TAKE_PHOTO;
            }
            
        }
        break;
            
        case TAKE_PHOTO:{
            
            takePhotoIndex ++;
            if (takePhotoIndex > 4) {
                frames[takePhotoIndex].update();
                takePhotoIndex = -1;
                action = STAND_BY;
            }else{
                frames[takePhotoIndex].update();
                action = COUNTDOWN;
            }
            
        }
        break;
            

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

//--------------------------------------------------------------
void ofApp::loadLUT(string path){
	LUTloaded=false;
	
	ofFile file(path);
	string line;
	for(int i = 0; i < 5; i++) {
		getline(file, line);
		ofLog() << "Skipped line: " << line;
	}
	for(int z=0; z<32; z++){
		for(int y=0; y<32; y++){
			for(int x=0; x<32; x++){
				ofVec3f cur;
				file >> cur.x >> cur.y >> cur.z;
				lut[x][y][z] = cur;
			}
		}
	}
	
	LUTloaded = true;
}
//--------------------------------------------------------------
void ofApp::applyLUT(ofPixelsRef pix){
	
    if (LUTloaded) {
		
		for(int y = 0; y < pix.getHeight(); y++){
			for(int x = 0; x < pix.getWidth(); x++){
				
				ofColor color = pix.getColor(x, y);
				
				int lutPos [3];
				for (int m=0; m<3; m++) {
					lutPos[m] = color[m] / 8;
					if (lutPos[m]==31) {
						lutPos[m]=30;
					}
				}
				
				ofVec3f start = lut[lutPos[0]][lutPos[1]][lutPos[2]];
				ofVec3f end = lut[lutPos[0]+1][lutPos[1]+1][lutPos[2]+1];
				
				for (int k=0; k<3; k++) {
					float amount = (color[k] % 8) / 8.0f;
					color[k]= (start[k] + amount * (end[k] - start[k])) * 255;
				}
				
				lutImg.setColor(x, y, color);
				
			}
		}
		
		lutImg.update();
	}
}

//--------------------------------------------------------------
void ofApp::setupLUT(){

    dir.allowExt("cube");
	dir.listDir("LUTs/");
    dir.sort();
    if (dir.size()) {
        dirLoadIndex=4;
		loadLUT(dir.getPath(dirLoadIndex));
    }
    
    lutImg.allocate(640, 480, OF_IMAGE_COLOR);
    lutPos.set(ofGetWidth()/2,ofGetHeight()/2);

}

//--------------------------------------------------------------
void ofApp::loadImages(){

    logoImg.loadImage("image/kiehlsLogo.png");
    frameImg.loadImage("image/frame.png");

}


