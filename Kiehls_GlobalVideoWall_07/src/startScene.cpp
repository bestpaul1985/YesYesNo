#include "startScene.h"

//--------------------------------------------------------------
void startScene::setup(){
   
    bgImage.loadImage("images/bg.png");
    loadXML();
    width = 2160/4;
    height = 3840/4;
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
    
    for (int i=0; i<15; i++) {
        ofImage temp;
        temp.loadImage("dogs/"+ofToString(i)+".png");
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
    
}

//--------------------------------------------------------------
void startScene::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void startScene::mouseReleased(int x, int y, int button){
    
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
