#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    logoImg.loadImage("image/logo.png");
    frameImg.loadImage("image/frame.png");
    
    ofBackground(0);
	ofSetColor(255);
    
    buttonPos.set(ofGetWidth()/2,ofGetHeight()-100);
    buttonRadius = 30;
    buttonColor.set(255);
    
    timer = ofGetElapsedTimeMillis();
    
    font.loadFont("verdana.ttf", 70);
    takePhotoIndex = 0;
    action = STAND_BY;
    
    
    grabPhoto.allocate(400, 500, GL_RGB);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){


    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        applyLUT(vidGrabber.getPixelsRef());
    }
    
//    grabPhoto.loadScreenData(ofGetWidth()/2,ofGetHeight()/2,300,300);

    
    takePhoto();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    ofTranslate(lutPos);
    ofSetColor(255);
    lutImg.draw(lutImg.getWidth()/2,-lutImg.getHeight()/2,-lutImg.getWidth(),lutImg.getHeight());
    ofPopMatrix();
    
    ofSetColor(255);
    vidGrabber.draw(thumbPos.x+160, thumbPos.y, -160, 120);

    ofSetColor(255);
//    grabPhoto.draw(200,200,200,200);
    
    ofSetColor(buttonColor);
    ofCircle(buttonPos, buttonRadius);
    
    ofSetColor(255);
    string number = ofToString(takePhotoIndex);
    font.drawString(number, ofGetWidth()/2-font.stringWidth(number)/2, ofGetHeight()/2+font.stringHeight(number)/2);
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
    
}
//--------------------------------------------------------------
void ofApp::takePhoto(){

    switch (action) {
        case COUNTDOWN:{
            if (ofGetElapsedTimeMillis() - timer > 1000 ) {
                takePhotoIndex ++;
                timer = ofGetElapsedTimeMillis();
            }
            
            if (takePhotoIndex > 3) {
                takePhotoIndex = 0;
                action = TAKE_PHOTO;
            }
            
        }
        break;
            
        case TAKE_PHOTO:{
          
//            unsigned char *lutPix = lutImg.getPixels();
//            unsigned char *photoPix = photo.getPixels();
//
//            for (int i=0; i<lutImg.width; i++) {
//                for (int j = 0; j<lutImg.height; j++) {
//                    
//                    int ii = j * lutImg.width + i;
//                    ofColor colro = ofColor( lutPix[ii*3], lutPix[ii*3+1], lutPix[ii*3+2] );
//
//                    photoPix[ ii * 3 ] = colro.r;
//                    photoPix[ ii * 3 + 1] = colro.g;
//                    photoPix[ ii * 3 + 2] = colro.b;
//                }
//            }
//            photo.update();
//            action = STAND_BY;
        }
        break;
            
            cout<<takePhotoIndex<<endl;

    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    ofPoint mouse(x,y);
    if (mouse.distance(buttonPos)<=buttonRadius) {
        buttonColor.set(200);
    }else{
        buttonColor.set(255);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    ofPoint mouse(x,y);
    if (mouse.distance(buttonPos)<=buttonRadius) {
        buttonColor.set(30);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    ofPoint mouse(x,y);
    if (mouse.distance(buttonPos)<=buttonRadius) {
        buttonColor.set(255);
        timer = ofGetElapsedTimeMillis();
        action = COUNTDOWN;
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
    vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(640,480);
    
    thumbPos.set(ofGetWidth()-200,50);
	lutPos.set(ofGetWidth()/2,ofGetHeight()/2, 0);

    

}


