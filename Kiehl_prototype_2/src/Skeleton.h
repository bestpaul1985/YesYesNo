//
//  Skeleton.h
//  Kiehl_prototype_2
//
//  Created by Peng Cheng on 5/15/14.
//
//

#ifndef __Kiehl_prototype_2__Skeleton__
#define __Kiehl_prototype_2__Skeleton__

#include <ofMain.h>

class Skeleton{
public:
    void setup();
    void update();
    void draw();
   
    
    ofImage imgHeavier,imgThinner;
    bool bAnimation;
    float angle;
    float timer;
};

#endif /* defined(__Kiehl_prototype_2__Skeleton__) */
