//
//  scene02.cpp
//  Kiehls_GlobalVideoWall_01
//
//  Created by Peng Cheng on 8/9/14.
//
//

#include "scene02.h"

//--------------------------------------------------------------
void scene02::setup(){
    
    photoAction = STAND_BY;
    counter = 0;
    
    camWidth = 960;
    camHeight = 540;
    
    dir.allowExt("cube");
	dir.listDir("LUTs/");
	dir.sort();
    dirLoadIndex=0;
    loadLUT(dir.getPath(dirLoadIndex));
	
	lutImg.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    lutPos.set(-lutImg.getWidth()*0.5f, lutImg.getHeight()*0.5f, 0);
    
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
    
	vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(60);
    
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
    
    grabWidth = 520;
    grabHeight = 520;
    
    videoInverted 	= new unsigned char[grabWidth*grabHeight*3];
    grabTexture.allocate(grabWidth, grabHeight,GL_RGB);
    
    motor.loadImage("images/DL1000A_L4_RED_FRONT.png");
    countImage[0].loadImage("number1.png");
    countImage[1].loadImage("number2.png");
    countImage[2].loadImage("number3.png");
    
    color.set(255,0);
    
}

//--------------------------------------------------------------
void scene02::update(){
    
    vidGrabber.update();
    if (vidGrabber.isFrameNew()){
        applyLUT(vidGrabber.getPixelsRef());
        
    }
    
    int totalPixels = camWidth*camHeight*3;
    int k = 0;
    unsigned char * pixels = lutImg.getPixels();
    for (int i = 0; i < camWidth; i++){
        for (int j=0; j<camHeight; j++) {
            
            if (i > ((camWidth - grabWidth)*0.5f)  && i <= ((camWidth - grabWidth)*0.5f + grabWidth) && j > (camHeight-grabHeight)*0.5f && j <= ((camHeight-grabHeight)*0.5f+grabHeight)) {
                int ii = j * camWidth + i;
                videoInverted[k * 3] = pixels[ii * 3];
                videoInverted[k * 3 + 1] = pixels[ii * 3 + 1];
                videoInverted[k * 3 + 2] = pixels[ii * 3 + 2];
                k ++;
            }
            
        }
        
    }
    //            cout<< k <<endl;
    grabTexture.loadData(videoInverted, grabWidth,grabHeight, GL_RGB);
    
    if (photoAction == COUNT_DOWN) {
        
        if (ofGetElapsedTimeMillis() - photoTimer > 1000) {
            counter ++;
            photoTimer = ofGetElapsedTimeMillis();
        }
        
        if (counter  > 2) {
            photoAction = TAKING;
            photoTimer = ofGetElapsedTimeMillis();
            color.set(255,200);
        }
        
    }
    
    
    if (photoAction == TAKING) {
        if (ofGetElapsedTimeMillis() - photoTimer > 50) {
            photoAction = DONE;
        }
    }

    
    
}

//--------------------------------------------------------------

void scene02::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f, 0);
    ofRotateZ(90);
    ofSetColor(255);
    lutImg.draw(lutPos.x, lutPos.y, camWidth, -camHeight);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f);
    ofSetColor(220);
    grabTexture.draw(-grabTexture.getWidth()/2, -grabTexture.getHeight()/2);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f+300);
    ofSetColor(255);
    float size = 0.3f;
    motor.draw(-motor.getWidth()*size/2, -motor.getHeight()*size/2, motor.getWidth()*size, motor.getHeight()*size);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, 100);
    if (counter>=0 && counter<3) {
        
        float size = 0.2f;
        countImage[counter].draw(-countImage[counter].getWidth()*size/2, -countImage[counter].getHeight()*size/2, countImage[counter].getWidth()*size, countImage[counter].getHeight()*size);
    }
    ofPopMatrix();
    
    ofSetColor(color);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    
}

//--------------------------------------------------------------
void scene02::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
            dirLoadIndex++;
            if (dirLoadIndex>=(int)dir.size()) {
                dirLoadIndex=0;
            }
            loadLUT(dir.getPath(dirLoadIndex));
            
            break;
        case OF_KEY_DOWN:
            dirLoadIndex--;
            if (dirLoadIndex<0) {
                dirLoadIndex=dir.size()-1;
            }
            loadLUT(dir.getPath(dirLoadIndex));
            break;
    }

    
}

//--------------------------------------------------------------
void scene02::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void scene02::mouseMoved(int x, int y ){
    
    
}

//--------------------------------------------------------------
void scene02::mouseDragged(int x, int y, int button){
    
    
    
    
}

//--------------------------------------------------------------
void scene02::mousePressed(int x, int y, int button){
    
    
    
    
}

//--------------------------------------------------------------
void scene02::mouseReleased(int x, int y, int button){
    
    
    
}

//--------------------------------------------------------------
void scene02::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void scene02::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void scene02::dragEvent(ofDragInfo dragInfo){
    
}



//--------------------------------------------------------------
void scene02::loadLUT(string path){
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
void scene02::applyLUT(ofPixelsRef pix){
	
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
void scene02::reset(){
    
    photoAction = STAND_BY;
    counter = -1;
    color.set(255,0);
    
}






