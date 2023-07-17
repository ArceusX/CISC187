cmake_minimum_required(VERSION 3.12)

project(lab3 VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
include (prevent_source_builds)
include (clang_tidy)

add_library(${PROJECT_NAME} 
	${PROJECT_NAME}.h ${PROJECT_NAME}.cpp)

add_executable(example main.cpp ${PROJECT_NAME}.cpp ${PROJECT_NAME}.h)
add_executable(example2 main.cpp v2.cpp ${PROJECT_NAME}.h)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
