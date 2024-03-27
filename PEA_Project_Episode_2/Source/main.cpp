//
// Created by Mateusz on 04/12/2023.
//

#include <iostream>
#include "string"
#include "fstream"
#include "../Graph/Graph.h"
#include "../TabuSearch/TabuSearch.h"
#include "../SimulatedAnnealing/SimulatedAnnealing.h"
#include "../PrimAlgorithm/PrimAlgorithm.h"

using namespace std;

int setTimeValue() {
    int time_value;

    cout << "Enter Time value >> ";
    cin >> time_value;

    if (time_value < 0) {
        cout << "Time value must be greater than 0" << endl;
        return 0;
    } else {
        cout << "Success!" << endl;
        return time_value;
    }
}

double setDTvalue() {
    double dT_value;

    cout << "Enter dT value >> ";
    cin >> dT_value;

    if (dT_value < 0) {
        cout << "dT value must be greater than 0" << endl;
        return 0;
    } else {
        cout << "Success!" << endl;
        return dT_value;
    }
}

void savePathToFile(vector<int> path_to_save) {
    string file_name;

    cout << "Enter file name >> ";
    cin >> file_name;

    file_name = "../bin/" + file_name;

    //open file for writing
    ofstream file(file_name, std::ofstream::out);

    //check if file was successfully opened for writing
    if (file.is_open()) {
        file << path_to_save.size() << "\n";

        //store vector content to file
        for (int i = 0; i < path_to_save.size(); i++) {
            if (i == path_to_save.size() - 1) {
                file << path_to_save[i];
            } else {
                file << path_to_save[i] << "\n";
            }
        }
//        file << loop_value;

        file.close();
        cout << "Success!" << endl;
    } else {
        cout << "Data can not be write";
    }
}

int main() {
    Graph graph;

    int time = 0;
    int weight;
    int greedy_weight;
    double temperature_factor = 0;
    string file_name;
    char option;
    bool was_data_loaded;

    vector<int> greedy_path;
    vector<int> file_path;
    vector<int> path_to_save;

    do {
        cout << "\nCurrent Time value : " << time << " s" << endl;
        cout << "Current dT value   : " << temperature_factor << endl << endl;

//        cout << graph.getDescription() << endl;

        cout << "==== MAIN MENU ====" << endl;
        cout << "1. Load graph from file" << endl;
        cout << "2. Set time" << endl;
        cout << "3. Set dT parameter" << endl;
        cout << "4. Print current matrix" << endl;
        cout << "5. Tabu Search" << endl;
        cout << "6. Simulated Annealing" << endl;
        cout << "7. Save current Path" << endl;
        cout << "8. Calculate Path weight from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: >> ";
        cin >> option;
        cout << endl;

        switch (option) {
            case '1':
                int option_file_type;

                cout << "Would you like to read ATSP or XML file?" << endl;
                cout << "0 -> ATSP" << endl;
                cout << "1 -> XML" << endl;
                cout << "Choose option: >> ";
                cin >> option_file_type;

                cout << "\nEnter file name >> ";
                cin >> file_name;

                if (option_file_type == 1) {
                    was_data_loaded = graph.readGraphXML(file_name);
                    graph.readGraphXML(file_name);
                } else {
                    was_data_loaded = graph.readGraphATSP(file_name);
                    graph.readGraphATSP(file_name);
                }

                if (!was_data_loaded) {
                    cout << "File can not be read" << endl;
                } else {
                    cout << "File read successfully" << endl;

                    PrimAlgorithm primAlgorithm(graph);
                    greedy_path = primAlgorithm.getPathMST();
                    primAlgorithm.printPath(greedy_path);

                    greedy_weight = graph.calculatePathWeight(greedy_path);

                    cout << "Loaded Path weight: " << greedy_weight << endl;
                }
                break;

            case '2':
                time = setTimeValue();
                break;

            case '3':
                temperature_factor = setDTvalue();
                break;

            case '4':
                if (graph.getMatrixSize() > 0) {
//                    graph.printMatrix();
                    cout << graph.getDescription();
                } else {
                    cout << "Current matrix is empty" << endl;
                }
                break;

            case '5':
                if (!time) {
                    cout << "Time value must not be equal 0" << endl;
                } else {
                    int option_path_source;
                    int option_neighbours;

                    cout << "Would you like to continue with MST or Path loaded from file?" << endl;
                    cout << "0 -> MST" << endl;
                    cout << "1 -> Path from file" << endl;
                    cout << "Choose option: >> ";
                    cin >> option_path_source;

                    cout << "\nWhich type of neighbours would you like to use?" << endl;
                    cout << "0 -> Swap" << endl;
                    cout << "1 -> Insert" << endl;
                    cout << "2 -> Invert" << endl;
                    cout << "Choose option: >> ";
                    cin >> option_neighbours;

                    if (option_path_source == 0) {
                        cout << "Tabu Search algorithm processing..." << endl;
                        TabuSearch tabuSearch(graph, time, greedy_path);

                        if (option_neighbours == 1) {
                            tabuSearch.startAlgorithm(1);
                            path_to_save = tabuSearch.getPath();
                        } else if (option_neighbours == 2) {
                            tabuSearch.startAlgorithm(2);
                            path_to_save = tabuSearch.getPath();
                        } else {
                            tabuSearch.startAlgorithm(0);
                            path_to_save = tabuSearch.getPath();
                        }
                    } else {
                        cout << "Enter file name >> ";
                        cin >> file_name;

                        file_path = graph.loadPathFromFile(file_name);
                        TabuSearch tabuSearch(graph, time, file_path);

                        cout << "Tabu Search algorithm processing..." << endl;

                        if (option_neighbours == 1) {
                            tabuSearch.startAlgorithm(1);
                            path_to_save = tabuSearch.getPath();
                        } else if (option_neighbours == 2) {
                            tabuSearch.startAlgorithm(2);
                            path_to_save = tabuSearch.getPath();
                        } else {
                            tabuSearch.startAlgorithm(0);
                            path_to_save = tabuSearch.getPath();
                        }
                    }
                }
                break;

            case '6':
                if (!time || !temperature_factor) {
                    cout << "Time and dT value must not be equal 0" << endl;
                } else {
                    int option_path_source;

                    cout << "Would you like to continue with MST or Path loaded from file?" << endl;
                    cout << "0 -> MST" << endl;
                    cout << "1 -> Path from file" << endl;
                    cout << "Choose option: >> ";
                    cin >> option_path_source;

                    cout << "Simulated Annealing algorithm processing..." << endl;

                    if (option_path_source == 0) {
                        SimulatedAnnealing simulatedAnnealing(graph, time, temperature_factor, greedy_path);
                        simulatedAnnealing.startAlgorithm();
                        path_to_save = simulatedAnnealing.getPath();
                    } else {
                        cout << "Enter file name >> ";
                        cin >> file_name;

                        file_path = graph.loadPathFromFile(file_name);

                        SimulatedAnnealing simulatedAnnealing(graph, time, temperature_factor, file_path);
                        simulatedAnnealing.startAlgorithm();
                        path_to_save = simulatedAnnealing.getPath();
                    }
                }
                break;

            case '7':
                savePathToFile(path_to_save);
                break;

            case '8':
                cout << "Enter file name >> ";
                cin >> file_name;

                weight = graph.calculatePathWeightFromFile(file_name);

                cout << "Loaded Path weight: " << weight << endl;
                break;
        }

    } while (option != '0');

    return 0;
}