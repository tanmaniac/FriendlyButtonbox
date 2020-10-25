cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(FriendlyButtonboxServer LANGUAGES CXX)

###################
# Third party
###################
add_subdirectory(third-party)

# cpp-httplib, for our RESTful server
include_directories(third-party/cpp-httplib)

# Simconnect, for actually connecting to Microsoft Flight Simulator
# You might need to change the path to this
set(SIMCONNECT_INSTALL_DIR "C:/Program Files/MSFS_SDK/SimConnect SDK")
include_directories("${SIMCONNECT_INSTALL_DIR}/include")
link_directories("${SIMCONNECT_INSTALL_DIR}/lib")

find_library(SIMCONNECT_LIBRARY
		     NAMES SimConnect
			 PATHS
				"${SIMCONNECT_INSTALL_DIR}/lib")

###################
# Libs and exes
###################
add_executable(main src/main.cpp 
					src/sim_api.cpp 
					src/http_server.cpp)
target_link_libraries(main ${SIMCONNECT_LIBRARY})
file(COPY ${SIMCONNECT_INSTALL_DIR}/lib/SimConnect.dll DESTINATION ${PROJECT_BINARY_DIR})