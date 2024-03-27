//
// Created by Mateusz on 04/12/2023.
//

#pragma once

#include <string>
#include <vector>

#define INF 100000000

using namespace std;

class Graph {
private:

    int **matrix = nullptr;
    int matrix_size = 0;
    string description;

public:

    string getDescription();

    void printMatrix();

    bool infDiag();

    bool readGraphATSP(string file_name);

    bool readGraphXML(string file_name);

    int getMatrixSize();

    int **getMatrix();

    int calculatePathWeightFromFile(string file_name);

    int calculatePathWeight(std::vector<int> path);

    vector<int> loadPathFromFile(string file_name);

    void generateRandom(int size);

    Graph();

    ~Graph();
};