#include "Graph.h"
#include <fstream>
#include <time.h>
#include <string>
#include <iostream>
#include "../lib/tinyxml2-9.0.0/tinyxml2.h"

using namespace tinyxml2;

string Graph::getDescription() {
    if (!matrix_size) {
        return "No data\n";
    } else {
        return description;
    }
}

void Graph::saveTimeRelativeToCost(string fileName, vector<BestPath> paths) {
    fileName = "../bin/" + fileName;

    ofstream file;
    file.open(fileName);
    file << matrix_size << endl;

    for (BestPath path: paths) {
        file << path.cost << ";" << path.time << endl;
    }

    file.close();
}

bool Graph::setDiagonal() {
    if (!matrix_size)
        return false;
    else {
        for (int i = 0; i < matrix_size; i++) {
            matrix[i][i] = -1;
        }
        return true;
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


bool Graph::loadXML(string file) {
    string x = "../bin/" + file;
    const char *fileName = x.c_str();
    int **temp;

    XMLDocument doc;
    doc.LoadFile(fileName);

    if (matrix_size) {
        for (int i = 0; i < matrix_size; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    auto root = doc.FirstChildElement("travellingSalesmanProblemInstance");
    auto graph = root->FirstChildElement("graph");

    matrix_size = 0;

    for (auto vertexElement = graph->FirstChildElement(
            "vertex"); vertexElement; vertexElement = vertexElement->NextSiblingElement("vertex")) {
        matrix_size++;
    }

    description.append("Name:" + string(root->FirstChildElement("name")->GetText()) + "\n");
    description.append("Description:" + string(root->FirstChildElement("description")->GetText()) + "\n");
    description.append("Vertex count: " + to_string(matrix_size) + "\n");


    temp = new int *[matrix_size];

    for (int i = 0; i < matrix_size; i++) {
        temp[i] = new int[matrix_size];
    }


    auto vertex = graph->FirstChildElement("vertex");

    for (int column = 0; column < matrix_size; column++) {
        auto edge = vertex->FirstChildElement("edge");
        int row = 0;

        while (edge != nullptr) {
            temp[row][column] = edge->FindAttribute("cost")->DoubleValue();
            edge = edge->NextSiblingElement("edge");
            ++row;
        }
        vertex = vertex->NextSiblingElement();
    }

    matrix = temp;
    return true;

}

bool Graph::loadATSP(string file_name) {
    file_name = "../bin/" + file_name;
    int **temporary;
    description = "";
    string temporary_desc = "";

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

    getline(file, temporary_desc);
    description.append(temporary_desc + "\n");

    getline(file, temporary_desc);
    description.append(temporary_desc + "\n");

    getline(file, temporary_desc);
    description.append(temporary_desc + "\n");

    file >> temporary_desc;
    description.append(temporary_desc);

    file >> matrix_size;
    description.append(to_string(matrix_size) + "\n");

    getline(file, temporary_desc);
    getline(file, temporary_desc);
    getline(file, temporary_desc);
    getline(file, temporary_desc);

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

int Graph::getMatrixSize() {
    return matrix_size;
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

    setDiagonal();
}

void Graph::savePathToFile(string file_name, int cost, vector<int> best_path) {
    file_name = "../bin/" + file_name;

    ofstream file;
    file.open(file_name);
    file << cost << endl;

    for (int node: best_path) {
        file << node << endl;
    }

    file.close();
}
