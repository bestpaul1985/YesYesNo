#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(230);
    
    loadPicture();
    font.loadFont("font/GillSans.ttc", 72, true, false, true, 0.1);
    
    XML.load("mySettings.xml");
  
    
        if(XML.getName() == "PHOTO" && XML.setTo("val[0]"))
        {
            do {
                Polaroidframe  photo;
                frames.push_back(photo);
                frames.back().init(XML.getValue<int>("X"),XML.getValue<int>("Y"), XML.getValue<int>("W"));
                frames.back().loadPic(images[1]);
                frames.back().setAngle(0);
                frames.back().loadFont(font);
                frames.back().picName = "Puppy";
                frames.back().cityName = "New York";
                frames.back().setLevel(XML.getValue<int>("L"));
                frames.back().setStyle(POLAROID);
            }
            while(XML.setToSibling());
            XML.setToParent();
        }
    
    cout<<frames.size()<<endl;

}

//--------------------------------------------------------------
void testApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for (int i=0; i<frames.size();i++){
        frames[i].update();
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    for (int i=0; i<frames.size();i++){
        frames[i].draw();
    }
    ofSetColor(255);
    banner.draw(0, 0, banner.width/2,banner.height/2);
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
   
    if(key == 's')
    {
       
//        XML.clear();
//        XML.addChild("PHOTO");
        XML.reset();
        ofXml point;
        point.addChild("val");
        point.setTo("val");
        
        point.addValue("X", frame.getPos().x);
        point.addValue("Y", frame.getPos().y);
        point.addValue("W", frame.getWidth());
        point.addValue("L", frame.getLevel());
        
        XML.addXml(point);
        
        XML.save("mySettings.xml");
        cout<< "settings saved to xml!" <<endl;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
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
    
    shadow.loadImage("image/shadow.png");
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

}

//--------------------------------------------------------------
void testApp::setupPicture(){

    int num = 5;
    int offSet = 1;
    int imgW = 156/2;
    int imgH = 186/2;
    
    for (int i=0; i<8; i++) {
        for (int j=0; j<10; j++) {
            picture temp;
            pics.push_back(temp);
            pics[pics.size()-1].init(offSet*i+imgW*i,banner.height/2+offSet*j+imgH*j, imgW, imgH, 0);
            pics[pics.size()-1].shadow = &shadow;
            pics[pics.size()-1].picture = &images[ofRandom(0,images.size())];
            
//            cout<<ofRandom(0,images.size())<<endl;
            
        }
    }
    
    

}











