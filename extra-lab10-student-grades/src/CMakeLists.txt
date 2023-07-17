cmake_minimum_required(VERSION 3.12)

project(lab10 VERSION 1.0.0 LANGUAGES CXX)

file(COPY class.txt 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(${PROJECT_NAME} 
  average.h average.cpp
  student.h student.cpp
)
add_executable(grades main.cpp)

target_link_libraries(grades ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

