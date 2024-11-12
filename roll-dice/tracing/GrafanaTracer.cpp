#include "GrafanaTracer.h"

GrafanaTracer::GrafanaTracer(const std::string &roomId, const std::string &endpointId, const std::string &userId) {
    tracer = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("gstreamer-tracer");
    roomSpan = createRoomSpan(roomId, endpointId, userId);
}

std::shared_ptr<Span> GrafanaTracer::createRoomSpan(const std::string &roomId, const std::string &endpointId, const std::string &userId) {
    auto span = tracer->StartSpan("RoomCall");
    span->SetAttribute("RoomId", roomId);
    span->SetAttribute("EndpointId", endpointId);
    span->SetAttribute("UserId", userId);
    return span;
}

Context GrafanaTracer::forceGetRoomContext() {
    return SetSpan(Context::GetCurrent(), roomSpan);
}

std::shared_ptr<Span> GrafanaTracer::openSpanWithinRoomSpan(const std::string &spanLabel) {
    auto roomSpanContext = forceGetRoomContext();
    return tracer->StartSpan(spanLabel, {}, roomSpanContext);
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