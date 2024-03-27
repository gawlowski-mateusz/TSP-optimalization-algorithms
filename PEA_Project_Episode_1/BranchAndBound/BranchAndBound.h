//
// Created by Mateusz on 25/10/2023.
//

#ifndef PEA_PROJECT_EPISODE_1_BRANCH_BOUND_H
#define PEA_PROJECT_EPISODE_1_BRANCH_BOUND_H

#include "../Graph/Graph.h"
#include "../Stack/Stack.h"

#define INF 9999

// Define a structure to represent a node in the Branch and Bound algorithm.
struct Node {
    int l_bound;       // The lower bound for this node.
    int vertex;        // The current vertex associated with this node.
};

// Define a class for the Branch and Bound algorithm.
class BranchAndBound {
private:
    int **matrix;         // A matrix to store the distance between nodes.
    int nodes_number;     // The number of nodes in the problem.
    int u_bound;          // The upper bound for the current problem instance.
    int temporary_cost;   // Temporary path_weight value used during the algorithm.
    bool *was_visited;    // An array to track visited nodes.
    int *outgoing_edges;  // An array to track outgoing edges for a node.
    int node0_lb;            // Lower bound for the initial (root) node.
    Stack path;           // A stack to store the current path.
    Stack helper_path;    // A stack to assist in path operations.

public:
    // Function to compute the lower bound for a given node and the next node to be added to the path.
    int lower_bound(Node argument, int next);

    // Function to start the recursive Branch and Bound algorithm.
    void startRecursiveAlgorithm();

    // Recursive function used in the Branch and Bound algorithm.
    void recursion(Node node);

    // Function to display the results of the Branch and Bound algorithm.
    void showResults();

    // Constructor for the Branch and Bound class, taking a graph as input.
    BranchAndBound(Graph graph);

    // Destructor for the Branch and Bound class.
    ~BranchAndBound();
};


#endif //PEA_PROJECT_EPISODE_1_BRANCH_BOUND_H
