//
// Created by Mateusz on 06.12.2023.
//

#pragma once

#include "../Graph/Graph.h"
#include <vector>

struct Node {
    int weight;
    int destination;

    Node(int weight, int destination) : weight(weight), destination(destination) {}

    Node() {}
};

class PrimAlgorithm {

private:
    int **matrix;
    int nodes;

public:
    PrimAlgorithm(Graph graph);

    vector<int> getPathMST();

    void printPath(vector<int> path);
};