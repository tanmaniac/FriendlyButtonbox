#include "http_server.h"

namespace buttonbox {
void HTTPServer::startListening(const std::string& host, int port) {
    // Do it in another thread so that we don't block
    _listeningThread = std::make_unique<std::thread>([&]() {
        std::cout << "Ready for requests at host " << host << ":" << port << std::endl;
        this->_server.listen(host.c_str(), port);
    });
}
} // namespace buttonbox