cmake_minimum_required(VERSION 3.29.6)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4 /WX")
  # Default debug flags are OK 
  set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfloat-equal -Werror -Wformat=2 -Wno-missing-declarations -Wmissing-include-dirs -Wcast-qual -Wpointer-arith -Wsequence-point -Wshadow -Wsign-conversion -Wextra -Wcast-align -Wswitch -Wundef -Wunreachable-code -Wno-format-extra-args -Wno-unused-function -Wno-unused-parameter -Wwrite-strings -Wstrict-aliasing -Wpedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  else()
    # nothing special for gcc at the moment
  endif()
endif()

set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(shit502)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")
