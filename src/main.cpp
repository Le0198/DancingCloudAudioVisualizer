#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW); // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofRunApp(new ofApp()); // start the app
}
