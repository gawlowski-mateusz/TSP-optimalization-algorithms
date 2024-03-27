//
// Created by Mateusz on 04/12/2023.
//

#include "Graph.h"
#include <fstream>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include "../lib/tinyxml2-9.0.0/tinyxml2.h"

using namespace tinyxml2;

string Graph::getDescription() {
    if (!matrix_size) {
        return "No data\n";
    } else {
        return description;
    }
}

void Graph::printMatrix() {
    string graph = "";
    graph.append(description);

    cout << "== CURRENT MATRIX ==" << endl << endl;
    cout << graph;

    for (int row = 0; row < matrix_size; row++) {
        for (int column = 0; column < matrix_size; column++) {
            if (matrix[row][column] == 100000000) {
                printf("%4s", "N"); // Print the matrix elements.
            } else {
                printf("%4d", matrix[row][column]); // Print the matrix elements.
            }
        }
        cout << endl;
    }
}

bool Graph::infDiag() {
    if (!matrix_size)
        return false;
    else {
        for (int i = 0; i < matrix_size; i++) {
            matrix[i][i] = INF;
        }
        return true;
    }
}

bool Graph::readGraphATSP(string file_name) {
    file_name = "../bin/" + file_name;
    int **temporary;
    description = "";
    string temporaryDesc;

    ifstream file;
    file.open(file_name);

    if (file.fail() || file.eof()) {
        return false;
    }

    if (matrix_size) {
        for (int i = 0; i < matrix_size; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    getline(file, temporaryDesc);

    description.append(temporaryDesc + "\n");

    getline(file, temporaryDesc);

    description.append(temporaryDesc + "\n");

    getline(file, temporaryDesc);

    description.append(temporaryDesc + "\n");

    file >> temporaryDesc;

    description.append(temporaryDesc);

    file >> matrix_size;


    description.append(to_string(matrix_size) + "\n");


    getline(file, temporaryDesc);
    getline(file, temporaryDesc);
    getline(file, temporaryDesc);
    getline(file, temporaryDesc);

    temporary = new int *[matrix_size];

    for (int i = 0; i < matrix_size; i++) {
        temporary[i] = new int[matrix_size];
    }

    for (int column = 0; column < matrix_size; column++) {
        for (int row = 0; row < matrix_size; row++) {
            file >> temporary[row][column];
        }
    }

    file.close();

    matrix = temporary;
    return true;
}

bool Graph::readGraphXML(string file_name) {
    string x = "../bin/" + file_name;
    const char *file = x.c_str();
    int **temporary;

    XMLDocument document;
    document.LoadFile(file);

    if (matrix_size) {
        for (int i = 0; i < matrix_size; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    auto root = document.FirstChildElement("travellingSalesmanProblemInstance");
    auto graph = root->FirstChildElement("graph");

    matrix_size = 0;

    for (auto vertexElement = graph->FirstChildElement("vertex");
         vertexElement; vertexElement = vertexElement->NextSiblingElement("vertex")) {
        matrix_size++;
    }

    description.append("Name: " + string(root->FirstChildElement("name")->GetText()) + "\n");
    description.append("Description: " + string(root->FirstChildElement("description")->GetText()) + "\n");
    description.append("Matrix size: " + to_string(matrix_size) + "\n");

    temporary = new int *[matrix_size];

    for (int i = 0; i < matrix_size; i++) {
        temporary[i] = new int[matrix_size];
    }

    auto vertex = graph->FirstChildElement("vertex");

    for (int column = 0; column < matrix_size; column++) {
        auto edge = vertex->FirstChildElement("edge");
        int row = 0;

        while (edge != nullptr) {
            temporary[row][column] = edge->FindAttribute("cost")->DoubleValue();
            edge = edge->NextSiblingElement("edge");
            ++row;
        }

        vertex = vertex->NextSiblingElement();
    }

    matrix = temporary;
    return true;
}

int Graph::getMatrixSize() {
    return matrix_size;
}

int Graph::calculatePathWeightFromFile(string file_name) {
    file_name = "../bin/" + file_name;
    int size = 0;
    int weight = 0;
    int first_argument;
    int second_argument;

    ifstream file;
    file.open(file_name);

    if (file.is_open()) { // always check whether the file is open
        file >> size; // pipe file's content into stream
//        cout << matrix_size << endl;

        file >> first_argument;

        for (int i = 0; i < size - 1; i++) {
            file >> second_argument;

            weight += matrix[first_argument][second_argument];
//            cout << weight << endl;
//            cout << first_argument << " " << second_argument << endl << endl;

            first_argument = second_argument;
        }
    }

    return weight;
}

int Graph::calculatePathWeight(vector<int> path) {
    int size;
    int weight = 0;
    int first_argument;
    int second_argument;

    size = path.size();
//        cout << matrix_size << endl;

    for (int i = 0; i < size - 1; i++) {
        first_argument = path[i];
        second_argument = path[i + 1];

        weight += matrix[first_argument][second_argument];
//            cout << weight << endl;
//            cout << first_argument << " " << second_argument << endl << endl;
//            cout << i << endl;
    }

    return weight;
}

vector<int> Graph::loadPathFromFile(string file_name) {
    file_name = "../bin/" + file_name;
    int size = 0;
    int argument;
    vector<int> path;

    ifstream file;
    file.open(file_name);

    if (file.is_open()) { // always check whether the file is open
        file >> size; // pipe file's content into stream
        path.reserve(size);

        for (int i = 0; i < size - 1; i++) {
            file >> argument;
            path.push_back(argument);
        }
    }
    return path;
}

Graph::Graph() {

}

Graph::~Graph() {

}

int **Graph::getMatrix() {
    return matrix;
}

void Graph::generateRandom(int size) {
    matrix_size = size;
    int **buffer = nullptr;
    buffer = new int *[matrix_size];

    srand(time(NULL));

    for (int i = 0; i < matrix_size; i++) {
        buffer[i] = new int[matrix_size];

        for (int j = 0; j < matrix_size; j++) {
            buffer[i][j] = rand() % 100 + 1;
        }
    }

    matrix = buffer;

    infDiag();
}

