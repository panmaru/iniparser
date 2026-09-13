cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(iniparser VERSION 0.1 LANGUAGES CXX)

add_subdirectory(utils)

add_executable(iniparser main.cpp)
target_link_libraries(iniparser PRIVATE iniparser_utils)