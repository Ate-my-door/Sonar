cmake_minimum_required(VERSION 3.10)

project(SONAR CXX)

add_executable(sonar sonar.cpp)

add_compile_options(sonar PUBLIC cxx_std_11 Wall)