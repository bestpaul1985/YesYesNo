#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(239,155,15);
    ofEnableAlphaBlending();

    loadPicture();
    font.loadFont("font/GillSans.ttc", 72, true, false, true, 0.1);
    
    
    XML.load("mySettings.xml");
    
    if(XML.getName() == "PHOTO" && XML.setTo("val[0]"))
    {
        do {
            Polaroidframe  photo;
            frames.push_back(photo);
            int x = int(XML.getValue<float>("X")*ofGetWidth());
            int y = int(XML.getValue<float>("Y")*ofGetHeight());
            float w = float(XML.getValue<float>("W")*ofGetWidth());
            
            frames.back().init(x,y,w);
            frames.back().loadPic(images[ofRandom(images.size())]);
            frames.back().setAngle(XML.getValue<int>("A"));
            frames.back().loadFont(font);
            frames.back().loadShadow(shadows[0]);
            frames.back().picName = "Hello";
            frames.back().cityName = "New York";
            frames.back().setLevel(XML.getValue<int>("L"));
            if (XML.getValue<int>("S") == 0) {
                frames.back().setStyle(Polaroidframe::NO_FRAME_1);
                frames.back().loadShadow(shadows[1]);
            }else if (XML.getValue<int>("S") == 1) {
                frames.back().setStyle(Polaroidframe::NO_FRAME_2);
                frames.back().loadShadow(shadows[0]);
            }else if (XML.getValue<int>("S") == 2) {
                frames.back().setStyle(Polaroidframe::FRAME);
                frames.back().loadShadow(shadows[1]);
            }else if (XML.getValue<int>("S") == 3) {
                frames.back().setStyle(Polaroidframe::POLAROID);
                frames.back().loadShadow(shadows[2]);
            }
        }
        while(XML.setToSibling());
        XML.setToParent();
    }
    sortPicture();
    
    Angle =0;
    frameWidth= 0;
    frameStyle = 0;
    shadowNum = 0;
    bTransition = false;
    enable_Debug_Mode = false;
}

//--------------------------------------------------------------
void testApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if (enable_Debug_Mode) {
        if (frames.size()>0) {
            for (int i=0; i<frames.size(); i++) {
                if (frames[i].bDebug) {
                    frames[i].setPos(mouseX, mouseY);
                    frames[i].setAngle(Angle);
                    frames[i].setWidth(frameWidth);
                }
            }
        }
        
            for (int i=0; i<frames.size();i++){
                frames[i].update();
           }
    }

    sortSelectPicture();
    
    for (int i=0; i<frames.size();i++){
        frames[i].update();
    }
    
    for (int i=0; i<frames.size(); i++) {
        if (frames[i].getTransition() == Polaroidframe::OUT_WINDOW) {
            frames[i].loadPic(images[ofRandom(images.size())]);
            frames[i].setTransition(Polaroidframe::GET_IN, frames[i].orgPos, ofRandom(14, 15));
        }
    }
    
}


