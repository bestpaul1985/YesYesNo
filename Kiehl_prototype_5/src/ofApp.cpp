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
    font.loadFont("verdana.ttf", 70);
    takePhotoIndex = 0;
    action = STAND_BY;
    
//    grabTexture.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(),GL_RGB);
//    grabPhoto.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), OF_IMAGE_COLOR_ALPHA);

}

//--------------------------------------------------------------
void ofApp::update(){

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
    
    if(action != STAND_BY){
        ofSetColor(255);
        string number = ofToString(takePhotoIndex);
        font.drawString(number, ofGetWidth()/2-font.stringWidth(number)/2, ofGetHeight()/2+font.stringHeight(number)/2);
    }
   
   
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255);
    grabTexture.draw(-frameImg.getWidth()/6,-frameImg.getHeight()/6,frameImg.getWidth()/3,frameImg.getHeight()/3);
    float W = ofMap(frameImg.getHeight()/3, 0, grabPhoto.getHeight(), 0, grabPhoto.getWidth());
    grabPhoto.draw(W/2, -frameImg.getHeight()/6, -W, frameImg.getHeight()/3);
    frameImg.draw(-frameImg.getWidth()/6,-frameImg.getHeight()/6,frameImg.getWidth()/3,frameImg.getHeight()/3);
    ofPopMatrix();
    
    ofSetColor(255);
    logoImg.draw(ofGetWidth()/2-logoImg.getWidth()/4, 50, logoImg.getWidth()/2, logoImg.getHeight()/2);
    
    cout<<mouseX<<" "<<mouseY<<endl;
    
    ofSetColor(255);
    string text;
    text = ofToString(takePhotoIndex);
    float fontW = font.stringWidth(text);
    float fontH = font.stringHeight(text);
    if(action == COUNTDOWN) font.drawString(text, ofGetWidth()/2-fontW/2, ofGetHeight()/2 + fontH/2);
    
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
        }
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
            
            unsigned char *vedioPix = lutImg.getPixels();
            unsigned char *imagePix = grabPhoto.getPixels();
            
            for (int i=0; i<lutImg.getWidth(); i++) {
                for (int j=0; j<lutImg.getHeight(); j++) {
                    
                    int ii = j*lutImg.getWidth()+i;
                    
                    if (i >= 160 && i<= 480) {
                        ofColor color = ofColor( vedioPix[ii*3], vedioPix[ii*3+1], vedioPix[ii*3+2], 255);
                        imagePix[ii*4]= color.r;
                        imagePix[ii*4+1]= color.g;
                        imagePix[ii*4+2]= color.b;
                        imagePix[ii*4+3]= color.a;
                    }else{
                        ofColor color(0,0);
                        imagePix[ii*4]= color.r;
                        imagePix[ii*4+1]= color.g;
                        imagePix[ii*4+2]= color.b;
                        imagePix[ii*4+3]= color.a;
                    }
                }
            }
            grabPhoto.update();
            action = STAND_BY;
            
            
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


