cmake_minimum_required(VERSION 3.12) 
project(dna VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
  main.cpp
)

file (COPY 
      FILES_MATCHING PATTERN commands*.txt
      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

