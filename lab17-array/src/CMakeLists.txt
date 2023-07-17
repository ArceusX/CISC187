cmake_minimum_required(VERSION 3.12)

project(array VERSION 1.0.0 LANGUAGES CXX)
add_library(${PROJECT_NAME} ${PROJECT_NAME}.h main.cpp)
add_executable(main main.cpp)

target_link_libraries(main ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

