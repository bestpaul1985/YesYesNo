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
    
    //-------------------------------------line finder//
    image.loadImage("earthOutline.png");
    colorImage.allocate(image.width,image.height);
    grayImage.allocate(image.width,image.height);
    threshold = 80;
    earthSize = 150;
    colorImage.setFromPixels(image.getPixels(),2000,1000);
    grayImage = colorImage;
    grayImage.threshold(threshold);
    contourFinder.findContours(grayImage, 20, 2000*1000, 100, true);	// find holes
    
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
    
    //--------------------------------------sphere//
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
    
    //--------------------------------------easy cam//
    cam.setDistance(400);
   
    
    //------------------------------------city//
    loadCity();
    gui.setup();
    gui.add(x.setup("x res", 0, 0, 360));
    gui.add(y.setup("y res", 0, 0, 360));
    gui.add(z.setup("z res", 0, 0, 360));


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
        cam.begin();
        ofScale(1,-1,1);

        ofClear(0,0,0,255);
    
   
    material.begin();
    texture.getTextureReference().bind();
    ofFill();
    ofSetColor(255);
    sphere.draw();
    texture.getTextureReference().unbind();
    material.end();
//        ofRotate(ofGetFrameNum()/2, 0, 1, 0);
        // sphere
    
//        mat.translate(ofGetWidth()/2, ofGetHeight()/2,0);
//        mat.rotate(ofGetFrameNum()/2, 0,1,0);
    
        for (int i = 0; i < lines.size(); i++){
            
            ofPolyline temp;
            temp = lines[i].PolyLine;
            for (int j = 0; j < temp.size(); j++){
                temp[j] = temp[j] * mat;
//                temp[j].z *= ofMap(mouseX, 0, ofGetWidth(), -3,3, true);
            }
            ofNoFill();
            ofSetColor(255);
            ofSetLineWidth(1);
            temp.draw();
        }
    

        cam.end();
    
        //--------outline circle
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
   
    //----------------------------------- flags
    ofEnableDepthTest();
    cam.begin();
    ofScale(1,-1,1);
    drawCity();
    cam.end();
    ofDisableDepthTest();
    
    ofSetColor(255);
    bot_banner.draw(0, 410);
    
//    ofSetColor(255);
//    gui.draw();
    
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

//--------------------------------------------------------------
void testApp::loadCity(){

    //------------ load city
	City newyork = { "new york", 40+47/60., -73 + 58/60. };
	City tokyo = { "tokyo", 35 + 40./60, 139 + 45/60. };
	City london = { "london", 51 + 32/60., -5./60. };
	City shanghai = { "shanghai", 31 + 10/60., 121 + 28/60. };
	City buenosaires = { "buenos aires", -34 + 35/60., -58 + 22/60. };
	City melbourne = { "melbourne" , -37 + 47/60., 144 + 58/60. };
    
	cities.push_back( newyork );
	cities.push_back( tokyo );
	cities.push_back( london );
	cities.push_back( shanghai );
	cities.push_back( buenosaires );
	cities.push_back( melbourne );
    
    //------------ load image
    ofImage img;
    for(int i=0; i<cities.size(); i++){
        img.loadImage("flags/flags"+ofToString(i)+".gif");
        flags.push_back(img);
    }
    
    //------------ load angle offsit
    ofPoint tempAngle;
    tempAngle.set(70,138,93);
    angle.push_back(tempAngle);
    tempAngle.set(149,30,0);
    angle.push_back(tempAngle);
    tempAngle.set(59,0,36);
    angle.push_back(tempAngle);
    tempAngle.set(129,232,304);
    angle.push_back(tempAngle);
    tempAngle.set(136,45,18);
    angle.push_back(tempAngle);
    tempAngle.set(228,208,0);
    angle.push_back(tempAngle);
}



//--------------------------------------------------------------
void testApp::drawCity(){

		
	for(int i = 0; i < cities.size(); i++){
	
		ofQuaternion latRot, longRot, spinQuat;
		latRot.makeRotate(cities[i].latitude, 1, 0, 0);
		longRot.makeRotate(cities[i].longitude, 0, 1, 0);
		ofVec3f center = ofVec3f(0,0,earthSize+2);
		ofVec3f worldPoint = latRot * longRot * spinQuat * center;
       
        ofPoint pt = worldPoint * cam.getModelViewMatrix();
        cout << pt << endl;
        
       
        if (pt.z > -380){
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
        ofTranslate(worldPoint);
        ofRotate(angle[i].x, 1, 0, 0);
        ofRotate(angle[i].y, 0, 1, 0);
        ofRotate(angle[i].z, 0, 0, 1);
        
        ofSetColor(255);
        
        flags[i].draw(0,0,20,15);
        
        ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
        }

	}
   
}









