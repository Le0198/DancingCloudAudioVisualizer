#pragma once

#include "ofMain.h"

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
	int distance_threshold = 50;
	double pt_velocity = .08;
	int cloud_radius = 300;
	double curr_time = 0;

public:
	void setup();
	void update();
	void draw();
	void drawPoints();
	void updatePoints();
	void connectPoints();
	void updateColors();
};
