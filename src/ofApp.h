#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
	int r_bg = 175, g_bg = 175, b_bg = 175;
	int r_pt = 0, g_pt = 0, b_pt = 0;

public:
	void setup();
	void update();
	void draw();
	void drawPoints();
	void setupPointCoord();
};
