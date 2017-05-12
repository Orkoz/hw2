cmake_minimum_required(VERSION 3.7)
project(hw2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        airport.c
        airport.h
        ex2.h
        flight.c
        flight.h
        runway.c
        runway.h)

add_executable(hw2 ${SOURCE_FILES})