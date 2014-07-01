#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    background.loadImage("takephoto01.png");
    button01.loadImage("button01.png");
    button02.loadImage("button02.png");
    
    buttonPos01.set(20, 450);
    buttonPos02.set(ofGetWidth()/2, 650);
    bButton01 = false;
    bButton02 = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    background.draw(0, 0, ofGetWidth(),ofGetHeight());
  
    stroke.draw();
   
    if (stroke.getVertices().size()>0) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        vector < ofPoint > pts = stroke.getVertices();
        
        for (int i = 0; i < pts.size(); i++){
            
            int i_m_1 = MAX(i-1,0);
            int i_p_1 = MIN(i+1, pts.size()-1);
            
            ofPoint pta = pts[i_m_1];
            ofPoint ptb = pts[i];
            ofPoint ptc = pts[i_p_1];
            
            ofPoint diff = ptc - pta;
            
            float angle = atan2(diff.y, diff.x);
            
            angle += PI/2;
            
            float width = 2; //diff.length();
            
            ofPoint offsetA;
            offsetA.x = ptb.x + width * cos(angle);
            offsetA.y = ptb.y + width * sin(angle);
            
            ofPoint offsetB;
            offsetB.x = ptb.x - width * cos(angle);
            offsetB.y = ptb.y - width * sin(angle);
            
            ofLine(offsetA, offsetB);
            mesh.addVertex(offsetA);
            mesh.addVertex(offsetB);
            
        }
        
        // draw the mesh
        ofEnableAlphaBlending();
        ofSetColor(30,30,30);
        ofFill();
        mesh.draw();
        ofCircle(pts[0].x,pts[0].y,2);
        ofCircle(pts[pts.size()-1].x,pts[pts.size()-1].y,2);
    }
   
    
    
    
    
    for (int i=0; i<strokes.size(); i++) {
        
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        vector < ofPoint > pts = strokes[i].getVertices();
        
        for (int i = 0; i < pts.size(); i++){
            
            int i_m_1 = MAX(i-1,0);
            int i_p_1 = MIN(i+1, pts.size()-1);
            
            ofPoint pta = pts[i_m_1];
            ofPoint ptb = pts[i];
            ofPoint ptc = pts[i_p_1];
            
            ofPoint diff = ptc - pta;
            
            float angle = atan2(diff.y, diff.x);
            
            angle += PI/2;
            
            float width = 2; //diff.length();
            
            ofPoint offsetA;
            offsetA.x = ptb.x + width * cos(angle);
            offsetA.y = ptb.y + width * sin(angle);
            
            ofPoint offsetB;
            offsetB.x = ptb.x - width * cos(angle);
            offsetB.y = ptb.y - width * sin(angle);
            
            ofLine(offsetA, offsetB);
            
            //ofColor col;
            //col.setHsb(ofMap(angle, -PI/2, 3*PI/2, 0,255, true), 100,255, ofMap(angle, -PI/2, 3*PI/2, 0,255, true));
            //mesh.addColor(col);
            mesh.addVertex(offsetA);
            //mesh.addColor(col);
            mesh.addVertex(offsetB);
            
        }
        
        // draw the mesh
        ofEnableAlphaBlending();
        ofSetColor(30,30,30);
        ofFill();
        mesh.draw();
        
        ofCircle(pts[0].x,pts[0].y,2);
        ofCircle(pts[pts.size()-1].x,pts[pts.size()-1].y,2);
    }
    
    if (bButton01) {
          ofSetColor(120);
    }else{
          ofSetColor(255);
    }
  
//    button01.draw(buttonPos01, button01.getWidth()/10*4, button01.getHeight()/10*4);
    
    
    if (bButton02) {
        ofSetColor(120);
    }else{
        ofSetColor(255);
    }
    ofRectangle rect;
    rect.setFromCenter(buttonPos02.x, buttonPos02.y, button02.getWidth()/10*4, button02.getHeight()/10*4);
    button02.draw(rect);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    ofPoint mousePos(x,y);
    float dis = mousePos.distance(buttonPos01);
    if (dis < button01.getWidth()/10*4) {
        bButton01 = true;
    }else{
        bButton01 = false;
    }
    
    ofRectangle rect;
    rect.setFromCenter(buttonPos02.x,buttonPos02.y, button02.getWidth()/10*4, button02.getHeight()/10*4);
    
    if (rect.inside(x, y)) {
        bButton02 = true;
    }else{
        bButton02 = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    ofPoint prevPt = stroke.getVertices()[stroke.getVertices().size()-1];
    
    float distance = (prevPt - ofPoint(x,y)).length();
    
    if (distance > 1){
        stroke.addVertex(x,y);
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
    stroke.clear();
    stroke.addVertex(x,y);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    strokes.push_back(stroke);
    
    ofPoint mousePos(x,y);
    float dis = mousePos.distance(buttonPos01);
    if (dis < button01.getWidth()/10*4) {
        bButton01 = true;
    }else{
        bButton01 = false;
    }
    
    
    ofRectangle rect;
    rect.setFromCenter(buttonPos02.x,buttonPos02.y, button02.getWidth()/10*4, button02.getHeight()/10*4);

    if (rect.inside(x, y)) {
        bButton02 = true;
        
        strokes.clear();
        stroke.clear();

    }else{
        bButton02 = false;
    }
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
