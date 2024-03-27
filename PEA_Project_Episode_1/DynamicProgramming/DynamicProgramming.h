//
// Created by Mateusz on 03/11/2023.
//

#ifndef PEA_PROJECT_EPISODE_1_DYNAMICPROGRAMMING_H
#define PEA_PROJECT_EPISODE_1_DYNAMICPROGRAMMING_H

#pragma once

#include "../Graph/Graph.h"
#include "../Stack/Stack.h"

#define INF 9999

// Define a class for the Dynamic Programming algorithm.
class DynamicProgramming {
private:
    int **matrix;        // 2D array to store the graph's adjacency matrix
    int number_of_nodes; // Number of nodes in the graph
    int **memory;        // Memoization table to store computed sub-problem results
    int path_weight;     // The weight of the current best path
    int VISITED_ALL;     // Mask to track visited nodes
    int *path;           // Array to store the current path
    int **preview;      // 2D array to store preview node information for each node

    // Recursive function to calculate the optimal TSP path
    int algorithm(int mask, int position);

public:
    // Initiates the recursive algorithm to solve the TSP problem.
    void startRecursiveAlgorithm();

    // Displays the result, i.e., the best path found and its weight.
    void showResults();

    // Constructor for initializing the DynamicProgramming object with graph data.
    DynamicProgramming(Graph graph);

    // Destructor for cleanup, if needed (memory management).
    ~DynamicProgramming();
};


#endif //PEA_PROJECT_EPISODE_1_DYNAMICPROGRAMMING_H
