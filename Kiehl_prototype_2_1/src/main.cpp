#include "testApp.h"
#include "ofAppGlutWindow.h"

#ifdef TARGET_OPENGLES
#include "ofGLProgrammableRenderer.h"
#endif
//--------------------------------------------------------------
int main(){
	ofSetLogLevel(OF_LOG_VERBOSE);
    #ifdef TARGET_OPENGLES
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    #endif
	ofSetupOpenGL(1024,500, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
