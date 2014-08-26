/*
 *  squareScene.cpp
 *  sceneExample
 *
 *  Created by zachary lieberman on 11/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "imageScene.h"
#include "testApp.h"




void imageScene::setup(){
		
	frog.loadImage("frog-1.jpg");
}




void imageScene::draw(){
	
    
    // ofGetAppPtr()  return ofBaseApp *
    
    testApp * app = (testApp *)ofGetAppPtr();
    ((squareScene*)(app->scenes[0]))->coolnessFactor = ofRandom(0,100);
    
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(255,255,255);
	frog.draw(100,100);
	
}
	
