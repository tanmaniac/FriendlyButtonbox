#include "sim_api.h"

namespace buttonbox {
void CALLBACK dispatchProcRd(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
    // the pContext pointer is set to a pointer to a simconnect handle
    //HANDLE* simConnectHandlePtr = reinterpret_cast<HANDLE*>(pContext);
    //HANDLE& simConnectHandle = *simConnectHandlePtr;
    SimAPI* simAPI = static_cast<SimAPI*>(pContext);

    HRESULT hr;
    switch (pData->dwID) {
    case SIMCONNECT_RECV_ID_EVENT: {
        SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;
        switch (evt->uEventID) {
        case EVERY_SECOND:
            // Request information on current autopilot status
            hr = SimConnect_RequestDataOnSimObjectType(simAPI->_simConnectHandle,
                                                       AUTOPILOT_DATA_REQUEST,
                                                       AUTOPILOT_DATA_DEFINITION,
                                                       0,
                                                       SIMCONNECT_SIMOBJECT_TYPE_USER);
            break;
        default:
            break;
        }
        break;
    }
    case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE: {
        auto* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;
        switch (pObjData->dwRequestID) {
        case AUTOPILOT_DATA_REQUEST: {
            DWORD ObjectID = pObjData->dwObjectID;
            AutopilotInfo* pAPStruct = (AutopilotInfo*)&pObjData->dwData;
            // Security check
            if (SUCCEEDED(StringCbLengthA(&pAPStruct->title[0], sizeof(pAPStruct->title), NULL))) {
                simAPI->_stateBuffer->setStateByName("AutopilotState", *pAPStruct);
                std::cout << "Has autopilot = " << pAPStruct->autopilotAvailable << std::endl;
                std::cout << "Autopilot active: " << pAPStruct->autopilotMaster << std::endl;
                std::cout << "FD active = " << pAPStruct->autopilotFlightDirectorActive
                          << std::endl;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    }
}

//------------- SimAPI member function definitions --------------
HRESULT SimAPI::addAutopilotDataDefinitions() {
    HRESULT hr = SimConnect_AddToDataDefinition(
        _simConnectHandle, AUTOPILOT_DATA_DEFINITION, "Autopilot available", "bool");
    hr = SimConnect_AddToDataDefinition(
        _simConnectHandle, AUTOPILOT_DATA_DEFINITION, "Autopilot master", "bool");
    hr = SimConnect_AddToDataDefinition(
        _simConnectHandle, AUTOPILOT_DATA_DEFINITION, "Autopilot flight director active", "bool");

    return hr;
}
} // namespace buttonbox