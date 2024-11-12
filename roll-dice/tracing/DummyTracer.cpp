#include "DummyTracer.h"
#include <iostream>

void DummyTracer::log(const std::string &message) {
    std::cout << message << std::endl;
}

void DummyTracer::openSpan(const std::string &spanLabel) {
    log("Opening span: " + spanLabel);
}

void DummyTracer::closeSpan(const std::string &spanLabel) {
    log("Closing span: " + spanLabel);
}

void DummyTracer::setAttribute(const std::string &spanLabel, const std::string &key, const std::string &value) {
    log("Setting attribute for span " + spanLabel + ": " + key + " = " + value);
}
