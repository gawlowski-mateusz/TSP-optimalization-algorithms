//
// Created by Mateusz on 25/10/2023.
//

#include "BranchAndBound.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define custom operators for comparing two Node objects based on their l_bound values.
bool operator>(const Node &argument_1, const Node &argument_2) {
    if (argument_1.l_bound > argument_2.l_bound)
        return true;
    else
        return false;
}

bool operator<(const Node &argument_1, const Node &argument_2) {
    if (argument_1.l_bound < argument_2.l_bound)
        return true;
    else
        return false;
}

bool operator==(const Node &argument_1, const Node &argument_2) {
    if (argument_1.l_bound == argument_2.l_bound)
        return true;
    else
        return false;
}

// Function to compute the lower bound for a given node and the next node to be added to the path.
int BranchAndBound::lower_bound(Node argument, int next) {
    int result = argument.l_bound;
    result -= outgoing_edges[argument.vertex];   // Subtract the outgoing edge path_weight of the current node.
    result += matrix[argument.vertex][next];     // Add the path_weight of moving to the next node.

    return result;
}

// Function to start the recursive Branch and Bound algorithm.
void BranchAndBound::startRecursiveAlgorithm() {
    Node start;
    start.vertex = 0;           // Starting node is the first node (usually node 0).
    start.l_bound = node0_lb;   // Initialize the lower bound with the initial lower bound.

    recursion(start);
}

// Recursive function used in the Branch and Bound algorithm.
void BranchAndBound::recursion(Node node) {
    helper_path.push(node.vertex);      // Add the current node to the helper path.
    was_visited[node.vertex] = true;    // Mark the current node as visited.
    Node temporary;
    priority_queue<Node, std::vector<Node>, std::greater<Node>> bounds; // Priority queue to store nodes with lower bounds.

    for (int i = 0; i < nodes_number; i++) {
        if (!was_visited[i]) {
            temporary.vertex = i;
            temporary.l_bound = lower_bound(node, i); // Calculate the lower bound for unvisited nodes.
            bounds.push(temporary);
        }
    }

    if (bounds.empty()) {
        if (lower_bound(node, 0) < u_bound) {
            u_bound = lower_bound(node, 0);   // Update the upper bound and the final path if a better path is found.
            helper_path.copy(&path);
        }
    } else {
        while (!bounds.empty()) {
            temporary = bounds.top();
            bounds.pop();

            if (temporary.l_bound < u_bound) {
                recursion(temporary);  // Recursively explore nodes with promising lower bounds.
            } else
                break;
        }
    }
    helper_path.pop();                 // Remove the current node from the helper path.
    was_visited[node.vertex] = false;  // Mark the current node as unvisited.
}

// Function to display the results of the Branch and Bound algorithm.
void BranchAndBound::showResults() {
    // Display the final path with "0" at the end to indicate the return to the starting node.
    cout << "Path: " << path.showResults() + "0" << endl;

    // Display the total weight (upper bound) of the path.
    cout << "Weight: " << u_bound << endl;
}

// Constructor for the Branch and Bound class, taking a graph as input.
BranchAndBound::BranchAndBound(Graph graph) {
    nodes_number = graph.getMatrixSize();   // Get the number of nodes from the input graph.
    matrix = graph.getMatrix();             // Get the distance matrix from the input graph.
    u_bound = INF;                          // Initialize the upper bound as infinity (unbounded).
    temporary_cost = 0;                     // Initialize temporary path_weight value.
    outgoing_edges = new int[nodes_number]; // Create an array to store outgoing edge costs.
    was_visited = new bool[nodes_number];   // Create an array to track visited nodes.
    node0_lb = 0;                           // Initialize the lower bound for the initial (root) node.
    int minimum = INF;

    // Calculate outgoing edge costs and initial lower bound.
    for (int row = 0; row < nodes_number; row++) {
        for (int column = 0; column < nodes_number; column++) {
            if (matrix[row][column] < minimum)
                minimum = matrix[row][column];
        }
        outgoing_edges[row] = minimum;
        node0_lb += minimum;
        minimum = INF;
    }

    // Initialize the visited array to mark all nodes as unvisited.
    for (int i = 0; i < nodes_number; i++) {
        was_visited[i] = false;
    }
}

// Destructor for the Branch and Bound class.
BranchAndBound::~BranchAndBound() {
    // Destructor is empty in this example.
}

