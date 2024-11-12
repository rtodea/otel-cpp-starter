#ifndef TRACER_PROVIDER_H
#define TRACER_PROVIDER_H

#include <memory>
#include "Tracer.h" // Assuming Tracer.h is the header file for the Tracer class

class TracerProvider {
private:
    std::shared_ptr<Tracer> tracerInstance;
    TracerProvider() = default;

public:
    static TracerProvider& getInstance();
    std::shared_ptr<Tracer> getTracer();
};

#endif // TRACER_PROVIDER_H