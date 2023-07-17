cmake_minimum_required(VERSION 3.12) 
project(take-away VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
include (prevent_source_builds)
include (clang_tidy)

add_library(${CMAKE_PROJECT_NAME} 
  computer_player.h computer_player.cpp
  game.h game.cpp
  options.h options.cpp
)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


add_subdirectory(alternate-solutions/v2)
add_subdirectory(alternate-solutions/v3)
add_subdirectory(alternate-solutions/v4)

