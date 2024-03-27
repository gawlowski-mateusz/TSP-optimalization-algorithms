//
// Created by Mateusz on 12/12/2023.
//

#pragma once

#include <vector>
#include "../Graph/Graph.h"
#include "../PrimAlgorithm/PrimAlgorithm.h"

class SimulatedAnnealing {
    double initial_temperature = 0;
    double cooling_rate = 0;
    double search_time_limit = 0;
    double searching_time = 0;
    double temperature;
    int **matrix;
    int matrix_size;
    int result;
//    PrimAlgorithm primAlgorithm;
    vector<int> best_path;
    vector<int> permutation;

public:

    int startAlgorithm();

    vector<int> randomPermutation(int size);
    vector<int> getPath();


    double calculateTemperature();

    int calculatePathWeight(vector<int> path);

    double getProbability(int diff, double temperature);

    SimulatedAnnealing(Graph graph, int time, double rate, vector<int> path_mst);

    ~SimulatedAnnealing();

    void savePath(string file_name);

    void saveResults(string file_name);
};

