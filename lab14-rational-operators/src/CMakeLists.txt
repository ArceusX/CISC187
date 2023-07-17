cmake_minimum_required(VERSION 3.12)

project(lab14 VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} ${PROJECT_NAME}.h)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)