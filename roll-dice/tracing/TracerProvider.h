#ifndef TRACER_PROVIDER_H
#define TRACER_PROVIDER_H

#include <memory>
#include "AppTracer.h" // Assuming Tracer.h is the header file for the Tracer class

class TracerProvider {
private:
    std::shared_ptr<AppTracer> tracerInstance;
    TracerProvider() = default;

public:
    static TracerProvider& getInstance();
    std::shared_ptr<AppTracer> getTracer();
};

#endif // TRACER_PROVIDER_H