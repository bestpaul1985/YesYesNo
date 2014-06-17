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
            frames.back().picName = "Puppy";
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

    Angle =0;
    frameWidth= 0;
    frameStyle = 0;
    shadowNum = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if (frames.size()>0) {
        frames.back().setPos(mouseX, mouseY);
        frames.back().setAngle(Angle);
        frames.back().setWidth(frameWidth);
    }
    
    for (int i=0; i<frames.size();i++){
        frames[i].update();
    }
    
    sortPicture();
    sortSelectPicture();
    
    for (int i=0; i<drawFrames.size();i++){
        drawFrames[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    for (int i=0; i<drawFrames.size();i++){
        if (!drawFrames[i].isSelected()) {
            
            drawFrames[i].draw();
            
        }
    }
    
    for (int i=0; i<drawFrames.size();i++){
        if (drawFrames[i].isSelected()) {
            drawFrames[i].draw();
        }
    }
    
    ofSetColor(255);
    banner.draw(0, 0, banner.width/2,banner.height/2);

    if (frames.size()>0) {
        string info =  "INFO : \n";
        info += "width = "+ ofToString(frames.back().getWidth())+"\n";
        info += "Level = "+ ofToString(frames.back().getLevel())+"\n";
        info += "Angle = "+ ofToString(frames.back().getAngle())+"\n";
        info += "Style = "+ ofToString(frames.back().getStyle())+"\n";
        ofSetColor(255);
        ofDrawBitmapString(info, 20,20);
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
   
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
    
    
    if(key == 'r')
    {
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
    }
    
   
    
    if (frames.size()>0) {
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
            drawFrames[i].mouseMoved(x, y);
        }
    }
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
   
    for (int i =0; i<frames.size(); i++) {
        drawFrames[i].mousePressed(x, y);
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

    if(drawFrames.size() != frames.size() ){
        drawFrames.clear();
        for (int i=0; i<10; i++) {
            for (int j=0; j<frames.size();j++){
                if (frames[j].getLevel() == i) {
                    drawFrames.push_back(frames[j]);
                }
            }
        }
    }
  
    
}


//--------------------------------------------------------------
void testApp::sortSelectPicture(){

    for (int i = drawFrames.size()-1; i>=0; i--) {
        if (drawFrames[i].isMouseOver()) {
            
            drawFrames[i].setSelected(true);
            for (int j = 0; j<drawFrames.size(); j++) {
                if (j!=i) {
                    drawFrames[j].setSelected(false);
                }
            }
            return;
            
        }
    }
    
  
}
//--------------------------------------------------------------
bool testApp::isAnimation(){

    int num = 0;
    for(int i=0; i < drawFrames.size(); i++){
        if (drawFrames[i].isAnimating()) {
            return true;
        }
    }
    
    return false;
}






