# Friendly Buttonbox

A REST API and web interface for controlling Microsoft Flight Simulator from another device.

## Getting started

1. Install VS Code for Windows
2. Install the Microsoft Visual C++ compiler by following these directions: https://code.visualstudio.com/docs/cpp/config-msvc. Make sure to install the Desktop C++ workload, which also includes CMake.
3. Launch the `Developer Command Prompt for VS 2019` from the start menu and navigate to this directory
4. Run `cmake`:

```shell
cd server
mkdir build
cd build
cmake ..
```

5. Build the code:

```shell
cmake --build .
```

You'll get an output like 

```shell
>cmake --build .
Microsoft (R) Build Engine version 16.8.3+39993bd9d for .NET Framework
Copyright (C) Microsoft Corporation. All rights reserved.

  Checking Build System
  Building Custom Rule C:/Users/Tanmay/Projects/FriendlyButtonbox/server/CMakeLists.txt
  main.cpp
  sim_api.cpp
  http_server.cpp
  Generating Code...
  main.vcxproj -> C:\Users\Tanmay\Projects\FriendlyButtonbox\server\build\Debug\main.exe
  Building Custom Rule C:/Users/Tanmay/Projects/FriendlyButtonbox/server/CMakeLists.txt
```

6. Now you can run the simconnect server with 

```shell
> Debug\main.exe
Ready for requests at host localhost:8081
Waiting to connect...
Waiting to connect...
```