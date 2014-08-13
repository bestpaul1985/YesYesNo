#include "ofMain.h"
#define _USE_4k_SCREEN

class scene04 : public ofBaseApp{
public:
    enum ACTION{
        DRASS_UP,
        SOCIAL_PROP,
        SOCIAL_NO_PROP,
        SIGN_UP,
        DONE
    };
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void reset();
    void drawMesh();
    
    vector<ofMesh>      meshes;
    ofTexture           photo;
    ofRectangle         frame;
    int                 photoWidth;
    int                 photoHeight;
    
    ofRectangle         buttonRect01;
    ofRectangle         buttonRect02;
    ofRectangle         buttonRect03;
    ofRectangle         buttonRect04;

    ofImage             buttonImg01;
    ofImage             buttonImg02;
    ofImage             buttonImg03;
    ofImage             buttonImg04;

    ofRectangle         propRect;
    ofImage             propImage;
    ofPoint             propTraget;
    bool                bSelected;
    
    ACTION              action;
};
