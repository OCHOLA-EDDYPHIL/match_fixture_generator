cmake_minimum_required(VERSION 3.28)
project(fixture_generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fixture_generator
        main.cpp
        Teams.csv)
