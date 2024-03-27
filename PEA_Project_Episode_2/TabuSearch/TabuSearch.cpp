//
// Created by Mateusz on 04/12/2023.
//

#include "TabuSearch.h"
#include <time.h>
#include <iostream>
#include "../Graph/Graph.h"
#include <algorithm>
#include <ctime>
#include <utility>

using namespace std;

// This function initiates the Tabu Search algorithm to find the shortest path in a graph.
void TabuSearch::startAlgorithm(int neighbour_switch) {
    // Initializing necessary variables and data structures
    vector<int> mst_permutation = permutation;                  // Save the initial MST permutation
    vector<int> temporary_permutation = permutation;            // Temporary permutation
    vector<vector<int>> matrix_tabu_search;                     // Tabu search matrix for tracking forbidden moves
    vector<int> best_path;                                      // Store the best_path path found so far
    vector<int> next(permutation);                              // Store the next candidate permutation

    int result = 1 << 30; // Initializing the result to a large value
    int first_to_swap;
    int second_to_swap;
    int next_cost;

    clock_t start; // For measuring time
    double time;
    double searching_time;

    matrix_tabu_search.resize(matrix_size); // Resizing the tabu search matrix

    for (int j = 0; j < matrix_size; ++j) {
        matrix_tabu_search[j].resize(matrix_size, 0); // Initializing tabu search matrix elements to 0
    }

    start = clock(); // Start the timer

    // Continue the algorithm until a stopping condition is met
    while (true) {
        for (int step = 0; step < 15 * matrix_size; ++step) {
            first_to_swap = 0;
            second_to_swap = 0;
            next_cost = 1 << 30;

            // Iterate through all possible swaps of elements in the permutation
            for (int first = 1; first < matrix_size; ++first) {
                for (int second = first + 1; second < matrix_size; ++second) {

                    if (neighbour_switch == 1) {
                        temporary_permutation = neighbourhood_solution_insert(permutation, first, second);
                    } else if (neighbour_switch == 2) {
                        temporary_permutation = neighbourhood_solution_invert(permutation, first, second);
                    } else {
                        temporary_permutation = neighbourhood_solution_swap(permutation, first, second);
                    }

                    // Calculate the cost of the current permutation
                    int current_cost = calculatePath(temporary_permutation);

                    // Update the best_path solution found if the current one is better
                    if (current_cost < result) {
                        result = current_cost;
                        best_path = temporary_permutation; // Update the best_path path
                        searching_time = (clock() - start) / (double)CLOCKS_PER_SEC; // Update time taken to find this solution
                    }

                    // Update the next candidate solution if it satisfies certain conditions
                    if (current_cost < next_cost) {
                        if (matrix_tabu_search[second][first] < step) {
                            next_cost = current_cost;
                            next = temporary_permutation; // Update the next candidate permutation

                            first_to_swap = second;
                            second_to_swap = first;
                        }
                    }

                    time = (clock() - start) / (double)CLOCKS_PER_SEC; // Calculate the current elapsed time

                    // Check if the allotted search time has been exceeded
                    if (time >= search_time_limit) {
                        // Print the best_path path found so far and related information
                        cout << "\n==== TABU SEARCH RESULT ====" << endl;
                        cout << "Path: ";

                        for (int d = 0; d < matrix_size + 1; d++) {
                            cout << best_path[d] << " ";
                        }

                        // Save the best_path Path found
                        setPath(best_path);

                        cout << "\nWeight: " << result << endl;
                        cout << "Searching time: " << searching_time << " s " << endl;
                        return; // End the search
                    }
                }
            }
            permutation = next; // Update the current permutation
            matrix_tabu_search[first_to_swap][second_to_swap] += step + rand() % matrix_size; // Increment the corresponding tabu search matrix value
        }

        // Clear the permutation and reinitialize tabu search matrix for the next iteration
        permutation.clear();

//        permutation = permutation_random(matrix_size); // Generate a new random permutation
        permutation = mst_permutation;   // Generate a new random permutation

        for (vector<vector<int>>::iterator it = matrix_tabu_search.begin(); it != matrix_tabu_search.end(); ++it) {
            it->clear(); // Clear inner vectors of tabu search matrix
        }
        matrix_tabu_search.clear(); // Clear the entire tabu search matrix

        matrix_tabu_search.resize(matrix_size); // Resize and reinitialize tabu search matrix

        for (vector<vector<int>>::iterator it = matrix_tabu_search.begin(); it != matrix_tabu_search.end(); ++it) {
            it->resize(matrix_size, 0); // Reset tabu search matrix elements to 0
        }
    }
}

vector<int> TabuSearch::neighbourhood_solution_swap(vector<int> permutation_to_solve, int first_argument, int second_argument) {
    swap(permutation_to_solve[first_argument], permutation_to_solve[second_argument]); // Swap elements
    return permutation_to_solve;
}

vector<int> TabuSearch::neighbourhood_solution_insert(vector<int> permutation_to_solve, int first_argument, int second_argument) {
    if (first_argument == second_argument) {
        return permutation_to_solve;
    }

    int element_to_move = permutation_to_solve[first_argument];
    if (first_argument < second_argument) {
        for (int i = first_argument; i < second_argument; ++i) {
            permutation_to_solve[i] = permutation_to_solve[i + 1];
        }
        permutation_to_solve[second_argument] = element_to_move;
    } else {
        for (int i = first_argument; i > second_argument + 1; --i) {
            permutation_to_solve[i] = permutation_to_solve[i - 1];
        }
        permutation_to_solve[second_argument + 1] = element_to_move;
    }

    return permutation_to_solve;
}

vector<int> TabuSearch::neighbourhood_solution_invert(vector<int> permutation_to_solve, int first_argument, int second_argument) {
    if (first_argument == second_argument) {
        return permutation_to_solve;
    }

    if (first_argument < second_argument) {
        while (first_argument < second_argument) {
            swap(permutation_to_solve[first_argument], permutation_to_solve[second_argument]); // Swap elements
            first_argument++;
            second_argument--;
        }
    } else {
        while (first_argument > second_argument) {
            swap(permutation_to_solve[second_argument], permutation_to_solve[first_argument]); // Swap elements
            first_argument--;
            second_argument++;
        }
    }
    return permutation_to_solve;
}

// Function to calculate the cost of a given path (permutation)
int TabuSearch::calculatePath(vector<int> path) {
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += matrix[path[i]][path[i + 1]]; // Accumulate the cost based on the matrix values
    }

    return cost; // Return the calculated cost of the path
}

void TabuSearch::setPath(vector<int> path) {
    path_to_save = path;
}

vector<int> TabuSearch::getPath() {
    return path_to_save;
}

// Constructor for TabuSearch class, takes a graph and a search time limit as input
TabuSearch::TabuSearch(Graph graph, int time, vector<int> path_mst) {
    matrix = graph.getMatrix();                // Get the adjacency matrix of the graph
    matrix_size = graph.getMatrixSize();       // Get the matrix_size of the matrix
    search_time_limit = time;                  // Set the search time limit
    permutation = std::move(path_mst);         // Set the initial permutation - greedy algorithm
}

// Destructor for TabuSearch class
TabuSearch::~TabuSearch() {
    // No explicit clean-up required as there are no dynamic allocations
}

