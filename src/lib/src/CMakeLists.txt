cmake_minimum_required(VERSION 3.10)

project(cEngine)

add_executable(Main main.c CrippleMD.c)

target_include_directories(Main PUBLIC ".")
