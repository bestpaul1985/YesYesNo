//
//  photoFrame.h
//  Kiehl_prototype_5
//
//  Created by Peng Cheng on 6/20/14.
//
//

#ifndef __Kiehl_prototype_5__photoFrame__
#define __Kiehl_prototype_5__photoFrame__

#include "ofMain.h"

class photoFrame{
public:
    void initial(int x, int y, ofImage &LUT, ofImage &Frame, ofTexture &Texture, float Scale);
    void update();
    void draw();
    void reset();
    ofPoint     getPos;
    ofImage     *lutImg;
    ofImage     *frameImg;
    ofImage     grabPhoto;
    ofTexture   *grabTexture;
    float       scale;
    
    int picW;
    int picH;
};

#endif /* defined(__Kiehl_prototype_5__photoFrame__) */
