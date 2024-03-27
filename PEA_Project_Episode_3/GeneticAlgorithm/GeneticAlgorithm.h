
#pragma once
#include "../Graph/Graph.h"
#include <vector>

class GeneticAlgorithm
{
private:

    int stop;
    int population_size;
    float crossing_rate;
    float mutation_rate;
    int **matrix;
    int matrix_size;
    int weight;
    vector<int> best_path;
    vector<BestPath> time_relative_to_cost;


public:

    GeneticAlgorithm(Graph graph, int stop, int population, float crossing_rate, float mutation_rate);
    int calculatePath(std::vector<int> &path);
    void orderedCrossover(std::vector<int> &parent_1, std::vector<int> &parent_2);
    void partiallyCrossover(std::vector<int> &parent_1, std::vector<int> &parent_2);
    bool isInPath(int element, int begin, int end, std::vector<int> &path);
    int start(bool crossing);
    vector<BestPath> getTimeRelativeToCost();
    vector<int> getFinalPath();
    string toString();
};

