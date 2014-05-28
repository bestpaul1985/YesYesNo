#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(60);

    height = 1920/2;
    width = 1080/2;
    
    int num = 5;
    int offSet = 5;
    int picW = (ofGetWidth() - offSet*(num-1))/num;
    int picH = picW/3*4;

    for (int i=0; i<num; i++) {
        for (int j=0; j<10; j++) {
            picture temp;
            temp.init(5*i+picW*i,5*j+picH*j, picW, picH);
            pics.push_back(temp);
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
