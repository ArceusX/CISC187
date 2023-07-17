cmake_minimum_required(VERSION 3.12) 
project(20q VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
  main.cpp
  helper.h helper.cpp
  node.h node.cpp
  game.h game.cpp
)

file (COPY data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

