//
// Created by Mateusz on 12/12/2023.
//

#include "SimulatedAnnealing.h"
#include "../Graph/Graph.h"
#include "../PrimAlgorithm/PrimAlgorithm.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <cstdlib>      // std::rand, std::srand
#include <random>
#include <fstream>
#include "../lib/effolkronium/random.hpp"

using Random = effolkronium::random_static;
using namespace std;

// Define the Simulated Annealing class and its methods
int SimulatedAnnealing::startAlgorithm() {
    // Initialize variables
    int first_to_swap;
    int second_to_swap;
    int difference;
    int current_cost = calculatePathWeight(permutation);
    double time = 0;

    temperature = initial_temperature;
    result = INF;

    clock_t start;
    start = clock();

    // Main loop for simulated annealing
    while (time < search_time_limit && temperature >= pow(10, -15)) {
        // Number of steps for each temperature
        int steps = 600 * matrix_size;

        // Iterate over the specified number of steps
        for (int i = steps; i > 0; i--) {
            if (time >= search_time_limit)
                break;

            vector<int> next = permutation;

            // Generate two random indices to swap
            do {
                first_to_swap = Random::get(1, matrix_size - 1);
                second_to_swap = Random::get(1, matrix_size - 1);
            } while (first_to_swap == second_to_swap);

            // Swap elements at the generated indices
            swap(next[first_to_swap], next[second_to_swap]);

            // Calculate the cost of the new solution
            int next_cost = calculatePathWeight(next);

            // Calculate the difference between the current and new solutions
            difference = current_cost - next_cost;

            // Update the best_path solution if the new solution is better
            if (difference > 0) {
                result = next_cost;
                current_cost = next_cost;
                best_path = next;
                permutation = next;
                searching_time = (clock() - start) / (double) CLOCKS_PER_SEC;
            } else {
                if (getProbability(difference, temperature) > Random::get<double>(0, 1)) {
                    permutation = next;
                    current_cost = next_cost;
                }
            }
            // Check if the specified time bound is reached
            time = (clock() - start) / (double) CLOCKS_PER_SEC;
        }
        // Decrease the temperature according to the cooling rate
        temperature *= cooling_rate;
    }

    // Output the best_path solution and information
    cout << "\n==== SIMULATED ANNEALING RESULT ====" << endl;
    cout << "Path: ";

    for (int node: best_path) {
        cout << node << " ";
    }

    cout << "\nWeight: " << result << endl;
    cout << "Searching time: " << searching_time << " s " << endl;
    cout << "Final temperature: " << temperature << endl;
    cout << "dT value: " << getProbability(difference, temperature) << endl;

    return result;
}

// Generate a random permutation of integers from 0 to _size
vector<int> SimulatedAnnealing::randomPermutation(int _size) {
    vector<int> temporary_permutation;
    temporary_permutation.reserve(_size);

    // Fill the vector with consecutive integers
    for (int i = 0; i < _size; i++) {
        temporary_permutation.push_back(i);
    }

    // Shuffle the vector to create a random permutation
    shuffle(temporary_permutation.begin(), temporary_permutation.end(), default_random_engine());

    return temporary_permutation;
}

// Calculate the initial temperature using a set of random swaps
double SimulatedAnnealing::calculateTemperature() {
    vector<int> origin;

    int first_to_swap;
    int second_to_swap;
    int delta = 0;
    int buffer = 0;

    // Perform a set number of random swaps to estimate the temperature
    for (int i = 0; i < 10000; i++) {
        do {
            first_to_swap = Random::get(1, matrix_size - 1);
            second_to_swap = Random::get(1, matrix_size - 1);
        } while (first_to_swap == second_to_swap);

        // Generate a random permutation and its neighbor
        origin = randomPermutation(matrix_size);
        vector<int> neighbour(origin);

        swap(neighbour[first_to_swap], neighbour[second_to_swap]);

        // Calculate the cost difference between the original and the neighbor
        delta = fabs(calculatePathWeight(origin) - calculatePathWeight(neighbour));
        buffer += delta;
    }

    // Calculate the average cost difference and use it to estimate the initial temperature
    buffer /= 10000;

    return (-1 * buffer) / log(0.99);
}

void SimulatedAnnealing::savePath(string file_name) {
    file_name = "../bin/SA_" + file_name;

    ofstream file;
    file.open(file_name);
    file << matrix_size << endl;

    for (int node: best_path) {
        file << node << endl;
    }

    file << endl;
    file.close();
}

void SimulatedAnnealing::saveResults(string file_name) {
    file_name = "../bin/" + file_name;
    ofstream file;

    file.open(file_name, ios_base::app);
    file << matrix_size << ";" << "SA" << ";" << result << ";" << search_time_limit << ";" << searching_time << ";" << cooling_rate << ";" << temperature << endl;
//    file << endl;
    file.close();
}


// Calculate the cost of a given path
int SimulatedAnnealing::calculatePathWeight(vector<int> path) {
    int path_weight = 0;

    // Calculate the total path_weight of the path by summing the distances between consecutive nodes
    for (int i = 0; i < path.size() - 1; ++i) {
        path_weight += matrix[path[i]][path[i + 1]];
    }
    // Add the distance from the last node to the first node to complete the cycle

    return path_weight;
}

// Calculate the probability of accepting a worse solution
double SimulatedAnnealing::getProbability(int diff, double temperature) {
    // Use the exponential function to determine the acceptance probability
    return exp(diff / temperature);
}

vector<int> SimulatedAnnealing::getPath() {
    return best_path;
}

// Constructor for the SimulatedAnnealing class
SimulatedAnnealing::SimulatedAnnealing(Graph graph, int time, double rate, vector<int> path_mst) {
    // Initialize the matrix, matrix_size, time bound, cooling rate, and initial temperature
    matrix = graph.getMatrix();
    matrix_size = graph.getMatrixSize();
    search_time_limit = time;
    cooling_rate = rate;
    initial_temperature = calculateTemperature();
    permutation = std::move(path_mst);         // Set the initial permutation - greedy algorithm
}

// Destructor for the SimulatedAnnealing class
SimulatedAnnealing::~SimulatedAnnealing() {
}
