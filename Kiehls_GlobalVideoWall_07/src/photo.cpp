#include "photo.h"

float photo::map(float in, float inMin,float inMax, float outMin, float outMax, float shaper){
    float pct = ofMap (in, inMin, inMax, 0, 1, true);
    pct = powf(pct, shaper);
    float out = ofMap(pct, 0,1, outMin, outMax, true);
    return out;
}
//--------------------------------------------------------------
photo::photo(){
    xSpeed = ofRandom(0.95, 1.05);
    bMousePressed = false;
    dragDx = 0;
    timer = ofGetElapsedTimeMillis();
    scale.set(1,1);
    myAction = DEFAULT;
}
//--------------------------------------------------------------
void photo::setup(ofImage &img, int x, int y, int Angle){
    
    pos.set(x,y);
    orgPos = pos;
    currentPos = pos;
    
    angle = Angle;
    image = &img;
    width = image->getWidth()/5;
    height = image->getHeight()/5;
    rect.setFromCenter(0,0,width, height);
    targetRect.setFromCenter(0, 0, width*3, height*3);
}


//--------------------------------------------------------------
void photo::update(){
    
    dragDx *= 0.97;
    pos.x += dragDx* xSpeed;

    if (pos.x < -width*0.5f) {
        pos.x = ofGetWidth()+width*0.5f;
    }
    else if (pos.x > ofGetWidth()+width*0.5f) {
        pos.x = -width*0.5f;
    }
    
    float xPct = ofMap(pos.x, 0, ofGetWidth(), 0, 1, true);
    float xPctShaped = powf(xPct, 3.0);
    pos.y = ofMap(xPctShaped, 0, 1, orgPos.y, ofGetHeight()/3 + 2*orgPos.y/3.0);

    
        switch (myAction) {
            case POP_OUT:{
    
                float goal;
                float t1 = 300;
                float t2 = 900;
                float sharp1 = 1.8;
                float sharp2 = 0.8;
                
                if(ofGetElapsedTimeMillis()-timer<t1){
                    pos.x = map(ofGetElapsedTimeMillis()-timer, 0, t1, currentPos.x, currentPos.x-offX, sharp1);
                    pos.y = map(ofGetElapsedTimeMillis()-timer, 0, t1, currentPos.y, currentPos.y-offY, sharp1);
                    goal = 0.5;
                    scale.x =  0.9*scale.x + 0.1*goal;
                    scale.y =  0.9*scale.y + 0.1*goal;
                }
                else{
                   
                    pos.x = map(ofGetElapsedTimeMillis()-timer, t1, t2, currentPos.x-offX, currentPos.x, sharp2);
                    pos.y = map(ofGetElapsedTimeMillis()-timer, t1, t2, currentPos.y-offY, currentPos.y, sharp2);
                    goal = 4;
                    scale.x =  0.88*scale.x + 0.12*goal;
                    scale.y =  0.88*scale.y + 0.12*goal;
                }
                
            }break;
                
            case POP_BACK:{
                
                float goal;
                float t1 = 300;
                float t2 = 900;
                float sharp1 = 1.8;
                float sharp2 = 0.8;
                

                if(ofGetElapsedTimeMillis()-timer<t1){
                    pos.x = map(ofGetElapsedTimeMillis()-timer, 0, t1, currentPos.x, currentPos.x+offX, sharp1);
                    pos.y = map(ofGetElapsedTimeMillis()-timer, 0, t1, currentPos.y, currentPos.y+offY, sharp1);
                    goal = 5;
                    scale.x =  0.9*scale.x + 0.1*goal;
                    scale.y =  0.9*scale.y + 0.1*goal;
                }
                else{
                    pos.x = map(ofGetElapsedTimeMillis()-timer, t1, t2, currentPos.x+offX, currentPos.x, sharp2);
                    pos.y = map(ofGetElapsedTimeMillis()-timer, t1, t2, currentPos.y+offY, currentPos.y, sharp2);
                    goal = 1;
                    scale.x =  0.88*scale.x + 0.12*goal;
                    scale.y =  0.88*scale.y + 0.12*goal;
                    
                    if (scale.x < 1.001) {
                        myAction = DEFAULT;
                        bMousePressed = false;
                    }
                }
                                
            }break;
                
            case DEFAULT:{
                
              
                
            }break;
        
    }
    
}

//--------------------------------------------------------------
void photo::draw(){
   
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofScale(scale.x, scale.y, 1);
    ofSetColor(255);
    image->draw(rect);
    ofPopMatrix();
    
//    ofMatrix4x4 matrix;
//    matrix.glTranslate( pos.x, pos.y, 0 );
//	matrix.glRotate( angle, 0, 0, 1 );
//    matrix.glScale(scale.x, scale.y, 1);
//    ofPushMatrix();
//    ofMultMatrix(matrix);
//    ofSetColor(0,255,0,100);
//    ofRect(rect);
//    ofPopMatrix();
    
    
}
