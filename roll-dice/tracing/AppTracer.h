#ifndef TRACER_H
#define TRACER_H

#include <string>

class AppTracer {
public:
    virtual ~AppTracer() = default;
    virtual void openSpan(const std::string &spanLabel) = 0;
    virtual void closeSpan(const std::string &spanLabel) = 0;
    virtual void setAttribute(const std::string &spanLabel, const std::string &key, const std::string &value) = 0;
};

#endif // TRACER_H
