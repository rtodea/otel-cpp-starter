#ifndef DUMMY_TRACER_H
#define DUMMY_TRACER_H

#include "AppTracer.h"
#include <map>

class DummyTracer : public AppTracer {
private:
    std::map<std::string, std::string> spanMap;
    void log(const std::string &message);

public:
    void openSpan(const std::string &spanLabel) override;
    void closeSpan(const std::string &spanLabel) override;
    void setAttribute(const std::string &spanLabel, const std::string &key, const std::string &value) override;
};

#endif // DUMMY_TRACER_H