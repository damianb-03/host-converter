project(hosts-convert)

set(CMAKE_CXX_FLAGS "-std=c++11 -g3 -O0 -Wall -pedantic")

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} boost_system)
