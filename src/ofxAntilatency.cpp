#include "ofxAntilatency.h"


void ofxAntilatency::setup(ofx::Antilatency::Setting& setting)
{
	this->setting = setting;
#if defined(__linux__)
	std::string path = "./bin/";
	std::string libNameADN = path + "libAntilatencyDeviceNetwork.so";
	std::string libNameTracking = path + "libAntilatencyAltTracking.so";
	std::string libNameEnvironmentSelector = path + "libAntilatencyAltEnvironmentSelector.so";
#else
	std::string libNameADN = "AntilatencyDeviceNetwork";
	std::string libNameTracking = "AntilatencyAltTracking";
	std::string libNameEnvironmentSelector = "AntilatencyAltEnvironmentSelector";
#endif


	// Load the Antilatency Device Network library
	deviceNetworkLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::DeviceNetwork::ILibrary>(libNameADN.c_str());
	if (deviceNetworkLibrary == nullptr) {
		ofLog() << "..Failed to get Antilatency Device Network Library";
	}

	// Load the Antilatency Alt Tracking library
	altTrackingLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::Alt::Tracking::ILibrary>(libNameTracking.c_str());
	if (altTrackingLibrary == nullptr) {
		ofLog() << "Failed to get Antilatency Alt Tracking Library";
	}

	// Load the Antilatency Alt Environment Selector library
	environmentSelectorLibrary = Antilatency::InterfaceContract::getLibraryInterface<Antilatency::Alt::Environment::Selector::ILibrary>(libNameEnvironmentSelector.c_str());
	if (environmentSelectorLibrary == nullptr) {
		ofLog() << "Failed to get Antilatency Alt Environment Selector Library";
	}

	// Create a device network filter and then create a network using that filter.
	filter = deviceNetworkLibrary.createFilter();
	filter.addUsbDevice(Antilatency::DeviceNetwork::Constants::AllUsbDevices);
	network = deviceNetworkLibrary.createNetwork(filter);
	if (network == nullptr) {
		ofLog() << "Failed to create Antilatency Device Network";
	}
	ofLog	() << "Antilatency Device Network created";

	// Create environment object from the serialized data.
	environment = environmentSelectorLibrary.createEnvironment(setting.environment);
	if (environment == nullptr) {
		ofLog() << "Failed to create environment";
	}

	// Create placement from the serialized data.
	placement = altTrackingLibrary.createPlacement(setting.placement);

	// Create alt tracking cotask constructor to find tracking-supported nodes and start tracking task on node.
	altTrackingCotaskConstructor = altTrackingLibrary.createTrackingCotaskConstructor();
	if (altTrackingCotaskConstructor == nullptr) {
		ofLog() << "Failed to create Antilatency Alt Tracking Cotask Constructor";
	}

	ofLog() << "Antilatency Setup Done";
	waitForThread(true);
}

void ofxAntilatency::start()
{
	if (network == nullptr)
	{
		ofLogError() << "network is not valid";
		return;
	}
	startThread();
}

