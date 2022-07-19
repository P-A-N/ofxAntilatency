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
	ofTrueTypeFont font;
	void exit()
	{
		antilatency.stopThread();
		ofSleepMillis(20);
	}

	void drawValue2(string title, float value, int x, int y, int rectSize, int rectHeight)
	{
		drawStr(title, value, x, y);
		drawSlider2(ofMap(value, -3, 3, -1, 1, true), 0, y + 10, rectSize, rectHeight);
	}

	void drawStr(string title, float value, int x, int y)
	{
		ofDrawBitmapString(title, x, y);
		ofDrawBitmapString(ofToString(value), x + 100, y);
	}

	void drawSlider(float valu, int x, int y, int width, int height)
	{
		ofPushMatrix();
		ofTranslate(x, y);
		ofTranslate(ofGetWidth() / 2 - width / 2, 0);
		ofNoFill();
		ofDrawRectangle(0, 0, width, height);
		ofTranslate(width / 2, 0);
		ofFill();
		ofDrawRectangle(0, 0, valu * width / 2, height);
		ofPopMatrix();
	}

	void drawSlider2(float valu, int x, int y, int width, int height)
	{
		ofPushMatrix();
		ofTranslate(x, y);
		ofNoFill();
		ofDrawRectangle(0, 0, width, height);
		ofFill();
		ofDrawRectangle(0, 0, valu * width, height);
		ofPopMatrix();
	}

	void drawSlider3(float valu, int x, int y, int width, int height)
	{
		ofPushMatrix();
		ofTranslate(x, y);
		ofNoFill();
		ofDrawRectangle(0, 0, width, height);
		ofFill();
		ofDrawRectangle(width*0.5, 0, valu * width/2, height);
		ofPopMatrix();
	}
	
	int sameValueCounter = 0;
	int rebootThresh = 10;
	int trackingLogLevel;
	bool flag_visualize = false;

	ofx::Antilatency::Data data;
	ofxAntilatency antilatency;
	ofxYAML yaml;
};
