//
//  mouseControl.cpp
//  Kiehls_GlobalVideoWall_07
//
//  Created by Peng Cheng on 9/1/14.
//
//

#include "mouseControl.h"
#include "ofApp.h"


mouseControl::mouseControl(){
    dragDx = 0;
}

//--------------------------------------------------------------
void mouseControl::update(){
    
    dragDx *= 0.97;
    ofApp * app = (ofApp *)ofGetAppPtr();
    
    for (int i=0; i< ((startScene*)(app->myScene[0]))->buttons.size(); i++) {
         ((startScene*)(app->myScene[0]))->buttons[i].pos.x += dragDx* ((startScene*)(app->myScene[0]))->buttons[i].xSpeed;
    }
    
}

//--------------------------------------------------------------
void mouseControl::keyPressed(int key){
    
}

//--------------------------------------------------------------
void mouseControl::keyReleased(int key){
    
}

//--------------------------------------------------------------
void mouseControl::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void mouseControl::mouseDragged(int x, int y, int button){
    
    currentMouse.set(x,y);
    ofPoint diff = currentMouse - preMouse;
    dragDx = 0.9f * dragDx + 0.1f * diff.x;
    preMouse= currentMouse;
    
}

//--------------------------------------------------------------
void mouseControl::mousePressed(int x, int y, int button){
    
    preMouse.set(x, y);
}

//--------------------------------------------------------------
void mouseControl::mouseReleased(int x, int y, int button){
    
}





