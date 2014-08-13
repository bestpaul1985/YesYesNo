#include "scene03.h"

//--------------------------------------------------------------
void scene03::setup(){
    
#ifdef _USE_4k_SCREEN
    frame.setFromCenter(0,0,1700,1850);
    photoWidth = 1500;
    photoHeight = 1500;
    
    sing_it_01.loadImage("images/sing_it.png");
    sing_it_02.loadImage("images/retake.png");
    sing_it_01_Pos.set(ofGetWidth()/2-170, ofGetHeight()/2+130);
    sing_it_02_Pos.set( ofGetWidth()/2, ofGetHeight()/2+300);
#else
    frame.setFromCenter(0,0,400,450);
    photoWidth = 350;
    photoHeight = 350;
    
    sing_it_01.loadImage("sing_it_01.png");
    sing_it_02.loadImage("sing_it_02.png");
    sing_it_01_Pos.set(ofGetWidth()/2-170, ofGetHeight()/2+130);
    sing_it_02_Pos.set( ofGetWidth()/2, ofGetHeight()/2+300);
#endif
    
    bRetake = false;
    bSign = false;
}

//--------------------------------------------------------------
void scene03::update(){
    
}

//--------------------------------------------------------------
void scene03::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255);
    ofRect(frame);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2-25);
    ofRotateZ(90);
    ofSetColor(255);
    photo.draw(-photoWidth*0.5f, photoHeight*0.5f,photoWidth,-photoHeight);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(sing_it_01_Pos);
    ofSetColor(255);
    sing_it_01.draw(-sing_it_01.getWidth()/2,-sing_it_01.getHeight()/2);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(sing_it_02_Pos);
    ofSetColor(255);
    sing_it_02.draw(-sing_it_02.getWidth()/2,-sing_it_02.getHeight()/2);
    ofPopMatrix();
    
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
//        ofCircle(pts[0].x,pts[0].y,2);
//        ofCircle(pts[pts.size()-1].x,pts[pts.size()-1].y,2);
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
        meshes.push_back(mesh);
       
        // draw the mesh

//        ofCircle(pts[0].x,pts[0].y,2);
//        ofCircle(pts[pts.size()-1].x,pts[pts.size()-1].y,2);
    }
    
    
    for (int i=0; i<meshes.size(); i++) {
        ofSetColor(30,30,30);
        ofFill();
        meshes[i].draw();
    }
}

//--------------------------------------------------------------
void scene03::keyPressed(int key){
    
}

//--------------------------------------------------------------
void scene03::keyReleased(int key){
    
}

//--------------------------------------------------------------
void scene03::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void scene03::mouseDragged(int x, int y, int button){
    ofPoint prevPt = stroke.getVertices()[stroke.getVertices().size()-1];
    
    float distance = (prevPt - ofPoint(x,y)).length();
    
    if (distance > 1){
        stroke.addVertex(x,y);
    }
}

//--------------------------------------------------------------
void scene03::mousePressed(int x, int y, int button){
    ofRectangle sign;
    ofRectangle retake;
    
    retake.setFromCenter(sing_it_02_Pos, sing_it_02.getWidth(), sing_it_02.getHeight());
    
    ofPoint org = sing_it_01_Pos;
    ofPoint mousePos(x,y);
    float dis = org.distance(mousePos);
    if (dis<sing_it_01.getWidth()/2) {
        bSign = true;
    }
    
    if (retake.inside(x, y)) {
        bRetake = true;
    }
    
    stroke.clear();
    stroke.addVertex(x,y);

}

//--------------------------------------------------------------
void scene03::mouseReleased(int x, int y, int button){
    strokes.push_back(stroke);

}

//--------------------------------------------------------------
void scene03::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void scene03::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void scene03::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
void scene03::reset(){
    strokes.clear();
    stroke.clear();
    meshes.clear();
    bRetake = false;
    bSign = false;
}


