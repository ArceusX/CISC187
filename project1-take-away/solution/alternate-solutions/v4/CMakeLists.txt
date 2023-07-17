cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(v4 VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
  game.h game.cpp
  help.h
  take-away.cpp
  tests.cpp
  turn.h turn.cpp
  utility.h utility.cpp
)

target_link_libraries(${PROJECT_NAME} doctest)

