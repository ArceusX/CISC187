cmake_minimum_required(VERSION 3.12) 
project(take-away VERSION 1.0.0 LANGUAGES CXX)

# If not using tests list all source files here
add_executable(${PROJECT_NAME} main.cpp helper.h helper.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)