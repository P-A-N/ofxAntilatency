#pragma once
//
//
//  Created by Hiroyuki Hori PAN Co Ltd
//

#include "ofMain.h"


#include <Antilatency.InterfaceContract.LibraryLoader.h>
#include <Antilatency.DeviceNetwork.h>



namespace ofx
{
	namespace Antilatency
	{
		struct Data
		{
			int altStatus = 0; // 0: Preparing, 1: Not connected, 2: Connected
			glm::vec3 position;
			glm::vec4 rotation;
			glm::vec3 acc;
			glm::vec3 angularAcc;
			int stability_stage;
			float stability;
		};

		struct Setting
		{
			string environment;
			string nextEnvironment;
			string placement;
			float extrapolateTime;
			int trackingIntervalMilliseconds;


			void printConfig() {
				ofLog() << "Config:";
				ofLog() << "\tEnvironment: " << environment;
				ofLog() << "\tnextEnvironment: " << nextEnvironment;
				ofLog() << "\tPlacement: " << placement;
				ofLog() << "\tExtrapolateTime: " << extrapolateTime;
				ofLog() << "\tTrackingIntervalMilliseconds: " << trackingIntervalMilliseconds;
			}
		};
	}
}

class ofxAntilatency : public ofThread
{
public:
	void setup(ofx::Antilatency::Setting& setting);
	void threadedFunction();
	void start();

	Antilatency::DeviceNetwork::NodeHandle getIdleTrackingNode(Antilatency::DeviceNetwork::INetwork network, Antilatency::Alt::Tracking::ITrackingCotaskConstructor altTrackingCotaskConstructor);
	void printTrackingStateLong(Antilatency::Alt::Tracking::State& state);
	void printTrackingStateShort(Antilatency::Alt::Tracking::State& state);
	void printTrackingState(Antilatency::Alt::Tracking::State& state);

	void getData(ofx::Antilatency::Data& data)
	{
		lock();
		data = this->data;
		unlock();
	}



private:
	ofx::Antilatency::Setting setting;
	ofx::Antilatency::Data data;

	Antilatency::DeviceNetwork::INetwork network;
	Antilatency::Alt::Tracking::ITrackingCotaskConstructor altTrackingCotaskConstructor;
	Antilatency::DeviceNetwork::ILibrary deviceNetworkLibrary;
	Antilatency::Alt::Tracking::ILibrary altTrackingLibrary;
	Antilatency::Alt::Environment::Selector::ILibrary environmentSelectorLibrary;
	Antilatency::DeviceNetwork::IDeviceFilter filter;
	Antilatency::Alt::Environment::IEnvironment environment;
	Antilatency::Math::floatP3Q placement;


	// Each time the device network is changed due to connection or disconnection of a device that matches the device filter of the network,
	// or start or stop of a task on any network device, the network update id is incremented by 1. 
	int prevUpdateId = 0;

	int trackingLogLevel = 0;
	float extrapolateTime = 0.03f;
	int trackingIntervalMilliseconds = 8;
};