ofPoint centerPos = ofPoint( 1080/4,1920/4);
ofPoint targetPos = ofPoint( 1080/4,1920/4);
//--------------------------------------------------------------
void testApp::draw(){
    
    bool bAnySelected = false;
    ofPoint selectionPoint;
    
    for (int i=0; i<frames.size();i++){
        if (frames[i].isMousepressed()) {
            bAnySelected = true;
            selectionPoint =frames[i].getPos();
        }
    }
    
    if (bAnySelected){
        ofBackground(100);
        targetPos = 0.98 * targetPos + 0.02 *selectionPoint;
    } else {
        ofBackground(150);
        targetPos = 0.98 * targetPos + 0.02 *centerPos;
    }
    
    ofPushMatrix();
    ofTranslate(-targetPos.x,-targetPos.y);
    ofTranslate(centerPos.x,centerPos.y);
    
    for (int i=0; i<frames.size();i++){
        if (!frames[i].isSelected()) {
            frames[i].draw();
        }
    }
    
    
    for (int i=0; i<frames.size();i++){
        if (frames[i].isSelected()) {
            frames[i].draw();
        }
    }
    
    ofPopMatrix();
    
  

    if (enable_Debug_Mode) {
        string info =  "INFO : \n";
        info += "space: add new frame\n";
        info += "key = 'w': width + \n";
        info += "key = 's': width - \n";
        info += "key = 'a': rotate left \n";
        info += "key = 'd': rotate right \n";
        info += "key = 'z': delete last frame \n";
        info += "number key = 1, 2, 3, 4 : level 1 - 4 \n";
        info += "key = 'e' : frame style 1 - 4 \n";
        info += "key = 'q' : shadow style 1 - 4 \n";
        info += "Level = "+ ofToString(frames.back().getLevel())+"\n";

        ofSetColor(255);
        ofDrawBitmapStringHighlight(info, 20,20);
    }else{
        ofSetColor(255);
        banner.draw(0, 0, banner.width/2,banner.height/2);
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
   
    if(key == OF_KEY_LEFT){
        for (int i=0; i<frames.size(); i++) {
            frames[i].setTransition(Polaroidframe::GET_OUT,
                                        ofPoint(-frames[i].getWidth()*1.2, ofGetHeight()/2),
                                        ofRandom(14, 20));
        }
    }
    
    if (key == ' ') {
        enable_Debug_Mode = !enable_Debug_Mode;
    }
    
    if (enable_Debug_Mode && frames.size()>0) {
        
        if (key == 'r') {
            int x = 100;
            int y = 200;
            int l = 1;
            frameWidth = 160;
            Polaroidframe  photo;
            frames.push_back(photo);
            frames.back().init(x,y,frameWidth);
            int i = (int)ofRandom(0,images.size()-1);
            frames.back().loadPic(images[i]);
            frames.back().setImageNum(i);
            
            frames.back().loadFont(font);
            frames.back().loadShadow(shadows[0]);
            
            frames.back().setAngle(0);
            frames.back().picName = "Puppy";
            frames.back().cityName = "New York";
            frames.back().setLevel(l);
            frames.back().setStyle(Polaroidframe::POLAROID);
            frames.back().loadShadow(shadows[2]);
            frames.back().bDebug = true;
            
            for (int i=0; i<frames.size()-1; i++) {
                frames[i].bDebug = false;
            }
        }
        
        if(key == 'p')
        {
            XML.clear();
            XML.addChild("PHOTO");
            for (int i=0; i<frames.size(); i++) {
                XML.reset();
                ofXml point;
                point.addChild("val");
                point.setTo("val");
                point.addValue("X", frames[i].getPos().x/ofGetWidth());
                point.addValue("Y", frames[i].getPos().y/ofGetHeight());
                point.addValue("W", frames[i].getWidth()/ofGetWidth());
                point.addValue("L", frames[i].getLevel());
                point.addValue("A", frames[i].getAngle());
                point.addValue("S", frames[i].getStyle());
                point.addValue("I", frames[i].getImageNum());
                
                XML.addXml(point);
            }
            
            XML.save("mySettings.xml");
            cout<< "settings saved to xml!" <<endl;
        }
        
        
       

        if (key == 'a') {
            
            Angle --;
        }
        
        if (key == 'd') {
            
            Angle ++;
        }
        
        
        if (key == 's') {
            
            frameWidth -=10;
        }
        
        if (key == 'w') {
            
            frameWidth+=10;
        }
        
        if (key == '1') {
            
            frames.back().setLevel(1);
            

        }
        
        if (key == '2') {
            
            frames.back().setLevel(2);
            
        }
        
        if (key == '3') {
            
            frames.back().setLevel(3);
            
        }
        
        if (key == '4') {
            
            frames.back().setLevel(4);
            
        }
        
        if (key == 'e') {
            
            frameStyle++;
            if (frameStyle >3)frameStyle =0;
            
            if (frameStyle == 0){
                frames.back().setStyle(Polaroidframe::NO_FRAME_1);
                frames.back().loadShadow(shadows[1]);
            }
            if (frameStyle == 1){
                frames.back().setStyle(Polaroidframe::NO_FRAME_2);
                frames.back().loadShadow(shadows[0]);
                
            }
            if (frameStyle == 2) {
                frames.back().setStyle(Polaroidframe::FRAME);
                frames.back().loadShadow(shadows[1]);
                
            }
            if (frameStyle == 3){
                frames.back().setStyle(Polaroidframe::POLAROID);
                frames.back().loadShadow(shadows[2]);
            }
        }
        
        if (key == 'z') {

            frames.erase(frames.end());
            
        }
        
        if (key == 'q') {
            
            shadowNum ++;
            if (shadowNum > shadows.size()-1) {
                shadowNum = 0;
            }
            frames.back().loadShadow(shadows[shadowNum]);
            
        }

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    for (int i =0; i<frames.size(); i++) {
        if (!isAnimation()) {
            frames[i].mouseMoved(x, y);
        }
    }
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
   
    for (int i =0; i<frames.size(); i++) {
        frames[i].mousePressed(x, y);
    }
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

//--------------------------------------------------------------
void testApp::loadPicture(){
    
    banner.loadImage("image/banner.png");
    
    ofDirectory dir;
    int nFiles = dir.listDir("image/photos");
    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
        }
        
    }
    
    nFiles = dir.listDir("image/shadows");
    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            shadows.push_back(ofImage());
            shadows.back().loadImage(filePath);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::sortPicture(){

    vector<Polaroidframe> drawFrames;
    
    for (int i=0; i<10; i++) {
        for (int j=0; j<frames.size();j++){
            if (frames[j].getLevel() == i) {
                drawFrames.push_back(frames[j]);
            }
        }
    }
  
    frames.clear();
    
    for (int i=0; i<drawFrames.size();i++){
        frames.push_back(drawFrames[i]);
    }

    
}


//--------------------------------------------------------------
void testApp::sortSelectPicture(){

    for (int i = frames.size()-1; i>=0; i--) {
        if (frames[i].isMouseOver()) {
            
            frames[i].setSelected(true);
            for (int j = 0; j<frames.size(); j++) {
                if (j!=i) {
                    frames[j].setSelected(false);
                }
            }
            return;
            
        }
    }
    
  
}
//--------------------------------------------------------------
bool testApp::isAnimation(){

    int num = 0;
    for(int i=0; i < frames.size(); i++){
        if (frames[i].isMousepressed()) {
            return true;
        }
    }
    
    return false;
}






