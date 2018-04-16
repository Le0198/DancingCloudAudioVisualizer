#include "ofApp.h"

const int num_pts = 250;
vector<double> y_off(num_pts), x_off(num_pts);
ofVec2f points[num_pts];
vector<bool> is_connected(num_pts, false);


void ofApp::setup() {
	for (size_t i = 0; i < num_pts; i++) {
		x_off[i] = ofRandom(0, 100);
		y_off[i] = ofRandom(0, 100);
	}
}

void ofApp::update() {
	updatePoints();
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
	ofSetColor(pt_color->r, pt_color->g, pt_color->b);
	ofFill();
	for (size_t i = 0; i < num_pts; i++) {
		ofDrawCircle(points[i], 2);
	}
	connectPoints();
	ofPopMatrix();
}

//Connects points within a certain distance of each other
void ofApp::connectPoints() {
	for (size_t i = 0; i < num_pts; i++) {
		for (size_t j = i + 1; j < num_pts; j++) {
			double dist = ofDist(points[i].x, points[i].y, points[j].x, points[j].y);
			if (dist < distance_threshold) {
				is_connected[i] = true;
				if (is_connected[i]) {
					ofSetColor(ofRandom(255));
				}
				else {
					ofSetColor(0, 0, 0);
				}
				ofDrawLine(points[i], points[j]);
			}
			is_connected[i] = false;
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
