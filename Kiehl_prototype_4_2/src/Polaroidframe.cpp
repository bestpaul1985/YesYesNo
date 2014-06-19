//
//  Polaroidframe.cpp
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 6/9/14.
//
//

#include "Polaroidframe.h"

Polaroidframe::Polaroidframe(){

    angle = 0;
    bBottomBanner = false;
    bFrame = false;
    bMouseOver = false;
    bSelected = false;
    bMousePressed = false;
    bColorChange = false;
    picName = "picName";
    cityName = "cityName";
    scale = 0.75;
    w = 0;
    imgNun = 0;
    pct = 0;
    colorPct = 0;
    color.set(255,0);
    vel.set(0,0);
    damping = 0.05f;
    anima = READY;
}
//-------------------------------------------------------------
void Polaroidframe::init(int x, int y, int W){

    pos.set(x, y);
    orgPos = pos;
    w = W;
    h = w/3*4;
    orgW = w;
    desW = w*3;
    angle = 0;

}
//-------------------------------------------------------------
void Polaroidframe::update(){
    
    animation();
    transition();
    colorChange();
    h = w*scale;
    
    if (bFrame) {
        offSet = w/15;
        imgW = w - offSet*2;
        imgH = h - offSet*2;
    }else{
        imgW = w;
        imgH = h;
    }
    
    if (bBottomBanner) {
        fontScale = ofMap(w, 0, 300, 0, 0.30);
        h = h*1.20;
    }
    
}
//-------------------------------------------------------------
void Polaroidframe::animation(){

    float temPct;
    if (bMousePressed) {
        
        switch (anima) {
            case READY:{
            
                if(ofGetElapsedTimeMillis() - timer < 200 ){
                    angle += ofRandom(-3,3);
                }else{
                    anima = GO;
                }
            }
                break;
            case GO:{
                
                pct = 0.90 * pct + 0.10 * 1.0;
                temPct = powf(pct, 1.5);
                if (pct>0.975) {
                    pct = 0;
                    anima = STOP;
                }
                w = (1-temPct)*orgW + temPct*desW*1.3;
                cout<<pct<<endl;

            }
                break;
            case STOP:{
                
                pct = 0.85 * pct + 0.15 * 1.0;
                temPct = powf(pct,5);
                if (pct>0.99) {
                    pct = 1;
                }
                w = (1-temPct)*desW*1.3 + temPct*desW;
                
                cout<<pct<<endl;
            }
                break;
 
        }
        
    }else{
        pct *= 0.98;
        temPct = powf(pct, 1.5);
        w = (1-temPct)*orgW + temPct*desW;
        anima = READY;
    }
    

}
//-------------------------------------------------------------
void Polaroidframe::colorChange(){
    
    float temPct;
    float c = 0;
    if ( bColorChange) {
        colorPct = 0.98 * colorPct + 0.02 * 1.0;
        temPct = powf(colorPct, 1.5);
        c = colorPct*150;
        color.set(0,c);
    }else{
        colorPct = 0.98 * colorPct;
        temPct = powf(colorPct, 1.5);
        c = colorPct*150;
        color.set(0,c);
    }
}
//-------------------------------------------------------------
void Polaroidframe::transition(){
    
    switch (trans) {
        case GET_OUT:{
            
            float radius = 200;
            ofPoint frc;
            ofPoint desired = posOfForce - pos;
            float d = desired.length();
            desired.normalize();
            
            if (d < radius) {
                float m = ofMap(d,0,radius,0,maxSpeed);
                desired *= m;
            }else{
                desired *= maxSpeed;
            }
            
            ofPoint steer;
            frc = desired - vel;
            
            vel = vel + frc;
            pos = pos + vel;
            
            if (pos.x < -w) {
                trans = OUT_WINDOW;
                vel.set(0,0);
                posOfForce = orgPos;
                pos.x = ofGetWidth()+ofRandom(w,w*10);
            }
        }
            break;
            
            
        case GET_IN:{
            
            float radius = 200;
            ofPoint frc;
            ofPoint desired =  posOfForce - pos;
            float d = desired.length();
            desired.normalize();
            
            if (d < radius) {
                float m = ofMap(d,0,radius,0,maxSpeed);
                desired *= m;
            }else{
                desired *= maxSpeed;
            }
            
            ofPoint steer;
            frc = desired - vel;
            
            vel = vel + frc;
            pos = pos + vel;
            
        }break;
    }
}
//-------------------------------------------------------------
void Polaroidframe::draw(){
    
    drawShadow();
    drawFrames();
    drawBottomBanner();
    drawPic();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofSetColor(color);
    ofRect(frame);
    ofPopMatrix();
    animation();
    
}
//-------------------------------------------------------------
void Polaroidframe::drawFrames(){
    
    frame.setFromCenter(0,0, w, h);
    
    if (bFrame) {
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateZ(angle);
        
        if (bFrame) {
            ofSetColor(255);
            ofRect(frame);
        }
        ofPopMatrix();
    }
    
    

}

