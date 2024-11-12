#ifndef ROLLDICESERVER_TRACERCONFIG_H
#define ROLLDICESERVER_TRACERCONFIG_H

#include <string>
#include <unordered_map>

class TracerConfig {
public:
    static TracerConfig& getInstance();

    void setProperty(const std::string &key, const std::string &value);
    std::string getProperty(const std::string &key) const;

private:
    TracerConfig() = default;
    TracerConfig(const TracerConfig&) = delete;
    TracerConfig& operator=(const TracerConfig&) = delete;

    std::unordered_map<std::string, std::string> properties;
};

#endif //ROLLDICESERVER_TRACERCONFIG_H
