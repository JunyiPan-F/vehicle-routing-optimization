
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "vrp.h"

using namespace std;

int main()
{
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
        {9, 9, 9, 9, 9, 9, 9}};
    vector<Vehicle> vehicles = {
        {10, 0, 0, 0, {}},
        {10, 0, 0, 0, {}},
        {10, 0, 0, 0, {}}};

    divideConquer(customers, vehicles);

    vector<int> subset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<vector<double>> memo(10, vector<double>(9, -1));
    cout << tsp(customers, subset, 0, memo) << endl;
    return 0;
}