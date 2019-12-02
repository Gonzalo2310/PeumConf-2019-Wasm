cmake_minimum_required(VERSION 3.14)
project(parametro)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/infogon/Aplicaciones/emsdk/fastcomp/emscripten/system/include/)

add_executable(parametro main.cpp)