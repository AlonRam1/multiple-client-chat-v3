cmake_minimum_required(VERSION 3.20)
project(client-session)

add_library(client_session_lib ${CMAKE_SOURCE_DIR}/client-session/src/client-session.cc)
target_link_libraries(client_session_lib PUBLIC proto_gen)
target_include_directories(client_session_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

