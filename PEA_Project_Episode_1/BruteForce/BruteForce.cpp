//
// Created by Mateusz on 24/10/2023.
//

#include <iostream>
#include "BruteForce.h"

using namespace std;

// This function initiates the recursive algorithm to find the optimal solution for the Traveling Salesman Problem (TSP)
void BruteForce::startRecursiveAlgorithm() {
    int bit_mask = 1;        // Initialize bitmask to track visited nodes
    int starting_node = 0;   // Starting node for the TSP problem
    int index = 0;           // Initialize index for path traversal
    path_weight = algorithm(bit_mask, starting_node); // Calculate optimal path weight using recursive algorithm

    // Reconstruct the optimal path using previously stored information
    for (int i = 0;; ++i) {
        path[i] = index; // Store the current index in the path array
        auto next_index = preview[bit_mask][index]; // Get the next index from the stored information

        // If next index is -1, indicating the end of the path, break the loop
        if (next_index == -1) {
            break;
        }

        // Update bitmask and index for next iteration
        auto next_bit_mask = bit_mask | (1 << next_index); // Update bitmask
        bit_mask = next_bit_mask;
        index = next_index;
    }

    // Add the starting node again to complete the cycle
    path[number_of_nodes] = 0;
}

// Recursive function to calculate the optimal TSP path
int BruteForce::algorithm(int mask, int position) {
    // If mask indicates all nodes have been visited, return path weight of returning to the starting node
    if (mask == VISITED_ALL) {
        return matrix[position][0];
    }

    int cost = INF; // Initialize cost to a large value
    int index;      // Variable to store the index of the next node in the optimal path

    // Iterate through all nodes to find unvisited nodes
    for (int node = 0; node < number_of_nodes; ++node) {
        // Check if the node has not been visited (using bitwise operations)
        if ((mask & (1 << node)) == 0) {
            // Calculate the cost of the new path and perform recursive call
            int new_cost = matrix[position][node] + algorithm(mask | (1 << node), node);

            // Update the cost and index if the new cost is smaller
            if (new_cost < cost) {
                cost = new_cost;
                index = node;
            }
        }
    }

    // Store the index of the next node for the current bitmask and position
    preview[mask][position] = index;
    return cost; // Return the optimal cost for the current state
}

// Display the resulting optimal path and its weight
void BruteForce::showResult() {
    cout << "Path: ";
    // Display the nodes in the optimal path
    for (int i = 0; i < number_of_nodes + 1; ++i) {
        cout << path[i] << " ";
    }
    cout << "\nWeight: " << path_weight << endl; // Display the weight of the optimal path
}

// Constructor for initializing the BruteForce object with graph data
BruteForce::BruteForce(Graph graph) {
    matrix = graph.getMatrix(); // Get the adjacency matrix from the graph object
    number_of_nodes = graph.getMatrixSize(); // Get the number of nodes in the graph

    // Initialize path array to store the optimal path
    path = new int[number_of_nodes + 1];

    // Allocate memory for memoization of distinct states
    memory = new int *[1 << number_of_nodes];
    for (int bit_mask = 0; bit_mask < (1 << number_of_nodes); ++bit_mask) {
        memory[bit_mask] = new int[number_of_nodes];
        // Initialize the memory values to -1
        for (int pos = 0; pos < number_of_nodes; ++pos) {
            memory[bit_mask][pos] = -1;
        }
    }

    // Initialize 'preview' array to store preview node information for each node
    preview = new int *[1 << number_of_nodes];
    for (int bit_mask = 0; bit_mask < (1 << number_of_nodes); ++bit_mask) {
        preview[bit_mask] = new int[number_of_nodes];
        // Initialize the 'preview' values to -1
        for (int pos = 0; pos < number_of_nodes; ++pos) {
            preview[bit_mask][pos] = -1;
        }
    }

    VISITED_ALL = (1 << number_of_nodes) - 1; // Calculate the bitmask for all nodes visited
}

// Destructor to deallocate memory used by the BruteForce object
BruteForce::~BruteForce() {
    for (int i = 0; i < (1 << number_of_nodes); ++i) {
        delete memory[i];
    }
    delete memory;
}
