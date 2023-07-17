cmake_minimum_required(VERSION 3.12)

project(zoo_lab VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} 
  Animal.h
  Canine.h
  Cat.cpp Cat.h
  Dog.cpp Dog.h
  Fish.cpp Fish.h
  Owl.cpp Owl.h
  Pet.h
  RoboDog.cpp RoboDog.h
  Robot.h
  Wolf.cpp Wolf.h
  zoo.cpp zoo.h
)
add_executable(zoo main.cpp)

target_link_libraries(zoo ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

