#include "http_server.h"

namespace buttonbox {
void HTTPServer::startListening(const std::string& address, int port) {
    std::cout << "Ready for requests at host " << address << ":" << port << std::endl;
    _server.listen(address.c_str(), port);
    // Do it in another thread so that we don't block
    /*_listeningThread = std::make_unique<std::thread>([&]() {
        std::cout << "Ready for requests at host " << address << ":" << port << std::endl;
        this->_server.listen(address.c_str(), port);
    });*/
}
} // namespace buttonbox