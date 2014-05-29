#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(60);

    height = 1920/2;
    width = 1080/2;
    
    int rowNum = 5;
    int offSet = 2;
    int imgW = (ofGetWidth() - offSet*(rowNum-1))/rowNum;
    int imgH = imgW/3*4;

//    for (int i=0; i<num; i++) {
//        for (int j=0; j<10; j++) {
//            picture temp;
//            temp.init(5*i+picW*i,5*j+picH*j, picW, picH);
//            pics.push_back(temp);
//        }
//    }
    
    ofDirectory dir;
    
    int nFiles = dir.listDir("image");
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) {
            
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            
        }
        
    }
    
    int size = images.size()%rowNum;
    for (int i=0; i<rowNum; i++) {
        for (int j=0; j<size; i++) {
            
            
            
        }
    }
    
}

//--------------------------------------------------------------
void testApp::update(){

   
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i=0; i<pics.size(); i++) {
        pics[i].draw();
    }
    
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
