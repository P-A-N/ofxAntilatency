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
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's')antilatency.stopThread();
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
