#include "ofApp.h"
int distance_threshold = 50;
float pt_velocity = .50;
float pt_radius = 3;
float line_width = 2;
float speed_multiplier = 2;
int cloud_radius = 350;
double curr_time = 0;
const int num_pts = 200;
const int num_bands = 300;
vector<double> y_off(num_pts), x_off(num_pts);
ofVec2f points[num_pts];
vector<bool> is_connected(num_pts, false);
float sound_spectrum[num_bands];
bool reached_max_bar_height = false;

void ofApp::setup() {
	sound_player.loadSound("../../songs/The\ Weeknd\ -\ The\ Hills.wav");
	sound_player.play();

	for (size_t i = 0; i < num_pts; i++) {
		x_off[i] = ofRandom(0, 1000);
		y_off[i] = ofRandom(0, 1000);
		pt_colors.push_back(*(new Color(0, 0, 0)));
	}

	for (size_t i = 0; i < num_bands; i++) {
		sound_spectrum[i] = 0.0f;
	}
}

void ofApp::update() {
	ofSoundUpdate();
	updatePoints();
	updateBars();
	
}

//Randomizes the color of a certain point and its line color once that point has been disconnected
void ofApp::updateColors() {
	for (size_t i = 0; i < is_connected.size(); i++) {
		if (!is_connected[i]) {
			pt_colors[i].r = ofRandom(100);
			pt_colors[i].g = 0;
			pt_colors[i].b = ofRandom(200);
		}
	}
}

//Updates the location of the point on the screen
void ofApp::updatePoints() {
	double elapsed_time = ofGetElapsedTimef();

	//Change in time since last update()
	double dt = elapsed_time - curr_time;
	curr_time = elapsed_time;

	for (size_t i = 0; i < num_pts; i++) {
		//Get distance travelled
		y_off[i] += pt_velocity * dt * getMaxFrequency() * speed_multiplier;
		x_off[i] += pt_velocity * dt * getMaxFrequency() * speed_multiplier;

		//Update position using Perlin Noise 
		//https://en.wikipedia.org/wiki/Perlin_noise
		points[i].x = ofSignedNoise(x_off[i]) * cloud_radius;
		points[i].y = ofSignedNoise(y_off[i]) * cloud_radius;
	}
}

float getMaxFrequency() {
	float max = 0.0F;
	for (size_t i = 0; i < num_bands; i++) {
		if (max < sound_spectrum[i]) {
			max = sound_spectrum[i];
		}
	}
	return max;
}

//Updates the audio reactive bars that are displayed on the screen
void ofApp::updateBars() {
	//Got help for making an audio reactive shape from this tutorial: https://www.youtube.com/watch?v=IiTsE7P-GDs
	float *val = ofSoundGetSpectrum(num_bands);
	for (int i = 0; i < num_bands; i++) {
		sound_spectrum[i] *= .97;
		sound_spectrum[i] = max(sound_spectrum[i], val[i]);
	}
}

void ofApp::draw() {
	ofBackground(bg_color->r, bg_color->g, bg_color->b);
	ofSetColor(0, 0, 0);
	drawBars();
	drawPoints();
}

void ofApp::drawBars() {
	reached_max_bar_height = false;
	for (int i = 0; i < num_bands; i++) {
		float barHeight = -sound_spectrum[i] * 250;
		ofRect(i * 5, ofGetHeight(), 4, barHeight);
		if (-barHeight >= 250)
		{
			reached_max_bar_height = true;
		}
	}
}

void ofApp::drawPoints() {
	if (reached_max_bar_height) {
		pt_radius = 4;
		line_width = 3;
	}
	else {
		pt_radius = 3;
		line_width = 2;
	}
	// Center points
	// https://stackoverflow.com/questions/12516550/openframeworks-rotate-an-image-from-its-center-through-opengl-calls
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	//Set color of points and create circles at those points
	for (size_t i = 0; i < num_pts; i++) {
		if (is_connected[i]) {
			ofSetColor(pt_colors[i].r, pt_colors[i].g, pt_colors[i].b);
		}
		else {
			ofSetColor(0);
		}
		ofDrawCircle(points[i], pt_radius);
	}
	connectPoints();
	ofPopMatrix();
}

//Connects points within a certain distance of each other
void ofApp::connectPoints() {
	for (size_t i = 0; i < num_pts; i++) {
		is_connected[i] = false;
		for (size_t j = i + 1; j < num_pts; j++) {
			double dist = ofDist(points[i].x, points[i].y, points[j].x, points[j].y);
			if (dist < distance_threshold) {
				is_connected[i] = true;
				ofSetColor(pt_colors[i].r, pt_colors[i].g, pt_colors[i].b);
				ofSetLineWidth(line_width);
				ofDrawLine(points[i], points[j]);
			}
		}
	}
	updateColors();
}

