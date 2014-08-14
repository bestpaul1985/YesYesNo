
#include "scene02.h"

//--------------------------------------------------------------
void scene02::setup(){
    
    photoAction = STAND_BY;
    counter = -1;
#ifdef _USE_4k_SCREEN
    camWidth = 640;
    camHeight = 480;
    ps3eye.initGrabber(camWidth, camHeight);

    //---------------------------LUT
    dir.allowExt("cube");
	dir.listDir("LUTs/");
	dir.sort();
    dirLoadIndex=0;
    loadLUT(dir.getPath(dirLoadIndex));
	
	lutImg.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    lutPos.set(-lutImg.getWidth()*0.5f, lutImg.getHeight()*0.5f, 0);
    
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    grabWidth = 480;
    grabHeight = 480;
    
    //------------------------taking photo
    motor.loadImage("images/DL1000A_L4_RED_FRONT.png");
    countImage[0].loadImage("number1.png");
    countImage[1].loadImage("number2.png");
    countImage[2].loadImage("number3.png");
    color.set(255,0);
    
    //----------------------shader
    shader.load("photobooth_shaders/noise.vert", "photobooth_shaders/noise.frag");
    myFbo.allocate(camHeight,camWidth, GL_RGBA, 4);
    shaderFbo.allocate(camHeight, camWidth, GL_RGBA, 4);
    
#else
    camWidth = 960;
    camHeight = 540;
    //---------------------------LUT
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
    //------------------------------video grabber
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
    
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
    
    grabWidth = 520;
    grabHeight = 520;
    
    photoData 	= new unsigned char[grabWidth*grabHeight*3];
    grabTexture.allocate(2160, 2160,GL_RGB);
    
    //------------------------taking photo
    motor.loadImage("images/DL1000A_L4_RED_FRONT.png");
    countImage[0].loadImage("number1.png");
    countImage[1].loadImage("number2.png");
    countImage[2].loadImage("number3.png");
    color.set(255,0);
    
    //----------------------shader
    shader.load("photobooth_shaders/noise.vert", "photobooth_shaders/noise.frag");
    myFbo.allocate(camWidth, camHeight, GL_RGBA, 4);
    shaderFbo.allocate(camWidth, camHeight, GL_RGBA, 4);
    
#endif
    
  
    
    

}

//--------------------------------------------------------------
void scene02::update(){
#ifdef _USE_4k_SCREEN
    
     ps3eye.update();
    if( ps3eye.isFrameNew() ){
        applyLUT(ps3eye.getPixelsRef());
    }
    
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
#else
    
    vidGrabber.update();
    if (vidGrabber.isFrameNew()){
        applyLUT(vidGrabber.getPixelsRef());
    }
    
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

#endif
   
    
    
}

//--------------------------------------------------------------

void scene02::draw(){
    ofSetColor(255);
    
   
    
  
#ifdef _USE_4k_SCREEN
  
    myFbo.begin();
    
    ofPushMatrix();
    ofTranslate(camHeight*0.5f, camWidth*0.5f);
    ofRotateZ(90);
    ofSetColor(255);
    lutImg.draw(-camWidth*0.5f, camHeight*0.5f, camWidth, -camHeight);
    ofPopMatrix();
    myFbo.end();
    
    ofSetColor(255);
    myFbo.draw(0, 0);
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255);
    float scale = 4;
    myFbo.getTextureReference().drawSubsection((ofGetWidth()-grabWidth*scale)*0.5f, 800, grabWidth*scale, grabWidth*scale, 0, 0, grabWidth, grabWidth);
    
    
    
    ofSetColor(color);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f+900);
    ofSetColor(255);
    float size = 1.0f;
    motor.draw(-motor.getWidth()*size/2, -motor.getHeight()*size/2, motor.getWidth()*size, motor.getHeight()*size);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, 400);
    if (counter>=0 && counter<=2) {
        float size = 1.0f;
        countImage[counter].draw(-countImage[counter].getWidth()*size/2, -countImage[counter].getHeight()*size/2, countImage[counter].getWidth()*size, countImage[counter].getHeight()*size);
    }
    ofPopMatrix();
    
    
#else
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    myFbo.begin();
    
    ofPushMatrix();
    ofTranslate(height*0.5f, width*0.5f);
    ofRotateZ(90);
    ofSetColor(255);
    lutImg.draw(-camWidth*0.5f, camHeight*0.5f, camWidth, -camHeight);
    ofPopMatrix();
    
    myFbo.end();
    
    ofSetColor(255);
    myFbo.draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f);
    ofRotateZ(90);
    ofSetColor(255);
    grabTexture.draw(-grabTexture.getWidth()/2, grabTexture.getHeight()/2, grabTexture.getWidth(), -grabTexture.getHeight());
    ofPopMatrix();
    
    ofSetColor(color);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5f, ofGetHeight()*0.5f+900);
    ofSetColor(255);
    float size = 1.0f;
    motor.draw(-motor.getWidth()*size/2, -motor.getHeight()*size/2, motor.getWidth()*size, motor.getHeight()*size);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, 100);
    if (counter>=0 && counter<=2) {
        float size = 1.0f;
        countImage[counter].draw(-countImage[counter].getWidth()*size/2, -countImage[counter].getHeight()*size/2, countImage[counter].getWidth()*size, countImage[counter].getHeight()*size);
    }
    ofPopMatrix();
#endif
    

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
            
        case ' ':
           
            if (photoAction == STAND_BY) {
                photoAction = COUNT_DOWN;
            }
            
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






