#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    lineFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
    rockImage.loadImage("stone_rocky_surface_texture.jpg");
    shader.load("shader/shader");
    
    ofSetCircleResolution(100);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    bot_banner.loadImage("banner.png");
    
    //line finder//
    
    image.loadImage("earthOutline.png");
    colorImage.allocate(image.width,image.height);
    grayImage.allocate(image.width,image.height);
    threshold = 80;
    earthSize = 150;
    colorImage.setFromPixels(image.getPixels(),2000,1000);
    grayImage = colorImage;
    grayImage.threshold(threshold);
    contourFinder.findContours(grayImage, 20, (2000*1000)/3, 10, true);	// find holes
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        earthLine newLine;
        lines.push_back(newLine);
        
        for (int j = 0; j < contourFinder.blobs[i].nPts; j++){
            
            ofPoint pot(ofMap(contourFinder.blobs[i].pts[j].x, 0, 2000, -180, 180),
                        ofMap(contourFinder.blobs[i].pts[j].y,0, 1000, -90,90));
            
            lines[i].pots.push_back(pot);
        }
        
        for (int j=0; j<lines[i].pots.size(); j++) {
            ofQuaternion latRot, longRot, spinQuat;
            latRot.makeRotate(-lines[i].pots[j].y, 1, 0, 0);
            longRot.makeRotate(lines[i].pots[j].x, 0, 1, 0);
            spinQuat.makeRotate(ofGetFrameNum(), 0, 1, 0);
            ofVec3f center = ofVec3f(0,0,earthSize);
            ofVec3f worldPoint = latRot * longRot * spinQuat * center;
            lines[i].PolyLine.addVertex(worldPoint);
        }
    }
    
    //sphere//
    
    ofDisableArbTex();
    texture.loadImage("earthTexture.png");
    texture.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 120 );
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetSphereResolution(24);
    sphere.setRadius(earthSize);
    sphere.setResolution(48);
    sphere.mapTexCoordsFromTexture( texture.getTextureReference() );
    sphere.setOrientation(ofPoint(0,180,0));

}

//--------------------------------------------------------------
void testApp::update(){
    if (ofGetFrameNum() % 30 == 0) shader.load("shader/shader");;
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
}

//--------------------------------------------------------------
void testApp::draw(){
   
    
    
    ofMatrix4x4 mat;
    mat = ofMatrix4x4::newIdentityMatrix();
    
    
    
    ofBackground(30);
    ofEnableDepthTest();
    
   
    //--------------------------------------- line
    lineFbo.begin();
        ofClear(0,0,0,255);
    
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotate(ofGetFrameNum()/2, 0, 1, 0);
    
    
    
        // sphere
    
        material.begin();
        ofNoFill();
        ofSetColor(255);
        texture.getTextureReference().bind();
        ofFill();
        ofSetColor(255);
        sphere.draw();
        texture.getTextureReference().unbind();
        material.end();
    
    
        ofPopMatrix();
    

    
        //mat.translate(ofGetWidth()/2, ofGetHeight()/2,0);
        mat.rotate(ofGetFrameNum()/2, 0,1,0);
    

    
        for (int i = 0; i < lines.size(); i++){
            
            ofPolyline temp;
            temp = lines[i].PolyLine;
            for (int j = 0; j < temp.size(); j++){
                temp[j] = temp[j] * mat + ofPoint(ofGetWidth()/2, ofGetHeight()/2);
                //temp[j].z *= ofMap(mouseX, 0, ofGetWidth(), -3,3, true);
            }
            ofNoFill();
            ofSetColor(255);
            ofSetLineWidth(1);
            temp.draw();
        }
    
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotateZ(ofGetFrameNum()/2);
        ofNoFill();
        ofSetColor(200);
        ofSetLineWidth(ofRandom(3,4));
        ofCircle(0,0, earthSize+12);
        ofPopMatrix();
    lineFbo.end();
    
    
    // --------------------------------------- shader
    ofDisableDepthTest();
    shader.begin();
    
    shader.setUniformTexture("tex0",lineFbo, 0 );
    shader.setUniformTexture("tex1",rockImage.getTextureReference(), 1 );
    
    ofSetColor(255);
    lineFbo.draw(0,0);
    shader.end();
    
    ofSetColor(255);
    bot_banner.draw(0, 410);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
