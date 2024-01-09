cmake_minimum_required(VERSION 3.27)
project(SmartPointers)

set(CMAKE_CXX_STANDARD 17)

add_executable(SmartPointers main.cpp
        SmartPointer.cpp
        SmartPointer.h
        CRefCounter.cpp
        CRefCounter.h
        SmartMPointer.cpp
        SmartMPointer.h)
