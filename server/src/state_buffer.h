#pragma once

#include <mutex>
#include <unordered_map>

namespace buttonbox {
    struct InfoBase {
    char title[256];
};
// Full documentation on all these fields are here:
// http://www.prepar3d.com/SDKv3/LearningCenter/utilities/variables/simulation_variables.html#Aircraft%20Autopilot%20Variables
struct AutopilotInfo : public InfoBase {
    bool autopilotAvailable, autopilotMaster, autopilotFlightDirectorActive;
};

/**
 * A thread-safe shared state buffer. The idea is that a SimAPI object running in one thread will
 * continually poll the MSFS server to get information about the user's aircraft and fill this
 * buffer with data; meanwhile, when an HTTP client wants information about the current aircraft
 * state, it can query that StateBuffer object to retreive it.
 */
class StateBuffer {
public:
    StateBuffer() = default;

    template <typename T>
    T getStateByName(const std::string& name) {
        static_assert(std::is_base_of<InfoBase, T>::value);

        std::lock_guard<std::mutex> guard(_accessMutex);
        // TODO @tanmay handle errors
        auto data = _data.at(name);
        return static_cast<T>(*data);
    }

    template <typename T>
    void setStateByName(const std::string& name, const T& data) {
        static_assert(std::is_base_of<InfoBase, T>::value);

        std::lock_guard<std::mutex> guard(_accessMutex);
        _data.insert({name, std::make_shared<T>(data)});
    }

private:
    std::mutex _accessMutex;

    std::unordered_map<std::string, std::shared_ptr<InfoBase>> _data;
};
} // namespace buttonbox