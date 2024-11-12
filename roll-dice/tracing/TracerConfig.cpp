#include "TracerConfig.h"

TracerConfig& TracerConfig::getInstance() {
    static TracerConfig instance;
    return instance;
}

void TracerConfig::setProperty(const std::string &key, const std::string &value) {
    properties[key] = value;
}

std::string TracerConfig::getProperty(const std::string &key) const {
    auto it = properties.find(key);
    if (it != properties.end()) {
        return it->second;
    }
    return "";
}
