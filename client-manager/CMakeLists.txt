cmake_minimum_required(VERSION 3.20)
project(client-manager)

add_library(client_manager_lib ${CMAKE_SOURCE_DIR}/client-manager/src/client-manager.cc)
target_include_directories(client_manager_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(client_manager_lib PUBLIC client_session_lib proto_gen)
