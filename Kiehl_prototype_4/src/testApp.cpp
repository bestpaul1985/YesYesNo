#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(230);

    height = 1920/2;
    width = 1080/2;
    
    loadPicture();

    int num = 5;
    int offSet = 1;
    int imgW = 156/2;
    int imgH = 186/2;

    //----------------------------------SETUP PIC
    for (int i=0; i<8; i++) {
        for (int j=0; j<10; j++) {
            picture temp;
            pics.push_back(temp);
            pics[pics.size()-1].init(offSet*i+imgW*i,banner.height/2+offSet*j+imgH*j, imgW, imgH);
            pics[pics.size()-1].shadow = &shadow;
            pics[pics.size()-1].picture = &images[ofRandom(0,images.size())];
            
            cout<<ofRandom(0,images.size())<<endl;

        }
    }
    
    
}

//--------------------------------------------------------------
void testApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    bool bPhotoSelected = false;
    for (int i=0; i<pics.size(); i++) {
        if (pics[i].bSelected) {
            bPhotoSelected = true;
            picture temp;
            temp = pics[i];
            pics.erase(pics.begin()+i);
            pics.insert(pics.begin(), temp);
            for (int j=0; j<pics.size(); j++) {
                if (j != i) {
                    pics[j].bFixed = true;
                }
            }
            break;
        }
    }
    
    if (!bPhotoSelected) {
        for (int j=0; j<pics.size(); j++) {
            pics[j].bFixed = false;
        }
    }
    
   
    for (int i=pics.size()-1; i>=0; i--) {
        pics[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i=pics.size()-1; i>=0; i--) {
        pics[i].draw();
    }
    
    ofSetColor(255);
    banner.draw(0, 0, banner.width/2,banner.height/2);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
    for (int i=0; i<pics.size(); i++) {
        pics[i].mouseMoved(x,y);
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for (int i=0; i<pics.size(); i++) {
        pics[i].mousePressed(x,y);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    for (int i=0; i<pics.size(); i++) {
        pics[i].mouseReleased(x,y);
    }
    
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
void testApp::loadPicture(){
    
    shadow.loadImage("shadow.png");
    banner.loadImage("banner.png");
    
    ofDirectory dir;
    int nFiles = dir.listDir("image");
    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
        }
        
    }

}












