#include "http_server.h"
#include "sim_api.h"

#include <iostream>

int main() {
	std::cout << "Hello world" << std::endl;

	// Start http server
    buttonbox::HTTPServer server;
    server.startListening("localhost", 69420);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}