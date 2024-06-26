
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "vrp.h"

using namespace std;

int main() {
    // Define customers and vehicles
    vector<Customer> customers = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3, 3},
        {4, 4, 4, 4, 4, 4, 4},
        {5, 5, 5, 5, 5, 5, 5},
        {6, 6, 6, 6, 6, 6, 6},
        {7, 7, 7, 7, 7, 7, 7},
        {8, 8, 8, 8, 8, 8, 8},
        {9, 9, 9, 9, 9, 9, 9}
    };

vector<Vehicle> vehicles = {
        {0, 10, 0, 0, 0, {}},
        {1, 20, 0, 0, 0, {}},
        {2, 30, 0, 0, 0, {}}
    };

    // Use divide and conquer to solve the vehicle routing problem
    divideConquer(customers, vehicles);

    // Optionally, you can test the tsp function with a subset of data
    vector<Vehicle> subset = vehicles;
    vector<vector<double> > memo(10, vector<double>(9, -1));
    cout << "TSP result: " << tsp(customers, subset, 0, memo) << endl;

    return 0;
}

