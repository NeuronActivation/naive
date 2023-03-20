cmake_minimum_required(VERSION 3.0)
project(naive)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(termos)
file(GLOB Sources naive/*.cc)

add_executable(naive ${Sources})
target_link_libraries(naive termos)
