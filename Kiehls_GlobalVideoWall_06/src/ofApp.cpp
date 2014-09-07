#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    background.loadImage("images/bg.png");
    photoBG.loadImage("images/photoBG.png");
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
            photo  tempPhoto;
            myPhotos.push_back(tempPhoto);
            int x = int(XML.getValue<float>("X")*ofGetWidth());
            int y = int(XML.getValue<float>("Y")*ofGetHeight());
            int angle = int(XML.getValue<int>("ANGLE"));
            
            if (i>dogImages.size()-1) {
                i = 0;
            }
            myPhotos.back().setup(dogImages[i], x , y, angle);
            i++;
        }
        while(XML.setToSibling());
        XML.setToParent();
    }

    bFix = false;
    
    int earthX = 1832/4;
    int earthY = 1046/4;
    earthPos.set(earthX, earthY);
    earthRadius = 640/4;
}


float dragDx = 0;
//--------------------------------------------------------------
void ofApp::update(){

    
    dragDx *= 0.97;
    
    if (true) {
        for (int i=0; i< myPhotos.size(); i++) {
            myPhotos[i].pos.x += dragDx * myPhotos[i].xSpeed;
        }
    }
    
    if (bFix && myPhotos.size()>0) {
        myPhotos.back().pos.set(mouseX,mouseY);
    }
    
    for (int i=0; i<myPhotos.size(); i++) {
        if (myPhotos[i].pos.x < -myPhotos[i].photoW*0.5f) {
            myPhotos[i].pos.x = ofGetWidth()+myPhotos[i].photoW*0.5f;
        }
        
        else if (myPhotos[i].pos.x > ofGetWidth()+myPhotos[i].photoW*0.5f) {
            myPhotos[i].pos.x = -myPhotos[i].photoW*0.5f;
        }
        
        
        float xPct = ofMap( myPhotos[i].pos.x, 0, ofGetWidth(), 0, 1, true);
        float xPctShaped = powf(xPct, 3.0);
        
        myPhotos[i].pos.y = ofMap(xPctShaped, 0, 1, myPhotos[i].orgY, ofGetHeight()/3 + 2*myPhotos[i].orgY/3.0);
        
        
        myPhotos[i].angle = ofMap(xPct, 0, 1, myPhotos[i].startAngle, myPhotos[i].endAngle);
        
    }
}

//---------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    background.draw(0, 0, ofGetWidth(),ofGetHeight());
    
    for (int i=0; i< myPhotos.size(); i++) {
        myPhotos[i].draw();
    }
    
//    ofSetColor(255, 0, 220, 150);
//    ofCircle(earthPos, earthRadius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'f') {
        ofToggleFullscreen();
    }
    
    if (key == ' ') {
        bFix = !bFix;
    }
    
    if (key == 'r') {
        int x = mouseX;
        int y = mouseY;
        int level = 0;
        photo  myPhoto;
        myPhotos.push_back(myPhoto);
        myPhotos.back().setup(photoBG, x , y, 0);
        myPhotos.back().level = level;
    }
    
    if (key == 'd') {
        myPhotos.back().angle++;
    }

    if (key == 'a') {
        myPhotos.back().angle--;
    }
    
    if (key == 'w') {
        myPhotos.back().pos.z++;
    }
    
    if (key == 's') {
        myPhotos.back().pos.z--;
    }
    
    if (key == 'z'&& myPhotos.size()>0) {
         myPhotos.erase(myPhotos.end());
    }
    
    if(key == 'p')
    {
        XML.clear();
        XML.addChild("PHOTO");
        for (int i=0; i<myPhotos.size(); i++) {
            XML.reset();
            ofXml point;
            point.addChild("val");
            point.setTo("val");
            point.addValue("X", myPhotos[i].pos.x/ofGetWidth());
            point.addValue("Y", myPhotos[i].pos.y/ofGetHeight());
            point.addValue("ANGLE", myPhotos[i].angle);
            XML.addXml(point);
        }
        
        XML.save("mySettings.xml");
        cout<< "settings saved to xml!" <<endl;
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

    ofPoint currentMouse(x,y);
    ofPoint diff = currentMouse - preMouse;
    
    dragDx = 0.9f * dragDx + 0.1f * diff.x;
    
    preMouse = currentMouse;
    
    cout<<diff <<"  "<< dragDx<<endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    preMouse.set(x, y);
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
