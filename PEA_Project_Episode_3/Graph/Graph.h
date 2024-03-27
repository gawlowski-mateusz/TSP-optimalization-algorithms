#pragma once

#include <string>
#include <vector>

#define INF 100000000

using namespace std;

struct BestPath {
    double time;
    int cost;

    BestPath(double time, int cost) {
        this->time = time;
        this->cost = cost;
    }

    BestPath() = default;
};

class Graph {
private:

    int **matrix = nullptr;
    int matrix_size = 0;
    string description = "";

public:
    void saveTimeRelativeToCost(string fileName, vector<BestPath> paths);

    void savePathToFile(string file_name, int cost, vector<int> best_path);

    string getDescription();

    void printMatrix();

    bool setDiagonal();

    int getMatrixSize();

    int **getMatrix();

    void generateRandom(int size);

    bool loadXML(string file);

    bool loadATSP(string file_name);

    Graph();

    ~Graph();
};

