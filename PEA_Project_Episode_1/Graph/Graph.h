//
// Created by Mateusz on 16/10/2023.
//

#ifndef PEA_PROJECT_EPISODE_1_GRAPH_H
#define PEA_PROJECT_EPISODE_1_GRAPH_H

#pragma once

#include <string>
#define INF 9999

using namespace std;

class Graph {
private:
    int **matrix = nullptr;     // A 2D array to represent the weighted graph matrix.
    int matrix_size = 0;        // The number of nodes in the graph (matrix size).

public:
    void printMatrix();
    // Function to print the graph's adjacency matrix.

    bool setDiagonal();
    // Function to set the diagonal elements of the matrix (i.e., self-edges).

    bool readGraph(string file);
    // Function to read a graph from a file and populate the matrix.

    int getMatrixSize();
    // Function to get the number of nodes in the graph.

    int **getMatrix();
    // Function to get a pointer to the graph's adjacency matrix.

    bool generateRandom(int size);
    // Function to generate a random graph with the given number of nodes.

    Graph();
    // Constructor for initializing a Graph object.

    ~Graph();
    // Destructor for cleaning up allocated memory, if needed.
};


#endif //PEA_PROJECT_EPISODE_1_GRAPH_H
