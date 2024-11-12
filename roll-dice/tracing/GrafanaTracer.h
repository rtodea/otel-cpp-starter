#ifndef GRAFANA_TRACER_H
#define GRAFANA_TRACER_H

#include "Tracer.h"
#include <opentelemetry/trace/span.h>
#include <opentelemetry/trace/tracer.h>
#include <opentelemetry/context/context.h>
#include <map>
#include <memory>

using namespace opentelemetry::trace;
using namespace opentelemetry::context;

class GrafanaTracer : public Tracer {
private:
    std::map<std::string, std::shared_ptr<Span>> spanMap;
    std::shared_ptr<Span> roomSpan;
    std::shared_ptr <Tracer> tracer;

    std::shared_ptr<Span> createRoomSpan(const std::string &roomId, const std::string &endpointId, const std::string &userId);
    Context forceGetRoomContext();
    std::shared_ptr<Span> openSpanWithinRoomSpan(const std::string &spanLabel);

public:
    GrafanaTracer(const std::string &roomId, const std::string &endpointId, const std::string &userId);
    void openSpan(const std::string &spanLabel) override;
    void closeSpan(const std::string &spanLabel) override;
    void setAttribute(const std::string &spanLabel, const std::string &key, const std::string &value) override;
    void start() override;
    void stop() override;
};

#endif // GRAFANA_TRACER_H