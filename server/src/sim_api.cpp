#include "sim_api.h"

namespace buttonbox {
void CALLBACK dispatchProcRd(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
    // the pContext pointer is set to a pointer to a simconnect handle
    HANDLE* simConnectHandlePtr = reinterpret_cast<HANDLE*>(pContext);
    HANDLE& simConnectHandle = *simConnectHandlePtr;

    HRESULT hr;
    switch (pData->dwID) {
    case SIMCONNECT_RECV_ID_EVENT: {
        SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;
        switch (evt->uEventID) {
        case EVERY_SECOND:
            // Request information on the user aircraft
            hr = SimConnect_RequestDataOnSimObjectType(simConnectHandle,
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
                std::cout << "Has autopilot = " << pAPStruct->autopilotAvailable << std::endl;
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
} // namespace buttonbox