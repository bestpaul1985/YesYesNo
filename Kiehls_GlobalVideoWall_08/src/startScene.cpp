#include "startScene.h"

//--------------------------------------------------------------
void startScene::setup(){
   
    bgImage.loadImage("images/bg.png");
    loadXML();
    width = 2160/4;
    height = 3840/4;

    bDragged = false;
}

//--------------------------------------------------------------
void startScene::update(){
    
    for (int i=0; i< buttons.size(); i++) {
        buttons[i].update();
    }
    
}

//--------------------------------------------------------------
void startScene::draw(){
    
    ofSetColor(255);
    bgImage.draw(0,0,width,height);
    for (int i=0; i< buttons.size(); i++) {
        buttons[i].draw();
    }
}

//--------------------------------------------------------------
void startScene::loadXML(){

    XML.load("mySettings.xml");
    
    for (int i=0; i<9; i++) {
        ofImage temp;
        temp.loadImage("dogs2/"+ofToString(i)+".png");
        dogImages.push_back(temp);
    }
    
    int i= 0;
    if(XML.getName() == "PHOTO" && XML.setTo("val[0]"))
    {
        do {
            button  tempPhoto;
            buttons.push_back(tempPhoto);
            int x = int(XML.getValue<float>("X")*ofGetWidth());
            int y = int(XML.getValue<float>("Y")*ofGetHeight());
            int angle = int(XML.getValue<int>("ANGLE"));
            
            if (i>dogImages.size()-1) {
                i = 0;
            }
            buttons.back().setup(dogImages[i], x , y, angle);
            i++;
        }
        while(XML.setToSibling());
        XML.setToParent();
    }

}
//--------------------------------------------------------------
void startScene::keyPressed(int key){
    
}

//--------------------------------------------------------------
void startScene::keyReleased(int key){
    
}

//--------------------------------------------------------------
void startScene::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void startScene::mouseDragged(int x, int y, int button){
    
    
    currentMouse.set(x, y);
    ofPoint diff = currentMouse - preMouse;
    if (diff.length()>0) {
        bDragged = true;
    }
    
    if (!isButtonSelected()) {
        for (int i=0; i<buttons.size(); i++) {
            buttons[i].dragDx = 0.9f *  buttons[i].dragDx + 0.1f * diff.x;
        }
    }
    
    preMouse = currentMouse;
}

//--------------------------------------------------------------
void startScene::mousePressed(int x, int y, int button){
    
    preMouse.set(x, y);
    bDragged = false;
  
}

//--------------------------------------------------------------
void startScene::mouseReleased(int x, int y, int button){
    
    if (!bDragged && !isButtonSelected()) {
        for (int i=0; i<buttons.size(); i++) {
            ofVec3f mouse(x,y,0);
            ofMatrix4x4 matrix;
            matrix.glTranslate( buttons[i].pos.x, buttons[i].pos.y, 0 );
            matrix.glRotate( buttons[i].angle, 0, 0, 1 );
            mouse = mouse*matrix.getInverse();
            if (buttons[i].rect.inside(mouse)) {
                buttons[i].bMousePressed = true;
                break;
            }
        }
    }
    
}

//--------------------------------------------------------------
void startScene::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void startScene::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void startScene::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
bool startScene::isButtonSelected(){

    for (int i=0; i<buttons.size(); i++) {
        if(buttons[i].bMousePressed){
            return true;
        }
    }
    
    return false;
    
}












