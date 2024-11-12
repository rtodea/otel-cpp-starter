#include "TracerProvider.h"
#include "DummyTracer.h"
#include "GrafanaTracer.h"
#include <cstdlib> // for std::getenv

TracerProvider &TracerProvider::getInstance() {
    static TracerProvider instance;
    return instance;
}

std::shared_ptr <Tracer> TracerProvider::getTracer() {
    if (!tracerInstance) {
        // Check for OTEL_* environment variables
        if (std::getenv("OTEL_EXPORTER_OTLP_ENDPOINT") \
 && std::getenv("OTEL_EXPORTER_OTLP_HEADERS") \
 && std::getenv("OTEL_RESOURCE_ATTRIBUTES")) {
            // Create GrafanaTracer instance
            TraceService traceService;
            tracerInstance = std::make_shared<GrafanaTracer>("room1", "endpoint1", "user1");
        } else {
            // Create DummyTracer instance
            tracerInstance = std::make_shared<DummyTracer>();
        }
    }
    return tracerInstance;
}