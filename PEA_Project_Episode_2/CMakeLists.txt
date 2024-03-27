cmake_minimum_required(VERSION 3.26)
project(PEA_Project_Episode_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA_Project_Episode_2 Source/main.cpp
        Graph/Graph.cpp
        Graph/Graph.h
        TabuSearch/TabuSearch.cpp
        TabuSearch/TabuSearch.h
        PrimAlgorithm/PrimAlgorithm.cpp
        SimulatedAnnealing/SimulatedAnnealing.h
        SimulatedAnnealing/SimulatedAnnealing.cpp
        SimulatedAnnealing/SimulatedAnnealing.cpp
        SimulatedAnnealing/SimulatedAnnealing.h
        lib/tinyxml2-9.0.0/tinyxml2.cpp
        lib/tinyxml2-9.0.0/tinyxml2.h)
