#include "TracerConfigurer.h"

TracerConfigurer& TracerConfigurer::getInstance() {
    static TracerConfigurer instance;
    return instance;
}

void TracerConfigurer::setProperty(const std::string &key, const std::string &value) {
    properties[key] = value;
}

std::string TracerConfigurer::getProperty(const std::string &key) const {
    auto it = properties.find(key);
    if (it != properties.end()) {
        return it->second;
    }
    return "";
}
