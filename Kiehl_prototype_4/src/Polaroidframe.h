//
//  Polaroidframe.h
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 6/9/14.
//
//

#ifndef __Kiehl_prototype_4__Polaroidframe__
#define __Kiehl_prototype_4__Polaroidframe__
enum FRAME_STYLE{
    NO_FRAME_1,
    NO_FRAME_2,
    FRAME_1,
    FRAME_2,
    POLAROID
};

#include "ofMain.h"
class Polaroidframe{
public:
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
    void loadShadow(vector<ofImage> imgs);
    void setStyle(FRAME_STYLE style);
    void setLevel(int Level);
    void setWidth(int W);
    
    ofPoint getPos();
    int getLevel();
    int getWidth();
    
    string picName;
    string cityName;
    
private:
    
    int w,h;
    float scale;

    void drawFrames();
    void drawPic();
    void drawBottomBanner();

    FRAME_STYLE style;

    ofImage *img;
    ofTrueTypeFont *font;
    
    float fontScale;

    ofRectangle frame;
    ofRectangle pic;
    
    int angle;
    int offSet;
    int imgW,imgH;
    int bannerH;
    int level;
    
    
    ofPoint pos;
    ofPoint fontPos;
    
    bool bBottomBanner;
    bool bFrame;
    
    vector<ofImage*> shadows;


};

#endif /* defined(__Kiehl_prototype_4__Polaroidframe__) */
