//
// Created by Mateusz on 14/01/2024.
//

#include <iostream>
#include "string"
#include "../Graph/Graph.h"
#include "../GeneticAlgorithm//GeneticAlgorithm.h"

bool setCrossingType();

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

int setPopulationSize() {
    int population_size;

    cout << "Enter population matrix_size >> ";
    cin >> population_size;

    if (population_size < 0) {
        cout << "Population matrix_size must be greater than 0" << endl;
        return 0;
    } else {
        cout << "Success!" << endl;
        return population_size;
    }
}

float setMutationRate() {
    float mutation_rate;

    cout << "Enter mutation rate >> ";
    cin >> mutation_rate;

    if (mutation_rate < 0) {
        cout << "Mutation rate must be greater than 0" << endl;
        return 0;
    } else {
        cout << "Success!" << endl;
        return mutation_rate;
    }
}

float setCrossingRate() {
    float crossing_rate;

    cout << "Enter crossing rate >> ";
    cin >> crossing_rate;

    if (crossing_rate < 0) {
        cout << "Crossing rate must be greater than 0" << endl;
        return 0;
    } else {
        cout << "Success!" << endl;
        return crossing_rate;
    }
}

bool setCrossingType() {
    int crossing_type;

    cout << "Enter crossing type " << endl;
    cout << "0 -> OX" << endl;
    cout << "1 -> PX" << endl;

    cin >> crossing_type;

    if (crossing_type == 1) {
        return false;
    } else {
        return true;
    }
}


int main() {
    Graph graph;

    int time = 120;
    int population_size = 1000;
    float mutation_rate = 0.01;
    float crossing_rate = 0.8;

    string file_name;
    char option;
    bool was_data_loaded;
    bool crossing_type = true;

    vector<int> greedy_path;
    vector<int> file_path;
    vector<int> path_to_save;

    do {
        cout << "\nCurrent Time value    : " << time << " s" << endl;
        cout << "Starting population   : " << population_size << endl;
        cout << "Current mutation rate : " << mutation_rate << endl;
        cout << "Current crossing rate : " << crossing_rate << endl;

        if (crossing_type) {
            cout << "Current crossing type : OX" << endl << endl;
        } else {
            cout << "Current crossing type : PX" << endl << endl;
        }

        cout << "==== MAIN MENU ====" << endl;
        cout << "1. Load graph from file" << endl;
        cout << "2. Set time" << endl;
        cout << "3. Set starting population matrix_size" << endl;
        cout << "4. Set mutation rate" << endl;
        cout << "5. Set crossing rate" << endl;
        cout << "6. Choose crossing rate" << endl;
        cout << "7. Genetic Algorithm" << endl;
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
                    was_data_loaded = graph.loadXML(file_name);
                    graph.loadXML(file_name);
                } else {
                    was_data_loaded = graph.loadATSP(file_name);
                    graph.loadATSP(file_name);
                }

                if (!was_data_loaded) {
                    cout << "File can not be read" << endl;
                } else {
//                    cout << graph.getDescription() << endl;
                    cout << "File read successfully" << endl;
                }
                break;

            case '2':
                time = setTimeValue();
                break;

            case '3':
                population_size = setPopulationSize();
                break;

            case '4':
                mutation_rate = setMutationRate();
                break;

            case '5':
                crossing_rate = setCrossingRate();
                break;

            case '6':
                crossing_type = setCrossingType();
                break;

            case '7':
                if (!time || !population_size || mutation_rate == 0.0 || crossing_rate == 0.0) {
                    cout << "Time, population matrix_size, mutation rade and crossing rate must not be equal 0" << endl;
                } else if (!was_data_loaded) {
                    cout << "There is no data loaded - Graph is empty" << endl;
                } else {
                    GeneticAlgorithm geneticAlgorithm(graph, time, population_size, crossing_rate, mutation_rate);

                    cout << "Genetic Algorithm processing..." << endl << endl;

                    geneticAlgorithm.start(crossing_type);

                    cout << geneticAlgorithm.toString();
                    cin.get();
                }
                break;
        }

    } while (option != '0');

    return 0;
}
