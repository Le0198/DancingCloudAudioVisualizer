#include "ofApp.h"

const int num_pts = 324;
ofVec2f points[num_pts];
int pt_spacing = 15;

void ofApp::setup() {
	setupPointCoord();
}

void ofApp::update() {

}

void ofApp::draw() {
	ofBackground(r_bg, g_bg, b_bg);
	drawPoints();
}

void ofApp::drawPoints() {
	int dimension = pt_spacing * (sqrt(num_pts));
	ofPushMatrix();
	ofTranslate((ofGetWidth() - dimension) / 2, (ofGetHeight() - dimension) / 2);
	ofSetColor(r_pt, g_pt, b_pt);
	ofFill();
	for (size_t i = 0; i < num_pts; i++) {
		ofCircle(points[i], 2);
	}
	ofPopMatrix();
}

void ofApp::setupPointCoord() {
	int index = 0;
	for (size_t i = 0; i < sqrt(num_pts); i++) {
		for (size_t j = 0; j < sqrt(num_pts); j++) {
			points[index].set(i * pt_spacing, j * pt_spacing);
			index++;
		}
	}
}