void ofxAntilatency::threadedFunction()
{
	while (network != nullptr && isThreadRunning()) {
		// Check if the network has been changed.
		const uint32_t currentUpdateId = network.getUpdateId();

		if (prevUpdateId != currentUpdateId) {
			prevUpdateId = currentUpdateId;
			ofLog() << "--- Device network changed, update id: " << currentUpdateId << " ---";
			// Get first idle node that supports tracking task.
			const Antilatency::DeviceNetwork::NodeHandle trackingNode = getIdleTrackingNode(network, altTrackingCotaskConstructor);

			if (trackingNode != Antilatency::DeviceNetwork::NodeHandle::Null) {
				lock();
				data.altStatus = 2;
				unlock();

				// Create new environment if needed
				Antilatency::Alt::Environment::IEnvironment newEnvironment = nullptr;
				if (setting.environment != setting.nextEnvironment) {
					try {
						newEnvironment = environmentSelectorLibrary.createEnvironment(setting.nextEnvironment);
					}
					catch (std::exception & e) {
						ofLog() << "Error occurred when parsing new environment: " << e.what();
					}
					if (newEnvironment != nullptr) {
						ofLog() << "Environment changed: " << setting.nextEnvironment;
						setting.environment = newEnvironment;
						setting.environment = setting.nextEnvironment;
					}
					else {
						ofLog() << "Failed to create new environment: " << setting.nextEnvironment;
						setting.nextEnvironment = setting.environment;
					}
				}

				// Start tracking task on node.
				Antilatency::Alt::Tracking::ITrackingCotask altTrackingCotask = altTrackingCotaskConstructor.startTask(network, trackingNode, environment);
				if (altTrackingCotask != nullptr) {
					while (altTrackingCotask != nullptr && isThreadRunning()) {
						// Print the extrapolated state of node to the console every 500 ms (2FPS).
						if (altTrackingCotask.isTaskFinished()) {
							ofLog() << "Tracking task finished";
							break;
						}
						if (setting.environment != setting.nextEnvironment) {
							ofLog() << "Stop tracking task to change environment";
							break;
						}
						Antilatency::Alt::Tracking::State state = altTrackingCotask.getExtrapolatedState(placement, extrapolateTime);
						lock();
						data.position.x = state.pose.position.x;
						data.position.y = state.pose.position.y;
						data.position.z = state.pose.position.z;

						data.rotation.x = state.pose.rotation.x;
						data.rotation.y = state.pose.rotation.y;
						data.rotation.z = state.pose.rotation.z;
						data.rotation.w = state.pose.rotation.w;


						data.acc.x = state.velocity.x;
						data.acc.y = state.velocity.y;
						data.acc.z = state.velocity.z;

						data.angularAcc.x = state.localAngularVelocity.x;
						data.angularAcc.y = state.localAngularVelocity.y;
						data.angularAcc.z = state.localAngularVelocity.z;

						data.stability_stage = static_cast<int32_t>(state.stability.stage);
						data.stability = state.stability.value;

						unlock();
						printTrackingState(state);
						if(isThreadRunning()) std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(trackingIntervalMilliseconds));
					}
				}
				else {
				}
			}
		}
		else {
			lock();
			data.altStatus = 1;
			unlock();
			if(isThreadRunning())std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

Antilatency::DeviceNetwork::NodeHandle ofxAntilatency::getIdleTrackingNode(Antilatency::DeviceNetwork::INetwork network, Antilatency::Alt::Tracking::ITrackingCotaskConstructor altTrackingCotaskConstructor) {
	// Get all currently connected nodes, that supports alt tracking task.
	std::vector<Antilatency::DeviceNetwork::NodeHandle> altNodes = altTrackingCotaskConstructor.findSupportedNodes(network);
	if (altNodes.size() == 0) {
		ofLog() << "No nodes with Alt Tracking Task support found";
		return Antilatency::DeviceNetwork::NodeHandle::Null;
	}

	// Return first idle node.
	for (auto node : altNodes) {
		if (network.nodeGetStatus(node) == Antilatency::DeviceNetwork::NodeStatus::Idle) {
			return node;
		}
	}

	ofLog() << "No idle nodes with Alt Tracking Task support found";
	return Antilatency::DeviceNetwork::NodeHandle::Null;
}


void ofxAntilatency::printTrackingStateLong(Antilatency::Alt::Tracking::State& state) {
	ofLog() << "State:";
	ofLog() << "\tPose:";
	ofLog() << "\t\tPosition: x: " << state.pose.position.x << ", y: " << state.pose.position.y << ", z: " << state.pose.position.z;
	ofLog() << "\t\tRotation: x: " << state.pose.rotation.x << ", y: " << state.pose.rotation.y << ", z: " << state.pose.rotation.z << ", w: " << state.pose.rotation.w;
	ofLog() << "\tStability:";
	ofLog() << "\t\tStage: " << static_cast<int32_t>(state.stability.stage);
	ofLog() << "\t\tValue: " << state.stability.value;
	ofLog() << "\tVelocity:" << state.velocity.x << ", y: " << state.velocity.y << ", z: " << state.velocity.z;
	ofLog() << "\tLocalAngularVelocity: x:" << state.localAngularVelocity.x << ", y: " << state.localAngularVelocity.y << ", z: " << state.localAngularVelocity.z << std::endl;
}

void ofxAntilatency::printTrackingStateShort(Antilatency::Alt::Tracking::State& state) {
	lock();
	ofLog() << "Alt Status" << data.altStatus << " Tracking Stability: " << static_cast<int32_t>(state.stability.stage) << ", " << state.stability.value;
	unlock();
}

void ofxAntilatency::printTrackingState(Antilatency::Alt::Tracking::State& state) {
	if (trackingLogLevel == 1) {
		printTrackingStateShort(state);
	}
	else if (trackingLogLevel == 2) {
		printTrackingStateLong(state);
	}
}
