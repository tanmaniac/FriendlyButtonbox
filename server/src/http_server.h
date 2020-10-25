#pragma once

#include <httplib.h>

#include <memory>
#include <thread>

namespace buttonbox {
class HTTPServer {
public:
    HTTPServer() = default;
    ~HTTPServer() {
        if (_server.is_running()) {
            _server.stop();
        }

        if (_listeningThread) {
            _listeningThread->join();
        }
    }

    void startListening(const std::string& host, int port);

private:
    httplib::Server _server;
    std::unique_ptr<std::thread> _listeningThread;
};
} // namespace buttonbox