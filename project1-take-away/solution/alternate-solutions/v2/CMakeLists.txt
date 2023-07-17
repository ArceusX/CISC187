cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(v2 VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
  main.cpp
  computer_player.hpp computer_player.cpp
  game.hpp game.cpp
)


