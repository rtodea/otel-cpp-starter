#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace trace_exporter = opentelemetry::exporter::trace;
namespace otlp = opentelemetry::exporter::otlp;

namespace {
    void InitTracer() {
        otlp::OtlpHttpExporterOptions opts;
        opts.url = "https://otlp-gateway-prod-us-east-0.grafana.net/otlp";
        auto otlp_exporter = otlp::OtlpHttpExporterFactory::Create(opts);
        auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(otlp_exporter));
        // Create a resource with the necessary attributes
        auto resource = opentelemetry::sdk::resource::Resource::Create(
                {{"service.name", "gstreamer"}});
        std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
                trace_sdk::TracerProviderFactory::Create(std::move(processor), resource);

        //set the global trace provider
        trace_api::Provider::SetTracerProvider(provider);
    }

    void CleanupTracer() {
        std::shared_ptr<opentelemetry::trace::TracerProvider> none;
        trace_api::Provider::SetTracerProvider(none);
    }

}

class Handler : public oatpp::web::server::HttpRequestHandler {
public:
    shared_ptr <OutgoingResponse> handle(const shared_ptr <IncomingRequest> &request) override {
        auto tracer = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("gstreamer-tracer");
        auto span = tracer->StartSpan("RollDiceServer");
        int low = 1;
        int high = 7;
        int random = rand() % (high - low) + low;
        // Convert a std::string to oatpp::String
        const string response = to_string(random);
        span->End();
        return ResponseFactory::createResponse(Status::CODE_200, response.c_str());
    }
};

void run() {
    auto router = oatpp::web::server::HttpRouter::createShared();
    router->route("GET", "/rolldice", std::make_shared<Handler>());
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
            {"localhost", 8888, oatpp::network::Address::IP_4});
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("Dice Server", "Server running on port %s",
               static_cast<const char *>(connectionProvider->getProperty("port").getData()));
    server.run();
}

int main() {
    oatpp::base::Environment::init();
    InitTracer();
    srand((int) time(0));
    run();
    oatpp::base::Environment::destroy();
    CleanupTracer();
    return 0;
}
