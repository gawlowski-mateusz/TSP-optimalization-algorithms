cmake_minimum_required(VERSION 3.26)
project(PEA_Project_Episode_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Project_Episode_3 Source/main.cpp
        Graph/Graph.cpp
        GeneticAlgorithm/GeneticAlgorithm.cpp
        lib/tinyxml2-9.0.0/tinyxml2.cpp
        lib/tinyxml2-9.0.0/tinyxml2.h)