//-------------------------------------------------------------
void Polaroidframe::drawShadow(){

        ofPushMatrix();
        ofTranslate(pos);
        ofRotateZ(angle);
        float sw;
        float sh;
        if (style == NO_FRAME_1 ) {
            sw = w*1.26;
            sh = ofMap(sw, 0, shadow->getWidth(), 0,  shadow->getHeight())*1.0;
        }
        if (style == NO_FRAME_2 ) {
            sw = w*1.19;
            sh = ofMap(sw, 0, shadow->getWidth(), 0,  shadow->getHeight())*1.0;
        }
        if (style == FRAME) {
             sw = w*1.28;
             sh = ofMap(sw, 0, shadow->getWidth(), 0,  shadow->getHeight())*1.05;
        }
    
        if (style == POLAROID) {
             sw = w*1.02;
             sh = ofMap(sw, 0, shadow->getWidth(), 0,  shadow->getHeight())*1.16;
        }
    
        shadowRect.setFromCenter(0,0, sw, sh);
        ofSetColor(255);
        shadow->draw(shadowRect);
    
        ofPopMatrix();
    
    
  
}

//-------------------------------------------------------------
void Polaroidframe::drawPic(){

    if (bFrame) {
        pic.set(frame.x+offSet,frame.y+offSet,imgW,imgH);
    }else{
        pic.setFromCenter(0,0,imgW,imgH);
    }
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);

    if (img) {
        ofSetColor(255);
        img->draw(pic);
    }else{
        ofSetColor(120);
        ofRectangle(pic);
    }
    ofPopMatrix();
    
    
}

//-------------------------------------------------------------
void Polaroidframe::drawBottomBanner(){
 
    if (bBottomBanner){
        float nameWidth = font->stringWidth(picName);
        float nameHeight = font->stringHeight(picName);
        float cityWidth = font->stringWidth(cityName);
        float cityHeight = font->stringHeight(cityName);
        
        ofPushMatrix();
        ofTranslate(pos.x,pos.y);
        ofRotateZ(angle);
        if (font){
            ofScale(fontScale,fontScale, 1);
            ofSetColor(255,0, 20);
            font->drawStringAsShapes(picName,(-imgW/2+imgW/30)/fontScale, (imgH/2+imgW/30)/fontScale);
        }
        
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(pos.x,pos.y);
        ofRotateZ(angle);
        if (font){
            ofSetColor(30);
            ofScale(fontScale,fontScale, 1);
            font->drawStringAsShapes(cityName, (imgW/2-imgW/30)/fontScale-cityWidth, (imgH/2+imgW/30)/fontScale);
        }
        ofPopMatrix();
    }
    
}

//-------------------------------------------------------------
void Polaroidframe::mousePressed(int x, int y){
    
    if (bSelected) {
        bMousePressed = !bMousePressed;
        timer = ofGetElapsedTimeMillis();
    }else{
        bColorChange = !bColorChange;
    }
    
    
}

