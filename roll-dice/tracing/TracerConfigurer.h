#ifndef ROLLDICESERVER_TRACERCONFIGURER_H
#define ROLLDICESERVER_TRACERCONFIGURER_H

#include <string>
#include <unordered_map>

class TracerConfigurer {
public:
    static TracerConfigurer& getInstance();

    void setProperty(const std::string &key, const std::string &value);
    std::string getProperty(const std::string &key) const;

private:
    TracerConfigurer() = default;
    TracerConfigurer(const TracerConfigurer&) = delete;
    TracerConfigurer& operator=(const TracerConfigurer&) = delete;

    std::unordered_map<std::string, std::string> properties;
};

#endif //ROLLDICESERVER_TRACERCONFIGURER_H
