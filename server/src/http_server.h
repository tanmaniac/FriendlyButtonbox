#pragma once

#include <httplib.h>

#include <memory>
#include <thread>

namespace buttonbox {
class HTTPServer {
public:
    HTTPServer() {
        _server.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
            res.set_content("Hello World!", "text/plain");
        });
    }

    ~HTTPServer() {
        if (_server.is_running()) {
            _server.stop();
        }

        if (_listeningThread) {
            _listeningThread->join();
        }
    }

    void startListening(const std::string& address, int port);

private:
    httplib::Server _server;
    std::unique_ptr<std::thread> _listeningThread;
};
} // namespace buttonbox