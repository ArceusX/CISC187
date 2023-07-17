cmake_minimum_required(VERSION 3.12)

project(lab4 VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
include (prevent_source_builds)
include (clang_tidy)

# add_library(${PROJECT_NAME} 
#   ${PROJECT_NAME}.h ${PROJECT_NAME}.cpp)

add_library(${PROJECT_NAME} 
  ${PROJECT_NAME}.h v2.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# function(check_source name)
#   foreach(fname in items ${ARGN})
#     if (exists "${CURRENT_SOURCE_DIR}/${fname}")
#       message(STATUS "Pass. ${fname} exists.")
#       return ()
#     else()
#       message(WARNING "Fail. ${fname} not found.")
#       return ()
#     endif()
#   endforeach()
# endfunction()


# add_test(NAME step1 COMMAND check_source lab4.h lab4.cpp)
