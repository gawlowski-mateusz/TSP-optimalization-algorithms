//
// Created by Mateusz on 06.12.2023.
//

#include <vector>
#include <queue>
#include <iostream>
#include "PrimAlgorithm.h"
#include "../Graph/Graph.h"

using namespace std;

bool operator > (const Node &argument_1, const Node &argument_2) {
    if (argument_1.weight > argument_2.weight)
        return true;
    else
        return false;
}

bool operator < (const Node &argument_1, const Node &argument_2) {
    if (argument_1.weight < argument_2.weight)
        return true;
    else
        return false;
}

bool operator == (const Node &argument_1, const Node &argument_2) {
    if (argument_1.weight == argument_2.weight)
        return true;
    else
        return false;
}

void PrimAlgorithm::printPath(vector<int> path) {
    cout << "\nGreedy Path: ";

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }

    cout << endl;
}

vector<int> PrimAlgorithm::getPathMST() {
    vector<int> path;
    bool was_visited[nodes];

    for (int i = 0; i < nodes; i++)
        was_visited[i] = false;

    was_visited[0] = true;
    path.push_back(0);

    std::priority_queue<Node, std::vector<Node>, std::greater<>> queue;
    int preview = 0;
    Node node;

    for (int i = 0; i < nodes - 1; i++) {
        for (int v = 0; v < nodes; v++) {
            if (!was_visited[v] && matrix[preview][v] != INF) {
                node = Node(matrix[preview][v], v);
                queue.push(node);
            }
        }

        was_visited[preview] = true;

        do {
            node = queue.top();
            queue.pop();
        } while (was_visited[node.destination]);

        preview = node.destination;
        path.push_back(preview);
    }
    path.push_back(0);

    return path;
}

PrimAlgorithm::PrimAlgorithm(Graph graph) {
    matrix = graph.getMatrix();
    nodes = graph.getMatrixSize();
}