//
// Created by Mateusz on 04/12/2023.
//

#pragma once

#include "../Graph/Graph.h"
#include "../PrimAlgorithm/PrimAlgorithm.h"
#include <vector>


class TabuSearch {
private:
    int **matrix = nullptr;     // Pointer to a 2D array representing the graph's adjacency matrix
    int matrix_size = 0;        // Size of the matrix (number of vertices)
    int search_time_limit = 0;  // Time limit for the search algorithm
    vector<int> path_to_save;
    vector<int> permutation;

    // Private helper functions

    // Calculates the cost of a given path (permutation) in the graph
    int calculatePath(vector<int> path);

public:
    // Public member functions

    // Initiates the Tabu Search algorithm to find the shortest path in the graph
    void startAlgorithm(int neighbour_switch);

    void setPath(vector<int> path);

    vector<int> getPath();

    vector<int> neighbourhood_solution_swap(vector<int> permutation_to_solve, int first_argument, int second_argument);

    vector<int> neighbourhood_solution_insert(vector<int> permutation_to_solve, int first_argument, int second_argument);

    vector<int> neighbourhood_solution_invert(vector<int> permutation_to_solve, int first_argument, int second_argument);


    // Constructor for TabuSearch class, takes a graph and a search time limit as input
    TabuSearch(Graph graph, int time, vector<int> path_mst);

    // Destructor for TabuSearch class
    ~TabuSearch();
};
