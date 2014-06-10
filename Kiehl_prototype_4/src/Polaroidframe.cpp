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
    picName = "picName";
    cityName = "cityName";
    scale = 0.75;
    w = 0;
    imgNun = 0;
}
//-------------------------------------------------------------
void Polaroidframe::init(int x, int y, int W){

    pos.set(x, y);
    w = W;
    h = w/3*4;
    angle = 0;
}
//-------------------------------------------------------------
void Polaroidframe::update(){
    
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
void Polaroidframe::draw(){

    ofPushMatrix();
    if (bFrame) drawFrames();
    if (bBottomBanner) drawBottomBanner();
    drawPic();
    drawShadow();
    ofPopMatrix();
    
   
    
}
//-------------------------------------------------------------
void Polaroidframe::drawFrames(){
    
    frame.setFromCenter(0,0, w, h);
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);

    if (bFrame) {
        ofSetColor(255);
        ofRect(frame);
    }
    ofPopMatrix();

}

//-------------------------------------------------------------
void Polaroidframe::drawShadow(){

    if (shadows.size()>0) {
        
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateZ(angle);
        if (style == POLAROID) {
            float sw = w*1.02;
            float sh = ofMap(sw, 0, shadows[0]->getWidth(), 0,  shadows[0]->getHeight())*1.17;
            shadowRect.setFromCenter(0,0, sw, sh);
            ofSetColor(255);
            shadows[0]->draw(shadowRect);
        }
        if (style == FRAME) {
            float sw = w*1.02;
            float sh = ofMap(sw, 0, shadows[0]->getWidth(), 0,  shadows[0]->getHeight())*1.32;
            shadowRect.setFromCenter(0,0, sw, sh);
            ofSetColor(255);
            shadows[0]->draw(shadowRect);
        }
        if (style == NO_FRAME_1 && style == NO_FRAME_2) {
            float sw = w*1.02;
            float sh = ofMap(sw, 0, shadows[0]->getWidth(), 0,  shadows[0]->getHeight())*1.0;
            shadowRect.setFromCenter(0,0, sw, sh);
            ofSetColor(255);
            shadows[0]->draw(shadowRect);
        }
        ofPopMatrix();
    }

    
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

/**************************************************************
 SETTING
**************************************************************/
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
void Polaroidframe::loadShadow(ofImage &imgs){

    shadows.push_back(&imgs);

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







