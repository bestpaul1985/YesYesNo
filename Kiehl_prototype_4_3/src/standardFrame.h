//
//  standardFrame.h
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 6/9/14.
//
//

#ifndef __Kiehl_prototype_4__standardFrame__
#define __Kiehl_prototype_4__standardFrame__

#include "ofMain.h"

class standarFrame{

public:
    void init(int x, int y, int W);
    void draw();
    void setPos(int x, int y);
    void setScale(float scale);
    void setAngle(int degree);
    void loadPic(ofImage &IMG);
    void loadFont(ofTrueTypeFont &Font);
    
    
    
private:
    
    ofImage *img;
    ofTrueTypeFont *font;
    
    ofRectangle frame;
    ofRectangle pic;
    
    int w,h;
    int angle;
    int offSet;
    int imgW,imgH;
    
    ofPoint pos;
    ofPoint fontPos;
    ofPoint fontScale;
    
};

#endif /* defined(__Kiehl_prototype_4__standardFrame__) */
