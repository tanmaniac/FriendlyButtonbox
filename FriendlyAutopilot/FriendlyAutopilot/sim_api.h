#pragma once

#include <stdio.h>
#include <strsafe.h>
#include <tchar.h>
#include <windows.h>

#include "SimConnect.h"

#include <iostream>
#include <thread>

namespace friendlyap {
	enum DataDefineID {
		DEFINITION_1,
	};

	enum DataRequestID {
		REQUEST_1,
	};

	struct Autopilot {
		bool autopilotAvailable;
		bool autopilotFlightDirectorActive;
	};

	class SimAPI {
	public:
		SimAPI(const std::string& appName) {
			while (SimConnect_Open(&_simConnectHandle, appName.c_str(), NULL, 0, 0, 0) != S_OK) {
				std::cout << "Waiting to connect..." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			std::cout << "Enabling data definitions..." << std::endl;

			auto hr = SimConnect_AddToDataDefinition(_simConnectHandle, DEFINITION_1, "Autopilot available", "bool");
			hr = SimConnect_AddToDataDefinition(_simConnectHandle, DEFINITION_1, "Autopilot flight director active", "bool");
		}

		~SimAPI() {
			if (SimConnect_Close(_simConnectHandle) == S_OK) {
				std::cout << "Disconnected successfully!" << std::endl;
			}
		}

	private:
		HANDLE _simConnectHandle;
	};
}