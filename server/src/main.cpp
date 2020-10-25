#include "http_server.h"
#include "state_buffer.h"
#include "sim_api.h"

#include <iostream>

int main() {
	std::cout << "Hello world" << std::endl;

    std::shared_ptr<buttonbox::StateBuffer> stateBuffer = std::make_shared<buttonbox::StateBuffer>();

    std::thread simThread([&]() {
        buttonbox::SimAPI simAPI("buttonbox", stateBuffer);
    });

	// Start http server
    buttonbox::HTTPServer server;
    server.startListening("localhost", 8081);

    // Start Sim API
    //buttonbox::SimAPI simAPI("ButtonBox", stateBuffer);

    //while (true) {
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //}
}