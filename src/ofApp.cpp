#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofx::Antilatency::Setting setting;
	
	yaml.load("config.yaml");

	//setup antilatency
	setting.environment = yaml["environment"].as<std::string>();
	setting.nextEnvironment = yaml["environment"].as<std::string>();
	setting.placement = yaml["placement"].as<std::string>();
	setting.extrapolateTime = yaml["extrapolateTime"].as<float>();
	setting.trackingIntervalMilliseconds = yaml["trackingIntervalMilliseconds"].as<int>();
	setting.statusOscIntervalMilliseconds = yaml["statusOscIntervalMilliseconds"].as<int>();

	//setup osc
	setting.oscOutAddress = yaml["oscOutAddress"].as<std::string>();
	setting.oscOutPort = yaml["oscOutPort"].as<int>();
	setting.oscInPort = yaml["oscInPort"].as<int>();


	//setup etc
	int trackingLogLevel = yaml["trackingLogLevel"].as<int>();
	setting.printConfig();
	antilatency.setup(setting);
	antilatency.start();

	font.load("verdana.ttf", 30);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!flag_visualize)return;
	antilatency.getData(data);
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	font.drawString("Antilatency OSC", 40, 60);

	if (!flag_visualize)return;

	int rectWidth = ofGetWindowWidth() * 0.8;
	int rectHeight = 15;
	
	ofPushMatrix();
	ofTranslate(50, 100);
	ofDrawBitmapString("CONECTIVITY;", 0, 0);
	switch (data.altStatus)
	{
	case 0:
		ofDrawBitmapStringHighlight("connecting", 100, 0, ofColor::yellow);
		break;
	case 1:
		ofDrawBitmapStringHighlight("not connected", 100, 0, ofColor::red, ofColor::black);
		break;
	case 2:
		ofDrawBitmapStringHighlight("connected", 100, 0, ofColor::green, ofColor::black);
		break;
	}
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(50, 130);
	ofDrawBitmapString("STATUS;", 0, 0);
	switch (data.stability_stage)
	{
	case 0:
		ofDrawBitmapStringHighlight("INITIALIZATION", 60, 0, ofColor::red);
		break;
	case 1:
		ofDrawBitmapStringHighlight("3DoF", 60, 0, ofColor::yellow, ofColor::black);
		break;
	case 2:
		ofDrawBitmapStringHighlight("6DoF", 60, 0, ofColor::green, ofColor::black);
		break;
	case 3:
		ofDrawBitmapStringHighlight("6DoF BLIND", 60, 0, ofColor::yellow, ofColor::black);
		break;
	}

	ofDrawBitmapString("STABILITY;", 120, 0);
	float value = ofMap(data.stability, 0, 2, 0, 1, true);
	drawSlider2(value, 210, -rectHeight + 3, 680, rectHeight);
	ofSetColor(0);
	ofDrawBitmapString(ofToString(data.stability), 220, 0);
	ofSetColor(255);
	ofPopMatrix();

	ofSetColor(150);
	ofDrawLine(80, 180, ofGetWidth() - 160, 180);
	ofSetColor(255);

	ofPushMatrix();
	ofTranslate(30, 230);
	{
		int x = 0, y = 0;
		float value = data.position.x;
		string title = "tx";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -3, 3, -1, 1, true), x, y+10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 50;
		float value = data.position.y;
		string title = "ty";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -3, 3, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 100;
		float value = data.position.z;
		string title = "tz";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -3, 3, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 150;
		float value = data.rotation.x;
		string title = "rx";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -PI, PI, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 200;
		float value = data.rotation.y;
		string title = "ry";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -PI, PI, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 250;
		float value = data.rotation.z;
		string title = "rz";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -PI, PI, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}
	{
		int x = 0, y = 300;
		float value = data.rotation.w;
		string title = "rw";
		drawStr(title, value, x, y);
		drawSlider(ofMap(value, -PI, PI, -1, 1, true), x, y + 10, rectWidth, rectHeight);
	}

	ofSetColor(150);
	ofDrawLine(80, 350, ofGetWidth() - 160, 350);
	ofSetColor(255);

	{
		int x = 30, y = 400;
		float value = data.acc.x;
		string title = "acc_x";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -2, 2, -1, 1, true), x+100, y-10, rectWidth/3, rectHeight);
	}
	{
		int x = 30, y = 450;
		float value = data.acc.y;
		string title = "acc_y";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -2, 2, -1, 1, true), x + 100, y - 10, rectWidth / 3, rectHeight);
	}
	{
		int x = 30, y = 500;
		float value = data.acc.z;
		string title = "acc_z";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -2, 2, -1, 1, true), x + 100, y - 10, rectWidth / 3, rectHeight);
	}
	{
		int x = ofGetWidth()/2 + 30, y = 400;
		float value = data.angularAcc.x;
		string title = "acc_rot_x";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -5, 5, -1, 1, true), x + 100, y - 10, rectWidth / 3, rectHeight);
	}
	{		
		int x = ofGetWidth() / 2 + 30, y = 450;
		float value = data.angularAcc.y;
		string title = "acc_rot_y";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -5, 5, -1, 1, true), x + 100, y - 10, rectWidth / 3, rectHeight);
	}
	{
		int x = ofGetWidth() / 2 + 30, y = 500;
		float value = data.angularAcc.z;
		string title = "acc_rot_z";
		drawStr(title, value, x, y);
		drawSlider3(ofMap(value, -5, 5, -1, 1, true), x + 100, y - 10, rectWidth / 3, rectHeight);
	}


	ofPopMatrix();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's')antilatency.stopThread();
	if (key == 'v') flag_visualize = !flag_visualize;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
