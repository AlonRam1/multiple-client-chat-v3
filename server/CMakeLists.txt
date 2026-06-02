cmake_minimum_required(VERSION 3.20)
project(server)

find_package(gRPC CONFIG REQUIRED)

set(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_DIR}/bin/server)

add_executable(server src/server.cc)
target_include_directories(server PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(server PRIVATE client_manager_lib proto_gen gRPC::grpc++)
