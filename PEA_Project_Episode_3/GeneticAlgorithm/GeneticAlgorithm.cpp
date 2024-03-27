#include "GeneticAlgorithm.h"
#include <ctime>
#include <iostream>
#include "../lib/effolkronium/random.hpp"

using Random = effolkronium::random_static;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

// Constructor for GeneticAlgorithm class
GeneticAlgorithm::GeneticAlgorithm(Graph graph, int stop, int population, float crossing_rate, float mutation_rate) {
    weight = INT32_MAX;
    matrix = graph.getMatrix();
    matrix_size = graph.getMatrixSize();
    population_size = population;

    this->stop = stop;
    this->crossing_rate = crossing_rate;
    this->mutation_rate = mutation_rate;
}

// Calculate the total cost of a given path in the graph
int GeneticAlgorithm::calculatePath(std::vector<int> &path) {
    int result = 0;

    for (int i = 0; i < matrix_size - 1; i++) {
        result += matrix[path[i]][path[i + 1]];
    }

    result += matrix[path[matrix_size - 1]][path[0]];

    return result;
}

// Perform partially-mapped crossover between two parent paths
void GeneticAlgorithm::partiallyCrossover(std::vector<int> &parent_1, std::vector<int> &parent_2) {
    // Initialization of descendant paths and mapping vectors
    std::vector<int> descendant_1(matrix_size, 0), descendant_2(matrix_size, 0);
    std::vector<int> map_1(matrix_size, -1), map_2(matrix_size, -1);
    int begin, end, temporary;

    // Select a random subpath for crossover
    do {
        begin = Random::get(2, matrix_size - 1);
        end = Random::get(2, matrix_size - 1);
    } while ((0 >= (end - begin)) || !begin || !(end - (matrix_size - 1)));

    // Perform crossover and update mapping vectors
    for (int i = begin; i <= end; i++) {
        descendant_1[i] = parent_1[i];
        descendant_2[i] = parent_2[i];
        map_1[parent_1[i]] = parent_2[i];
        map_2[parent_2[i]] = parent_1[i];
    }

    for (int p = 1, d = 1; p < matrix_size && d < matrix_size;) {
        if (d == begin) {
            d = end + 1;
            p = end + 1;
        }

        if (!(isInPath(parent_2[p], begin, end, descendant_1))) {
            descendant_1[d] = parent_2[p];

        } else {
            temporary = parent_2[p];

            do {
                temporary = map_1[temporary];
            } while (isInPath(temporary, begin, end, descendant_1));

            descendant_1[d] = temporary;
        }
        d++;
        p++;
    }

    for (int p = 1, d = 1; p < matrix_size && d < matrix_size;) {
        if (d == begin) {
            d = end + 1;
            p = end + 1;
        }

        if (!(isInPath(parent_1[p], begin, end, descendant_2))) {
            descendant_2[d] = parent_1[p];

        } else {
            temporary = parent_1[p];

            do {
                temporary = map_2[temporary];
            } while (isInPath(temporary, begin, end, descendant_2));

            descendant_2[d] = temporary;
        }

        d++;
        p++;
    }

    // Update parent paths with the generated descendant paths
    parent_1.clear();
    parent_2.clear();
    parent_1 = descendant_1;
    parent_2 = descendant_2;
}


// Initialization of descendant paths and iterators
void GeneticAlgorithm::orderedCrossover(std::vector<int> &parent_1, std::vector<int> &parent_2) {
    std::vector<int> descendant_1(matrix_size), descendant_2(matrix_size);
    std::vector<int>::iterator itr1, itr2;
    int begin, end;

    do {
        begin = Random::get(2, matrix_size - 2);
        end = Random::get(2, matrix_size - 2);
    } while (end < begin);

    for (int i = begin; i <= end; i++) {
        descendant_1[i] = parent_1[i];
        descendant_2[i] = parent_2[i];
    }

    for (int p = 1, d = 1; p < matrix_size && d < matrix_size;) {
        if (d == begin) {
            d = end + 1;
        }

        if (!(isInPath(parent_2[p], begin, end, descendant_1))) {
            descendant_1[d] = parent_2[p];
            d++;
        }

        p++;
    }

    for (int p = 1, d = 1; p < matrix_size && d < matrix_size;) {
        if (d == begin) {
            d = end + 1;
        }

        if (!(isInPath(parent_1[p], begin, end, descendant_2))) {
            descendant_2[d] = parent_1[p];
            d++;
        }

        p++;
    }

    parent_1.clear();
    parent_2.clear();
    parent_1 = descendant_1;
    parent_2 = descendant_2;
}

