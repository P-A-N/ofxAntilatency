#pragma once

#include "ofMain.h"
#include "ofxAntilatency.h"
#include "ofxYAML.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit()
	{
		antilatency.stopThread();
		ofSleepMillis(20);
	}
	
	int sameValueCounter = 0;
	int rebootThresh = 10;
	int trackingLogLevel;

	ofx::Antilatency::Model model;
	ofxAntilatency antilatency;
	ofxYAML yaml;
};
