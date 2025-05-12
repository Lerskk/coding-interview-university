cmake_minimum_required(VERSION 3.10)
project(libds)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_VECTOR "Build vector" OFF)

include_directories(include)

add_library(libds STATIC
  src/vector.c
)

add_executable(main src/main.c)
target_link_libraries(main PRIVATE libds)

if(BUILD_VECTOR)
  add_executable(vector_test example/generic_vector.c)
  target_link_libraries(vector_test PRIVATE libds)
endif()
