#include <opentelemetry/trace/context.h>
#include "GrafanaTracer.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;
namespace otlp = opentelemetry::exporter::otlp;

// From the documentation:
void InitTracer() {
    otlp::OtlpHttpExporterOptions opts;
    auto exporter  = otlp::OtlpHttpExporterFactory::Create(opts);
    auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
    auto resource = opentelemetry::sdk::resource::Resource::Create(
            {{"service.name", "gstreamer"}});
    std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
            trace_sdk::TracerProviderFactory::Create(std::move(processor), resource);
    std::shared_ptr<opentelemetry::trace::TracerProvider> api_provider = provider;
    trace_api::Provider::SetTracerProvider(api_provider);
}

void CleanupTracer() {
    std::shared_ptr<opentelemetry::trace::TracerProvider> none;
    trace_api::Provider::SetTracerProvider(none);
}

GrafanaTracer::GrafanaTracer(const std::string &roomId, const std::string &endpointId, const std::string &userId) {
    InitTracer();
    tracer = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("gstreamer-tracer");
    roomSpan = createRoomSpan(roomId, endpointId, userId);
}

GrafanaTracer::~GrafanaTracer() {
    CleanupTracer();
}

opentelemetry::nostd::shared_ptr<Span> GrafanaTracer::createRoomSpan(const std::string &roomId, const std::string &endpointId, const std::string &userId) {
    auto span = tracer->StartSpan("RoomCall");
    span->SetAttribute("RoomId", roomId);
    span->SetAttribute("EndpointId", endpointId);
    span->SetAttribute("UserId", userId);
    return span;
}

Context GrafanaTracer::forceGetRoomContext() {
    // TODO(robert): Correctly get the context of the room span
    // return SetSpan(Context::GetCurrent(), roomSpan);
    auto context = opentelemetry::context::RuntimeContext::GetCurrent();
    return SetSpan(context, roomSpan);
}

opentelemetry::nostd::shared_ptr<Span> GrafanaTracer::openSpanWithinRoomSpan(const std::string &spanLabel) {
    // auto roomSpanContext = forceGetRoomContext();
    // return tracer->StartSpan(spanLabel, {}, roomSpanContext);
    trace_api::StartSpanOptions options;
    options.parent = roomSpan->GetContext();
    return tracer->StartSpan(spanLabel, options);
}

void GrafanaTracer::openSpan(const std::string &spanLabel) {
    auto newSpan = openSpanWithinRoomSpan(spanLabel);
    spanMap[spanLabel] = newSpan;
}

void GrafanaTracer::closeSpan(const std::string &spanLabel) {
    auto it = spanMap.find(spanLabel);
    if (it != spanMap.end()) {
        it->second->End();
        spanMap.erase(it);
    }
}

void GrafanaTracer::setAttribute(const std::string &spanLabel, const std::string &key, const std::string &value) {
    auto it = spanMap.find(spanLabel);
    if (it != spanMap.end()) {
        it->second->SetAttribute(key, value);
    }
}