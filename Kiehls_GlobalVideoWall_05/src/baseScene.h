//
//  baseScene.h
//  Kiehls_GlobalVideoWall_04
//
//  Created by Peng Cheng on 8/14/14.
//
//

#ifndef __Kiehls_GlobalVideoWall_04__baseScene__
#define __Kiehls_GlobalVideoWall_04__baseScene__

#include "ofMain.h"


class baseScene {
	
    
public:
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    
};

#endif