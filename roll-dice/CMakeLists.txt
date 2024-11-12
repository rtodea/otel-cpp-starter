cmake_minimum_required(VERSION 3.25)
project(RollDiceServer)

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(project_name roll-dice-server)

# Define your project's source files
set(SOURCES
    main.cpp
        tracing/GrafanaTracer.cpp
        tracing/GrafanaTracer.h
        tracing/DummyTracer.cpp
        tracing/DummyTracer.h
        tracing/TracerProvider.cpp
        tracing/TracerProvider.h
        tracing/AppTracer.h  # Add your source files here
)
find_package(Threads REQUIRED)

# Create an executable target
add_executable(dice-server ${SOURCES})

set(OATPP_ROOT ./libraries/oatpp)
set(opentelemetry-cpp_DIR ./libraries/otel-cpp/lib/cmake/opentelemetry-cpp)

find_library(OATPP_LIB NAMES liboatpp.a HINTS "${OATPP_ROOT}/build/src/" NO_DEFAULT_PATH)
if (NOT OATPP_LIB)
  message(SEND_ERROR "Did not find oatpp library ${OATPP_ROOT}/build/src")
endif()

# set the path to the directory containing "oatpp" package configuration files
include_directories(${OATPP_ROOT}/src)

find_package(opentelemetry-cpp CONFIG REQUIRED NO_DEFAULT_PATH)

message(STATUS "OpenTelemetry C++ Libraries: ${OPENTELEMETRY_CPP_LIBRARIES}")
target_link_libraries(dice-server PRIVATE
        ${OATPP_LIB}
        Threads::Threads
        ${OPENTELEMETRY_CPP_LIBRARIES})
