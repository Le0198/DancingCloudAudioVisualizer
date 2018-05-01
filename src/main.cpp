#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(1440, 768, OF_FULLSCREEN); // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofRunApp(new ofApp()); // start the app
}
