//
//  Polaroidframe.h
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 6/9/14.
//
//

#ifndef __Kiehl_prototype_4__Polaroidframe__
#define __Kiehl_prototype_4__Polaroidframe__


#include "ofMain.h"
class Polaroidframe{
    
  
public:
    
    enum FRAME_STYLE{
        NO_FRAME_1,
        NO_FRAME_2,
        FRAME,
        POLAROID
    };
    
    
    Polaroidframe();
    void init(int x, int y, int W);
    void loadPic(ofImage &IMG);
    void update();
    void draw();
    void setPos(int x, int y);
    void setAngle(int degree);
    void loadFont(ofTrueTypeFont &Font);
    void enableBottomBanner();
    void enableFrame();
    void loadShadow(ofImage &Shadow);
    void setStyle(FRAME_STYLE Style);
    void setLevel(int Level);
    void setWidth(int W);
    void setImageNum(int I);
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    void setSelected(bool Selected);
    bool isMouseOver();
    bool isSelected();
    bool isAnimating();
    
    ofPoint getPos();
    int getLevel();
    float getWidth();
    int getAngle();
    int getStyle();
    int getImageNum();
    ofRectangle frame;

    string picName;
    string cityName;
    
    

    
private:
    
    float w,h;
    float orgW;
    float desW;
    float speed;
    float pct;
    
    int imgNun;
    float scale;

    void drawFrames();
    void drawPic();
    void drawBottomBanner();
    void drawShadow();

    void animation();
    
    ofImage *img;
    ofTrueTypeFont *font;
    
    float fontScale;

    ofRectangle pic;
    ofRectangle shadowRect;
    
    int angle;
    int offSet;
    int imgW,imgH;
    int bannerH;
    int level;
    
    
    ofPoint pos;
    ofPoint orgPos;
    ofPoint desPos;

    ofPoint fontPos;
    
    bool bBottomBanner;
    bool bFrame;
    bool bMouseOver;
    bool bSelected;
    bool bMousePressed;
    ofImage* shadow;

    int style;

};

#endif /* defined(__Kiehl_prototype_4__Polaroidframe__) */
