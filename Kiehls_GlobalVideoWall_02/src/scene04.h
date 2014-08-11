#include "ofMain.h"

class scene04 : public ofBaseApp{
public:
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
    
    ofRectangle         buttonRect;
    ofImage             buttonImg;
    
    ofRectangle         propRect;
    ofImage             propImage;

};
