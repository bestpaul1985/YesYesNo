//
//  photo.h
//  Kiehls_GlobalVideoWall_06
//
//  Created by Peng Cheng on 8/19/14.
//
//

#ifndef __Kiehls_GlobalVideoWall_06__photo__
#define __Kiehls_GlobalVideoWall_06__photo__

#include "ofMain.h"

class photo{
public:
    photo();
    void setup(ofImage &img, int x, int y, int Angle);
    void update();
    void draw();
    
    ofPoint pos;
    float orgY;
    float angle;
    float startAngle;
    float endAngle;
    
    float photoW,photoH;
    int level;
    ofImage *photoBg;
    ofRectangle rect;
    
    float xSpeed;
    
};

#endif /* defined(__Kiehls_GlobalVideoWall_06__photo__) */
