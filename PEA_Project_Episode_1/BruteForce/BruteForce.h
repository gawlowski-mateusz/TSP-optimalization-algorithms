//
// Created by Mateusz on 24/10/2023.
//

#ifndef PEA_PROJECT_EPISODE_1_BRUTEFORCE_H
#define PEA_PROJECT_EPISODE_1_BRUTEFORCE_H

#include "../Graph/Graph.h"
#include "../Stack/Stack.h"

#define INF 9999

// This class represents a brute-force algorithm for solving the Traveling Salesman Problem (TSP).

class BruteForce {
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
    void showResult();

    // Constructor for initializing the BruteForce object with graph data.
    BruteForce(Graph graph);

    // Destructor for cleanup, if needed (memory management).
    ~BruteForce();
};



#endif //PEA_PROJECT_EPISODE_1_BRUTEFORCE_H
