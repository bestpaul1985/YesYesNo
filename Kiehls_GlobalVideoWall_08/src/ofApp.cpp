#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    myScene[0] = new startScene();
    currentScene = 0;
    
    for (int i=0; i<SCENE_NUM; i++) {
        myScene[currentScene]->setup();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    myScene[currentScene]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    myScene[currentScene]->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

     myScene[currentScene]->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    myScene[currentScene]->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    myScene[currentScene]->mouseMoved(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    myScene[currentScene]->mouseDragged(x, y, button);


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    myScene[currentScene]->mousePressed(x, y, button);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    myScene[currentScene]->mouseReleased(x, y, button);

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
