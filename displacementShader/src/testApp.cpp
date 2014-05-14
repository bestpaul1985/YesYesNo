#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    lineFbo.allocate(1024, 768, GL_RGBA, 4);
    rockImage.loadImage("stone_rocky_surface_texture.jpg");
    shader.load("shader/shader");
}

//--------------------------------------------------------------
void testApp::update(){

    
    if (ofGetFrameNum() % 30 == 0) shader.load("shader/shader");;
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(255);
    
    
    lineFbo.begin();
    ofSetLineWidth(5);
    ofClear(255,255,255,255);
    ofSetColor(0);
    line.draw();
    lineFbo.end();
    
    
    shader.begin();
    
    shader.setUniformTexture("tex0",lineFbo, 0 );
    shader.setUniformTexture("tex1",rockImage.getTextureReference(), 1 );
    
    ofSetColor(255);
    lineFbo.draw(0,0);
    shader.end();
    
   
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    line.addVertex(ofPoint(x,y));
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    line.clear();
    line.addVertex(ofPoint(x,y));
    
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
