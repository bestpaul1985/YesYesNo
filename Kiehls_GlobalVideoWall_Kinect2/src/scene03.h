
#include "ofMain.h"
#define _USE_4k_SCREEN

class scene03 : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void reset();
    

    ofRectangle frame;
    ofFbo       photo;
    int         photoWidth;
    int         photoHeight;
    ofImage     sing_it_01;
    ofImage     sing_it_02;
    ofPoint     sing_it_01_Pos;
    ofPoint     sing_it_02_Pos;
    
    bool        bRetake;
    bool        bSign;
    
    vector<ofPolyline>  strokes;
    ofPolyline          stroke;
    vector<ofMesh>      meshes;
};

