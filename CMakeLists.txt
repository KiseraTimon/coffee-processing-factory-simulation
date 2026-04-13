cmake_minimum_required(VERSION 4.0)
project(Coffee_Processing_Factory_Simulation)

set(CMAKE_CXX_STANDARD 26)

add_executable(Coffee_Processing_Factory_Simulation main.cpp
        include/Core/Entity.h
        include/Core/Worker.h
        src/Core/Worker.cpp
        include/Core/CoreTypes.h)
