cmake_minimum_required(VERSION 3.26)
project(PEA_Project_Episode_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source)

add_executable(PEA_Project_Episode_1
        Source/main.cpp
        Graph/Graph.cpp
        Graph/Graph.h
        Stack/Stack.cpp
        Stack/Stack.h
        Time/Time.cpp
        Time/Time.h
        BruteForce/BruteForce.cpp
        BruteForce/BruteForce.h
        BranchAndBound/BranchAndBound.cpp
        BranchAndBound/BranchAndBound.h
        DynamicProgramming/DynamicProgramming.cpp
        DynamicProgramming/DynamicProgramming.h
        Tests/Tests.cpp
)
