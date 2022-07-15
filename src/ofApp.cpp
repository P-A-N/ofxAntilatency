#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
#if defined(__linux__)
	Dl_info dlinfo;
	dladdr(reinterpret_cast<void*>(&main), &dlinfo);
	std::string path = getParentPath(dlinfo.dli_fname);
	std::string libNameADN = path + "/libAntilatencyDeviceNetwork.so";
	std::string libNameTracking = path + "/libAntilatencyAltTracking.so";
	std::string libNameEnvironmentSelector = path + "/libAntilatencyAltEnvironmentSelector.so";
#else
	std::string libNameADN = "AntilatencyDeviceNetwork";
	std::string libNameTracking = "AntilatencyAltTracking";
	std::string libNameEnvironmentSelector = "AntilatencyAltEnvironmentSelector";
#endif


	// Load the Antilatency Device Network library
	Antilatency::DeviceNetwork::ILibrary deviceNetworkLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::DeviceNetwork::ILibrary>(libNameADN.c_str());
	if (deviceNetworkLibrary == nullptr) {
		std::cout << "Failed to get Antilatency Device Network Library" << std::endl;
	}

	// Load the Antilatency Alt Tracking library
	Antilatency::Alt::Tracking::ILibrary altTrackingLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::Alt::Tracking::ILibrary>(libNameTracking.c_str());
	if (altTrackingLibrary == nullptr) {
		std::cout << "Failed to get Antilatency Alt Tracking Library" << std::endl;
	}

	// Load the Antilatency Alt Environment Selector library
	Antilatency::Alt::Environment::Selector::ILibrary environmentSelectorLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::Alt::Environment::Selector::ILibrary>(libNameEnvironmentSelector.c_str());
	if (environmentSelectorLibrary == nullptr) {
		std::cout << "Failed to get Antilatency Alt Environment Selector Library" << std::endl;
	}

	// Create a device network filter and then create a network using that filter.
	Antilatency::DeviceNetwork::IDeviceFilter filter = deviceNetworkLibrary.createFilter();
	filter.addUsbDevice(Antilatency::DeviceNetwork::Constants::AllUsbDevices);
	Antilatency::DeviceNetwork::INetwork network = deviceNetworkLibrary.createNetwork(filter);
	if (network == nullptr) {
		std::cout << "Failed to create Antilatency Device Network" << std::endl;
	}
	std::cout << "Antilatency Device Network created" << std::endl;

	//// Get environment serialized data.
	//const std::string environmentData = argv[1];
	//// Get placement serialized data.
	//const std::string placementData = argv[2];

	//// Create environment object from the serialized data.
	//const Antilatency::Alt::Environment::IEnvironment environment = environmentSelectorLibrary.createEnvironment(environmentData);
	//if (environment == nullptr) {
	//	std::cout << "Failed to create environment" << std::endl;
	//}

	//// Create placement from the serialized data.
	//const Antilatency::Math::floatP3Q placement = altTrackingLibrary.createPlacement(placementData);

	//// Create alt tracking cotask constructor to find tracking-supported nodes and start tracking task on node.
	//Antilatency::Alt::Tracking::ITrackingCotaskConstructor altTrackingCotaskConstructor = altTrackingLibrary.createTrackingCotaskConstructor();
	//if (altTrackingCotaskConstructor == nullptr) {
	//	std::cout << "Failed to create Antilatency Alt Tracking Cotask Constructor" << std::endl;
	//}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
