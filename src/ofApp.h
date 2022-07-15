#pragma once

#include "ofMain.h"
#include <Antilatency.InterfaceContract.LibraryLoader.h>
#include <Antilatency.DeviceNetwork.h>


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

	std::string oscOutAddress = "169.254.8.63";
	int oscOutPort = 10000;
	int oscInPort = 10001;
	std::string initialEnvironmentData = "AntilatencyAltEnvironmentHorizontalGrid~AgZ5ZWxsb3cEBLhTiT_cRqA-r45jvZqZmT4AAAAAAAAAAACamRk_AQQAAQEBAwABAAADAQE";
	std::string placementData = "AAAAAAAAAAAAAAAAAAAAAIAAAAAAAAAAAA";
	float extrapolateTime = 0.03f;
	int trackingIntervalMilliseconds = 8;
	int statusOscIntervalMilliseconds = 100;
	int trackingLogLevel = 0;
	bool enableReboot = false;

	float angleAccX = 0;
	float angleAccY = 0;
	float angleAccZ = 0;
	int sameValueCounter = 0;
	int rebootThresh = 10;
	int altStatus = 0; // 0: Preparing, 1: Not connected, 2: Connected

private:
	void printConfig() {
		std::cout << "Config:" << std::endl;
		std::cout << "\tOscOutAddress: " << oscOutAddress << std::endl;
		std::cout << "\tOscOutPort: " << oscOutPort << std::endl;
		std::cout << "\tOscInPort: " << oscInPort << std::endl;
		std::cout << "\tEnvironment: " << initialEnvironmentData << std::endl;
		std::cout << "\tPlacement: " << placementData << std::endl;
		std::cout << "\tExtrapolateTime: " << extrapolateTime << std::endl;
		std::cout << "\tTrackingIntervalMilliseconds: " << trackingIntervalMilliseconds << std::endl;
		std::cout << "\tStatusOscIntervalMilliseconds: " << statusOscIntervalMilliseconds << std::endl;
		std::cout << "\tTrackingLogLevel: " << trackingLogLevel << std::endl;
		std::cout << "\tenableReboot: " << enableReboot << std::endl;
		std::cout << "\trebootThresh: " << rebootThresh << std::endl;
	}


	Antilatency::DeviceNetwork::NodeHandle getIdleTrackingNode(Antilatency::DeviceNetwork::INetwork network, Antilatency::Alt::Tracking::ITrackingCotaskConstructor altTrackingCotaskConstructor) {
		// Get all currently connected nodes, that supports alt tracking task.
		std::vector<Antilatency::DeviceNetwork::NodeHandle> altNodes = altTrackingCotaskConstructor.findSupportedNodes(network);
		if (altNodes.size() == 0) {
			std::cout << "No nodes with Alt Tracking Task support found" << std::endl;
			return Antilatency::DeviceNetwork::NodeHandle::Null;
		}

		// Return first idle node.
		for (auto node : altNodes) {
			if (network.nodeGetStatus(node) == Antilatency::DeviceNetwork::NodeStatus::Idle) {
				return node;
			}
		}

		std::cout << "No idle nodes with Alt Tracking Task support found" << std::endl;
		return Antilatency::DeviceNetwork::NodeHandle::Null;
	}

	void printTrackingStateLong(Antilatency::Alt::Tracking::State& state) {
		std::cout << "State:" << std::endl;
		std::cout << "\tPose:" << std::endl;
		std::cout << "\t\tPosition: x: " << state.pose.position.x << ", y: " << state.pose.position.y << ", z: " << state.pose.position.z << std::endl;
		std::cout << "\t\tRotation: x: " << state.pose.rotation.x << ", y: " << state.pose.rotation.y << ", z: " << state.pose.rotation.z << ", w: " << state.pose.rotation.w << std::endl;
		std::cout << "\tStability:" << std::endl;
		std::cout << "\t\tStage: " << static_cast<int32_t>(state.stability.stage) << std::endl;
		std::cout << "\t\tValue: " << state.stability.value << std::endl;
		std::cout << "\tVelocity:" << state.velocity.x << ", y: " << state.velocity.y << ", z: " << state.velocity.z << std::endl;
		std::cout << "\tLocalAngularVelocity: x:" << state.localAngularVelocity.x << ", y: " << state.localAngularVelocity.y << ", z: " << state.localAngularVelocity.z << std::endl << std::endl;
	}

	void printTrackingStateShort(Antilatency::Alt::Tracking::State& state) {
		std::cout << "Alt Status" << altStatus << " Tracking Stability: " << static_cast<int32_t>(state.stability.stage) << ", " << state.stability.value << std::endl;
	}

	void printTrackingState(Antilatency::Alt::Tracking::State& state) {
		if (trackingLogLevel == 1) {
			printTrackingStateShort(state);
		}
		else if (trackingLogLevel == 2) {
			printTrackingStateLong(state);
		}
	}

	void checkValue(Antilatency::Alt::Tracking::State& state)
	{
		if (angleAccX == state.localAngularVelocity.x &&
			angleAccY == state.localAngularVelocity.y &&
			angleAccZ == state.localAngularVelocity.z &&
			state.stability.stage != Antilatency::Alt::Tracking::Stage::InertialDataInitialization)
		{
			sameValueCounter++;
		}
		else
		{
			angleAccX = state.localAngularVelocity.x;
			angleAccY = state.localAngularVelocity.y;
			angleAccZ = state.localAngularVelocity.z;
			sameValueCounter = 0;
		}
	}

#if defined(__linux__)
	std::string getParentPath(const char* inp) {
		auto len = strlen(inp);
		if (len == 0) throw std::runtime_error("no parent path: " + std::string(inp));
		int i = len - 1;
		while (i > 0) {
			if (inp[i] == '/') {
				return std::string(inp, inp + i + 1);
			}
			--i;
		}
		throw std::runtime_error("no parent path: " + std::string(inp));
	}
#endif
};