//-------------------------------------------------------------
void Polaroidframe::mouseMoved(int x, int y){

    ofRectangle rect;
    rect.setFromCenter(pos.x,pos.y,w,h);
    if (rect.inside(x, y) && !bMousePressed) {
        bMouseOver = true;
    }else if(!rect.inside(x, y) && !bMousePressed){
        bMouseOver = false;
    }

}
//-------------------------------------------------------------
void Polaroidframe::mouseReleased(int x, int y){
    
}

/**************************************************************
 SETTING
**************************************************************/

void Polaroidframe::setColor(ofColor Color){
    
    color = Color;

}
//-------------------------------------------------------------
void Polaroidframe::setTransition(TRANSITION Trans,ofPoint PosOfForce, float MaxSpeed){
    
    trans = Trans;
    posOfForce = PosOfForce;
    maxSpeed = MaxSpeed;
}
//-------------------------------------------------------------
void Polaroidframe::setSelected(bool Selected){

    bSelected = Selected;
    
}

//-------------------------------------------------------------
void Polaroidframe::setPos(int x,  int y){

    pos.set(x, y);

}
//-------------------------------------------------------------
void Polaroidframe::setAngle(int degree){
    
    angle = degree;
}
//-------------------------------------------------------------
void Polaroidframe::setStyle(FRAME_STYLE Style){
    
    style = Style;
    
    switch (style) {
        case NO_FRAME_1:{
    
            scale = 10.0/7.0;
            bFrame = false;
            bBottomBanner = false;
        }
            break;
            
        case NO_FRAME_2:{
            scale = 7.0/10.0;
            bFrame = false;
            bBottomBanner = false;
        }
            break;
        
        case FRAME:{
            scale = 3.0/2.0;
            bFrame = true;
            bBottomBanner = false;
            
        }break;
            
        case POLAROID:{
            scale = 11.0/10.0;
            bFrame = true;
            bBottomBanner = true;
        }break;
    }
}

void Polaroidframe::setLevel(int Level){

    level = Level;

}

void Polaroidframe::setWidth(int W){
    
    w = W;
   
}

void Polaroidframe::setImageNum(int I){

    imgNun = I;
}


/**************************************************************
 GET
 **************************************************************/
int Polaroidframe::getLevel(){
    
    return level;
    
}

//-------------------------------------------------------------
Polaroidframe::TRANSITION Polaroidframe::getTransition(){
    
    return trans;
    
}

//-------------------------------------------------------------
ofPoint Polaroidframe::getPos(){
    
    return pos;
    
}

//-------------------------------------------------------------
float Polaroidframe::getWidth(){
    return w;
}

//-------------------------------------------------------------
int Polaroidframe::getAngle(){
    
    return angle;
    
}
//-------------------------------------------------------------
int Polaroidframe::getStyle(){
    
    return style;
    
}

int Polaroidframe::getImageNum(){
    
    return imgNun;
    
}

/**************************************************************
 LODING
 **************************************************************/

//-------------------------------------------------------------
void Polaroidframe::loadPic(ofImage &IMG){

    img = &IMG;
    
}

//-------------------------------------------------------------
void Polaroidframe::loadFont(ofTrueTypeFont &Font){
    
    font = &Font;
}

//-------------------------------------------------------------
void Polaroidframe::loadShadow(ofImage &Shadow){

    shadow = &Shadow;

}


/**************************************************************
 ENABLE
 **************************************************************/



//-------------------------------------------------------------
void Polaroidframe::enableBottomBanner(){

    bBottomBanner = true;

}

//-------------------------------------------------------------
void Polaroidframe::enableFrame(){
    
    bFrame = true;
    
}

//-------------------------------------------------------------
bool Polaroidframe::isMouseOver(){

    return bMouseOver;
}

//-------------------------------------------------------------
bool Polaroidframe::isSelected(){
    return bSelected;
}

//-------------------------------------------------------------
bool Polaroidframe::isMousepressed(){
    
    return bMousePressed;
}



