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
    
    enum TRANSITION{
        GET_IN,
        GET_OUT,
        OUT_WINDOW,
        DONE
    };
    
    enum ANIMATION{
        READY,
        GO,
        STOP
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
    void setTransition(TRANSITION Trans,ofPoint PosOfForce, float MaxSpeed);
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    void setSelected(bool Selected);
    bool isMousepressed();
    bool isMouseOver();
    bool isSelected();
    void setColor(ofColor Color);
    TRANSITION getTransition();
    
    ofPoint getPos();
    int getLevel();
    float getWidth();
    int getAngle();
    int getStyle();
    int getImageNum();
    ofRectangle frame;

    string picName;
    string cityName;

    ofColor color;
    ofPoint orgPos;
    ofVec2f vel;
    float damping;
    float maxSpeed;
    bool bDebug;

private:
    
    float w,h;
    float orgW;
    float desW;
    float pct;
    float colorPct;
    int imgNun;
    float scale;

    void drawFrames();
    void drawPic();
    void drawBottomBanner();
    void drawShadow();
    void animation();
    void transition();
    void colorChange();
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
    ofPoint desPos;

    ofPoint fontPos;
    
    ofPoint posOfForce;
    
    bool bBottomBanner;
    bool bFrame;
    bool bMouseOver;
    bool bSelected;
    bool bMousePressed;
    bool bTranslation;
    bool bColorChange;
    ofImage* shadow;

    int style;
    TRANSITION trans;
    ANIMATION  anima;
    float timer;

};

#endif /* defined(__Kiehl_prototype_4__Polaroidframe__) */
