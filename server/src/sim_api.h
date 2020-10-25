#pragma once

// Typically system headers should come after project-specific ones and right before stdc++ ones.
// But windows is such a mess that you *have* to order headers like this for stuff to even compile.
// TODO @Satya Nadella pls fix
#include <stdio.h>
#include <strsafe.h>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

#include "SimConnect.h"

#include <iostream>
#include <thread>

namespace buttonbox {
enum DataDefineID {
    AUTOPILOT_DATA_DEFINITION,
};

enum DataRequestID {
    AUTOPILOT_DATA_REQUEST,
};

enum EventID {
    EVERY_SECOND,
};

struct AutopilotInfo {
    char title[256];
    bool autopilotAvailable, autopilotFlightDirectorActive;
};

void CALLBACK dispatchProcRd(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);

class SimAPI {
public:
    SimAPI(const std::string& appName) {
        while (SimConnect_Open(&_simConnectHandle, appName.c_str(), NULL, 0, 0, 0) != S_OK) {
            std::cout << "Waiting to connect..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "Enabling data definitions..." << std::endl;

        auto hr = SimConnect_AddToDataDefinition(
            _simConnectHandle, AUTOPILOT_DATA_DEFINITION, "Autopilot available", "bool");
        hr = SimConnect_AddToDataDefinition(_simConnectHandle,
                                            AUTOPILOT_DATA_DEFINITION,
                                            "Autopilot flight director active",
                                            "bool");

        hr = SimConnect_SubscribeToSystemEvent(_simConnectHandle, EVERY_SECOND, "1sec");

        while (true) {
            SimConnect_CallDispatch(_simConnectHandle, dispatchProcRd, &_simConnectHandle);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Just vibin" << std::endl;
        }
    }

    ~SimAPI() {
        if (SimConnect_Close(_simConnectHandle) == S_OK) {
            std::cout << "Disconnected successfully!" << std::endl;
        }
    }

private:
    HANDLE _simConnectHandle;
};
} // namespace buttonbox