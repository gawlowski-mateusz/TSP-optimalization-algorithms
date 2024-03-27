//
// Created by Mateusz on 16/10/2023.
//

#include <iostream>
#include "string"
#include "../Graph/Graph.h"
#include "../BruteForce/BruteForce.h"
#include "../BranchAndBound/BranchAndBound.h"
#include "../DynamiCProgramming/DynamicProgramming.h"
#include "../Time/Time.h"
#include "../Tests/Tests.h"

using namespace std;

void print_matrix(Graph graph) {
    if (graph.getMatrixSize() > 0) {
        graph.printMatrix();
    } else {
        cout << "Current matrix is empty" << endl;
    }
    // Display the matrix if it's not empty; otherwise, show an "empty matrix" message.
}

int main() {
    Graph graph;
    Time time;
    Tests tests;
    string file_name;
    int size = 0;

//    tests.test();

    char option;
    bool was_data_loaded = false;

    do {
        cout << "\n==== MAIN MENU ====" << endl;
        cout << "1. Load Data from file" << endl;
        cout << "2. Generate random matrix" << endl;
        cout << "3. Print current matrix" << endl;
        cout << "4. BruteForce" << endl;
        cout << "5. Branch & Bound" << endl;
        cout << "6. Dynamic Programming" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: >> ";
        cin >> option;
        cout << endl;

        switch (option) {
            case '1':
                cout << "Enter file name >> ";
                cin >> file_name;

                was_data_loaded = graph.readGraph(file_name);

                if (!was_data_loaded) {
                    cout << "File can not be read" << endl;
                } else {
                    cout << "File read successfully" << endl;
                }

                graph.setDiagonal();

                break;

            case '2':
                cout << "Insert matrix size >> ";
                cin >> size;

                was_data_loaded = graph.generateRandom(size);

                if (graph.getMatrixSize() > 0) {
                    cout << "Matrix created successfully" << endl;
                } else {
                    cout << "Error during Matrix creation" << endl;
                }

                break;

            case '3':
                print_matrix(graph);
                break;

            case '4':
                if (was_data_loaded) {
                    BruteForce bruteForce(graph);
                    cout << "BruteForce algorithm processing..." << endl;
                    time.startTime();
                    bruteForce.startRecursiveAlgorithm();
                    time.stopTime();
                    cout << "Execution time: " << time.processTime() << " ns -> " << time.processTime() * 0.000000001 << " s" << endl;
                    bruteForce.showResult();
                } else {
                    cout << "No data loaded" << endl;
                }
                break;

            case '5':
                if (was_data_loaded) {
                    BranchAndBound branchAndBound(graph);
                    cout << "BranchAndBound algorithm processing..." << endl;
                    time.startTime();
                    branchAndBound.startRecursiveAlgorithm();
                    time.stopTime();
                    cout << "Execution time: " << time.processTime() << " ns -> " << time.processTime() * 0.000000001 << " s" << endl;
                    branchAndBound.showResults();
                } else {
                    cout << "No data loaded" << endl;
                }
                break;
            case '6':
                if (was_data_loaded) {
                    DynamicProgramming dynamicProgramming(graph);
                    cout << "DynamicProgramming algorithm processing..." << endl;
                    time.startTime();
                    dynamicProgramming.startRecursiveAlgorithm();
                    time.stopTime();
                    cout << "Execution time: " << time.processTime() << " ns -> " << time.processTime() * 0.000000001 << " s" << endl;
                    dynamicProgramming.showResults();
                } else {
                    cout << "No data loaded" << endl;
                }
                break;
        }

    } while (option != '0');

    return 0;
}