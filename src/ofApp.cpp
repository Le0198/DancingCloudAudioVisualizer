#include "ofApp.h"

const int num_pts = 350;
const int num_bands = 350;
vector<double> y_off(num_pts), x_off(num_pts);
ofVec2f points[num_pts];
vector<bool> is_connected(num_pts, false);
float sound_spectrum[num_bands];

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
	float *val = ofSoundGetSpectrum(num_bands);
	updatePoints();
	for (int i = 0; i < num_bands; i++) {
		sound_spectrum[i] *= .97;
		sound_spectrum[i] = max(sound_spectrum[i], val[i]);
 	}
}

void ofApp::draw() {
	ofBackground(bg_color->r, bg_color->g, bg_color->b);
	drawPoints();
}

//Point Setup, Update, and Draw for Dancing Cloud

void ofApp::drawPoints() {
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
		ofDrawCircle(points[i], 3);
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
				ofDrawLine(points[i], points[j]);
			}
		}
	}
	updateColors();
}

void ofApp::updateColors() {
	for (size_t i = 0; i < is_connected.size(); i++) {
		if (!is_connected[i]) {
			pt_colors[i].r = ofRandom(255);
			pt_colors[i].g = ofRandom(255);
			pt_colors[i].b = ofRandom(255);
		}
	}
}

void ofApp::updatePoints() {
	double elapsed_time = ofGetElapsedTimef();

	//Change in time since last update()
	double dt = elapsed_time - curr_time;
	curr_time = elapsed_time;

	for (size_t i = 0; i < num_pts; i++) {
		//Get distance travelled
		y_off[i] += pt_velocity * dt;
		x_off[i] += pt_velocity * dt;

		//Update position using Perlin Noise 
		points[i].x = ofSignedNoise(x_off[i]) * cloud_radius;
		points[i].y = ofSignedNoise(y_off[i]) * cloud_radius;
	}
}