// Check if an element is present in a path between specified indices
bool GeneticAlgorithm::isInPath(int element, int begin, int end, std::vector<int> &path) {
    for (int i = begin; i <= end; i++) {
        if (element == path[i])
            return true;
    }
    return false;
}

// Start the genetic algorithm with specified parameters
int GeneticAlgorithm::start(bool crossing) {
    // Initialization of populations, fitness, and permutation vector
    std::vector<std::vector<int>> population, next_population;
    std::vector<int> fitness, permutation;
    std::clock_t start;

    int best_path_index;
    int tournament_size = 5;
    int index, result, p_1, p_2;

    for (int i = 0; i < matrix_size; i++) {
        permutation.push_back(i);
    }

    // Generate the initial population
    for (int i = 0; i < population_size; i++) {
        std::shuffle(++permutation.begin(), permutation.end(), std::default_random_engine(seed));
        population.push_back(permutation);
    }

    start = std::clock();

    // Run the genetic algorithm until the specified stop criterion is met
    while (((std::clock() - start) / (CLOCKS_PER_SEC)) < stop) {
        fitness.clear();

        // Evaluate the fitness of individuals in the current population
        for (auto &iterator: population) {
            fitness.push_back(calculatePath(iterator));
        }

        // Select individuals for the next generation using tournament selection
        for (int j = 0; j < population_size; j++) {
            result = INT32_MAX;

            // Perform tournament selection
            for (int k = 0; k < tournament_size; k++) {
                index = Random::get(0, population_size - 1);

                if (fitness[index] < result) {
                    result = fitness[index];
                    permutation.clear();
                    permutation = population[index];

                    auto foundTime = (clock() - start) / (double) CLOCKS_PER_SEC;

                    if (weight > result) {
                        weight = result;
                        best_path_index = index;
                    }
                }
            }

            next_population.push_back(permutation);
        }

		// Update the current population with the selected individuals
		for (auto &iterator: population) {
			iterator.clear();
		}

		population.clear();
		population = next_population;

        for (auto &iterator: next_population) {
            iterator.clear();
        }

        next_population.clear();

        // Perform crossover between pairs of individuals
        for (int j = 0; j < (int) (crossing_rate * (float) population_size); j += 2) {
            do {
                p_1 = Random::get(0, population_size - 1);
                p_2 = Random::get(0, population_size - 1);
            } while (!(p_1 - p_2));

            // Perform ordered or partially-mapped crossover based on the 'crossing' parameter
            if (crossing)
                orderedCrossover(population.at(j), population.at(j + 1));
            else
                partiallyCrossover(population.at(j), population.at(j + 1));
        }

        // Perform mutations on selected individuals
        for (int j = 0; j < (int) (mutation_rate * (float) population_size); j++) {
            do {
                p_1 = Random::get(0, matrix_size - 1);
                p_2 = Random::get(0, matrix_size - 1);
            } while (!(p_1 - p_2));

            std::swap(population.at(j)[p_1], population.at(j)[p_2]);
        }
//        std::shuffle(population.begin(), population.end(), std::default_random_engine(seed));
    }
    best_path = population[best_path_index];

    return weight;
}

string GeneticAlgorithm::toString() {
    string result;
    result += "Weight: " + to_string(weight);
    result += "\nminPath: ";

    for (int i: best_path) {
        result += to_string(i) + " ";
    }

    result += "0 \n";

    return result;
}

vector<BestPath> GeneticAlgorithm::getTimeRelativeToCost() {
    return time_relative_to_cost;
}

vector<int> GeneticAlgorithm::getFinalPath() {
    return best_path;
}