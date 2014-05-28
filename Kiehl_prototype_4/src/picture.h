//
//  picture.h
//  Kiehl_prototype_4
//
//  Created by Peng Cheng on 5/27/14.
//
//

#ifndef __Kiehl_prototype_4__picture__
#define __Kiehl_prototype_4__picture__

#include "ofMain.h"

class picture{
    
public:
    void init(int x, int y, int w, int h);
    void draw();
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    void mouseMoved(int x, int y);


    ofColor color;
    ofRectangle rect;
    
};

#endif /* defined(__Kiehl_prototype_4__picture__) */
