#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;

class Matrix {

private:
    int rows;
    int cols;
    vector<vector<int>> matrix;

public:

    Matrix() {
        rows = 10;
        cols = 10;
    }

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        matrix.resize(rows, vector<int>(cols, 0));
    }

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }

    int get(int i, int j) {
        return matrix[i][j];
    }

    void set(int i, int j, int value) {
        matrix[i][j] = value;
    }

    void populate(int min, int max) {
        srand(time(NULL));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = min + (rand() % (max - min + 1));
            }
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};