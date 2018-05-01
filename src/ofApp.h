#pragma once

#include "ofMain.h"
float getMaxFrequency();

class ofApp : public ofBaseApp {
	struct Color {
		Color(int red, int green, int blue) : r(red), g(green), b(blue){};
		int r;
		int g;
		int b;
	};
	Color *bg_color = new Color(175, 175, 175);
	vector<Color> pt_colors;
	ofSoundPlayer sound_player;

public:
	void setup();
	void update();
	void updatePoints();
	void connectPoints();
	void updateColors();
	void updateBars();
	void draw();
	void drawPoints();
	void drawBars();
};
