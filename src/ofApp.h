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
	Color *pt_color = new Color(0, 0, 0);
	vector<Color> colors;
	
	int distance_threshold = 50;
	double pt_velocity = .05;
	int cloud_radius = 500;
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
