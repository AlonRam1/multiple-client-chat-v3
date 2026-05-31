cmake_minimum_required(VERSION 3.20)
project(multiple-client-chat-v3)

find_package(gRPC CONFIG REQUIRED)

set(PROTOBUF_DEFINITION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/chat.proto)

set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(PROTOBUF_GENERATE_DIR ${PROJECT_BUILD_DIR}/gen/protobuf)
set(GRPC_GENERATE_DIR ${PROJECT_BUILD_DIR}/gen/grpc)

set(PROTOBUF_GENERATED_FILES ${PROTOBUF_GENERATE_DIR}/chat.pb.cc ${PROTOBUF_GENERATE_DIR}/chat.pb.h)
set(GRPC_GENERATED_FILES ${GRPC_GENERATE_DIR}/chat.grpc.pb.cc ${GRPC_GENERATE_DIR}/chat.grpc.pb.h)
set(GENERATED_CC_FILES ${PROTOBUF_GENERATE_DIR}/chat.pb.cc ${GRPC_GENERATE_DIR}/chat.grpc.pb.cc)
set(GENERATED_HEADER_FILES ${PROTOBUF_GENERATE_DIR}/chat.pb.h ${GRPC_GENERATE_DIR}/chat.grpc.pb.h)


add_custom_command(
OUTPUT ${PROTOBUF_GENERATED_FILES} ${GRPC_GENERATED_FILES}
COMMAND protoc -I=${CMAKE_CURRENT_SOURCE_DIR}/proto --cpp_out=${PROTOBUF_GENERATE_DIR} --grpc_out=${GRPC_GENERATE_DIR} --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin> ${PROTOBUF_DEFINITION_FILE}
DEPENDS ${PROTOBUF_DEFINITION_FILE}
VERBATIM
)
add_library(proto_gen ${GENERATED_CC_FILES})

target_include_directories(proto_gen PUBLIC ${GRPC_GENERATE_DIR} ${PROTOBUF_GENERATE_DIR})

add_subdirectory(server)
add_subdirectory(client)




