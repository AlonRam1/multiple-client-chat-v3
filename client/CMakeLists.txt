cmake_minimum_required(VERSION 3.20)
project(client)

find_package(gRPC CONFIG REQUIRED)

set(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_DIR}/bin/client)

add_executable(client src/client.cc)
target_link_libraries(client PRIVATE proto_gen gRPC::grpc++)
