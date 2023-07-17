cmake_minimum_required(VERSION 3.12)

project(lab2 VERSION 1.0.0 LANGUAGES CXX)

add_library(${CMAKE_PROJECT_NAME} 
	change.h change.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
