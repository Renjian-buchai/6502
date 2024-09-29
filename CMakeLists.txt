cmake_minimum_required(VERSION 3.29.6)

if (!MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfloat-equal -Werror -Wformat=2 -Wno-missing-declarations -Wmissing-include-dirs -Wcast-qual -Wpointer-arith -Wsequence-point -Wshadow -Wsign-conversion -Wextra -Wcast-align -Wswitch -Wundef -Wunreachable-code -Wno-format-extra-args -Wno-unused-function -Wno-unused-parameter -Wwrite-strings -Wstrict-aliasing -Wpedantic")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(shit502)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/shit502.cc)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")
