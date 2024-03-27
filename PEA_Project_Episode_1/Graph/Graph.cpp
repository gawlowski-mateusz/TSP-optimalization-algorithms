//
// Created by Mateusz on 16/10/2023.
//

#include "Graph.h"
#include <fstream>
#include <time.h>
#include <iostream>

bool Graph::readGraph(string file) {
    int **temp;

    ifstream data_file;
    data_file.open(file);

    if (data_file.fail() || data_file.eof()) {
        return false; // Failed to open or read the file.
    }

    if (matrix_size) {
        // Deallocate memory if the matrix already exists.
        for (int i = 0; i < matrix_size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    data_file >> matrix_size; // Read the size of the matrix from the file.

    temp = new int *[matrix_size];

    for (int i = 0; i < matrix_size; i++) {
        temp[i] = new int[matrix_size];
    }

    for (int row = 0; row < matrix_size; row++) {
        for (int column = 0; column < matrix_size; column++) {
            data_file >> temp[row][column]; // Read the matrix values from the file.
        }
    }

    data_file.close(); // Close the file.

    matrix = temp; // Update the matrix with the new data.
    return true; // Successfully read and loaded the matrix.
}

void Graph::printMatrix() {
    cout << "== CURRENT MATRIX ==\n";

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf("%4d", matrix[i][j]); // Print the matrix elements.
        }
        cout << endl;
    }
}

bool Graph::setDiagonal() {
    if (!matrix_size)
        return false; // Matrix size is zero; cannot set the diagonal.
    else {
        for (int i = 0; i < matrix_size; i++) {
            matrix[i][i] = -1; // Set the diagonal elements to -1.
        }
        return true; // Diagonal set successfully.
    }
}

int Graph::getMatrixSize() {
    return matrix_size; // Return the size of the matrix.
}

int **Graph::getMatrix() {
    return matrix; // Return a pointer to the matrix.
}

bool Graph::generateRandom(int size) {
    matrix_size = size;
    int **buffer = nullptr;
    buffer = new int *[matrix_size];

    srand(time(NULL));

    for (int i = 0; i < matrix_size; i++) {
        buffer[i] = new int[matrix_size];

        for (int j = 0; j < matrix_size; j++) {
            buffer[i][j] = rand() % 100 + 1; // Generate random values for the matrix.
        }
    }

    matrix = buffer; // Update the matrix with the randomly generated data.

    setDiagonal(); // Set the diagonal elements.
    return true; // Random matrix generated successfully.
}

Graph::Graph() {
    // Constructor: Default constructor, no specific initialization.
}

Graph::~Graph() {
    // Destructor: No specific cleanup needed since memory management is handled in other functions.
}
