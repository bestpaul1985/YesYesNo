//
//  photoFrame.cpp
//  Kiehl_prototype_5
//
//  Created by Peng Cheng on 6/20/14.
//
//

#include "photoFrame.h"

void photoFrame::initial(int x, int y, ofImage &LUT, ofImage &Frame, ofTexture &Texture, float Scale){

    getPos.set(x, y);
    lutImg = &LUT;
    frameImg = &Frame;
    grabTexture = &Texture;
    grabPhoto.allocate(lutImg->getWidth(), lutImg->getHeight(), OF_IMAGE_COLOR_ALPHA);
    scale = Scale;
    
    unsigned char *imagePix = grabPhoto.getPixels();
    for (int i=0; i<lutImg->getWidth(); i++) {
        for (int j=0; j<lutImg->getHeight(); j++) {
            int ii = j*lutImg->getWidth()+i;
            ofColor color(0,0);
            imagePix[ii*4]= color.r;
            imagePix[ii*4+1]= color.g;
            imagePix[ii*4+2]= color.b;
            imagePix[ii*4+3]= color.a;
        }
    }
    grabPhoto.update();

}

//-----------------------------------------------------------------
void photoFrame::update(){
    
    unsigned char *vedioPix = lutImg->getPixels();
    unsigned char *imagePix = grabPhoto.getPixels();
    
    for (int i=0; i<lutImg->getWidth(); i++) {
        for (int j=0; j<lutImg->getHeight(); j++) {
            
            int ii = j*lutImg->getWidth()+i;
            
            if (i >= 160 && i<= 480) {
                ofColor color = ofColor( vedioPix[ii*3], vedioPix[ii*3+1], vedioPix[ii*3+2], 255);
                imagePix[ii*4]= color.r;
                imagePix[ii*4+1]= color.g;
                imagePix[ii*4+2]= color.b;
                imagePix[ii*4+3]= color.a;
            }else{
                ofColor color(0,0);
                imagePix[ii*4]= color.r;
                imagePix[ii*4+1]= color.g;
                imagePix[ii*4+2]= color.b;
                imagePix[ii*4+3]= color.a;
            }
        }
    }
    grabPhoto.update();
    
}

//-----------------------------------------------------------------
void photoFrame::draw(){
    
    ofPushMatrix();
    ofTranslate(getPos);
    ofSetColor(255);
    grabTexture->draw(-frameImg->getWidth()/6*scale,-frameImg->getHeight()/6*scale,frameImg->getWidth()/3*scale,frameImg->getHeight()/3*scale);
    float W = ofMap(frameImg->getHeight()/3, 0, grabPhoto.getHeight(), 0, grabPhoto.getWidth());
    grabPhoto.draw(W/2*scale, -frameImg->getHeight()/6*scale, -W*scale, frameImg->getHeight()/3*scale);
    frameImg->draw(-frameImg->getWidth()/6*scale,-frameImg->getHeight()/6*scale,frameImg->getWidth()/3*scale,frameImg->getHeight()/3*scale);
    ofPopMatrix();
    
    
}

//-----------------------------------------------------------------
void photoFrame::reset(){

    grabPhoto.clear();
    grabPhoto.allocate(lutImg->getWidth(), lutImg->getHeight(), OF_IMAGE_COLOR_ALPHA);
    unsigned char *imagePix = grabPhoto.getPixels();
    for (int i=0; i<lutImg->getWidth(); i++) {
        for (int j=0; j<lutImg->getHeight(); j++) {
            int ii = j*lutImg->getWidth()+i;
            ofColor color(0,0);
            imagePix[ii*4]= color.r;
            imagePix[ii*4+1]= color.g;
            imagePix[ii*4+2]= color.b;
            imagePix[ii*4+3]= color.a;
        }
    }
    grabPhoto.update();

}






