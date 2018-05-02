#include "ofApp.h"

double curr_time = 0;

const int num_pts = 550;
ofVec2f points[num_pts];
vector<double> y_off(num_pts), x_off(num_pts);
float pt_radius = 3;
float pt_velocity = .50;
float speed_multiplier = 1.1;
int cloud_radius = 625;

vector<bool> is_connected(num_pts, false);
int distance_threshold = 50;
float line_width = 2;


const int num_bands = 250;
vector<int> band_x_pos(num_bands);
const int band_width = 11;
const int max_band_height = 300;
const int min_band_height = 25;
bool reached_max_bar_height = false;
float sound_spectrum[num_bands];

void ofApp::setup() {
	sound_player.loadSound("../../songs/imagine.wav");
	sound_player.play();
	// Loading image to use as background https://www.youtube.com/watch?v=eXx5aJCmbz0
	image.load("../../images/bgpic.jpg");
	for (size_t i = 0; i < num_pts; i++) {
		x_off[i] = ofRandom(0, 1000);
		y_off[i] = ofRandom(0, 1000);
		pt_colors.push_back(*(new Color(0, 0, 0)));
	}
	for (size_t i = 0; i < num_bands; i++) {
		sound_spectrum[i] = 0.0f;
		band_x_pos[i] = (band_width + 1) * i;
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
			//10 total options for coloring
			int options = ofRandom(10);
			if (options == 1) {		// 10% chance that point/line is colored with some mixture of green and blue
				pt_colors[i].r = 50;
				pt_colors[i].g = ofRandom(100, 150);
				pt_colors[i].b = ofRandom(50, 125);
			} else if (options == 2) {		// 10% chance that point/line is colored with some mixture of red and blue
				pt_colors[i].r = ofRandom(125, 175);
				pt_colors[i].g = 50;
				pt_colors[i].b = ofRandom(50, 125);
			} else {		// 80% chance that the point/line is colored black
				pt_colors[i].r = 0;
				pt_colors[i].g = 0;
				pt_colors[i].b = 0;
			}
		}
	}
}

// Updates the location of the point on the screen
void ofApp::updatePoints() {
	double elapsed_time = ofGetElapsedTimef();

	// Change in time since last update()
	double dt = elapsed_time - curr_time;
	curr_time = elapsed_time;

	for (size_t i = 0; i < num_pts; i++) {
		// Get distance travelled. Speed of point depends on the highest frequency at the current time
		y_off[i] += pt_velocity * dt * getMaxFrequency() * speed_multiplier;
		x_off[i] += pt_velocity * dt * getMaxFrequency() * speed_multiplier;
	
		// Update position using Perlin Noise 
		// https://en.wikipedia.org/wiki/Perlin_noise
		points[i].x = ofSignedNoise(x_off[i]) * cloud_radius;
		points[i].y = ofSignedNoise(y_off[i]) * cloud_radius - 50;
	}
}

// Finds highest frequency value in sound spectrum
float getMaxFrequency() {
	float max = 0.0F;
	for (size_t i = 0; i < num_bands; i++) {
		if (max < sound_spectrum[i]) {
			max = sound_spectrum[i];
		}
	}
	return max;
}

// Updates the audio reactive bars that are displayed on the screen
void ofApp::updateBars() {
	// Audio reactive shape help from this tutorial: https://www.youtube.com/watch?v=IiTsE7P-GDs
	float *val = ofSoundGetSpectrum(num_bands);
	for (int i = 0; i < num_bands; i++) {
		sound_spectrum[i] *= .92;
		sound_spectrum[i] = max(sound_spectrum[i], val[i]);
		band_x_pos[i] += 1;
		if (band_x_pos[i] > ofGetScreenWidth()) {
			band_x_pos[i] = -band_width;
		}
	}
}

void ofApp::draw() {
	ofSetColor(255);
	image.draw(0, 0, ofGetWidth(), ofGetHeight());
	drawPoints();
	drawBands();
}

void ofApp::drawBands() {
	reached_max_bar_height = false;
	for (int i = 0; i < num_bands; i++) {
		float band_height = -sound_spectrum[i] * max_band_height;
		float band_red_hue = sound_spectrum[i] * 255 + 75;		// Change hue of red depending on the frequency
		ofSetColor(band_red_hue, 0 , 25);
		float band_height_threshold = max_band_height - min_band_height;
		if (-band_height >= band_height_threshold) {
			reached_max_bar_height = true;
			ofSetColor(25, 175, 150);
		}
		ofRect(band_x_pos[i], ofGetHeight(), band_width, band_height - min_band_height);
	}
}

void ofApp::drawPoints() {
	if (reached_max_bar_height) {
		bassBoost();
	} else {
		clearBoost();
	}
	// Center points
	// https://stackoverflow.com/questions/12516550/openframeworks-rotate-an-image-from-its-center-through-opengl-calls
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	//Set color of points and create circles at those points
	for (size_t i = 0; i < num_pts; i++) {
		ofSetColor(0);
		ofDrawCircle(points[i], pt_radius + 1);
		ofSetColor(150, 0, 50);
		ofDrawCircle(points[i], pt_radius);
	}
	connectPoints();
	ofPopMatrix();
}

void bassBoost() {
	pt_radius = 6;
	line_width = 4;
	speed_multiplier = 1.1;
}

void clearBoost() {
	pt_radius = 3;
	line_width = 2;
	speed_multiplier = .8;
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

