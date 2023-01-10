cmake_minimum_required(VERSION 3.10)

project(cEngine)

set(CMAKE_BUILD_TYPE Debug)

add_executable(main.out main.c CrippleMD.c)

target_include_directories(main.out PUBLIC ".")
