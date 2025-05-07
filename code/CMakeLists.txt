cmake_minimum_required(VERSION 3.10)
project(libds)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(libds 
  src/main.c
)
target_link_libraries(libds m)
