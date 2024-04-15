#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;

class Customer {

private:
    int id;
    vector<int, int> coordinates;
    int demand;
    int serviceTime;

public:

    Customer() {
        id = 0;
        coordinates = {0, 0};
        demand = 0;
        serviceTime = 0;
    }
    
    Customer(int id, vector<int, int> coordinates, int demand, int serviceTime) {
        this->id = id;
        this->coordinates = coordinates;
        this->demand = demand;
        this->serviceTime = serviceTime;
    }

    void print() {
        cout << "Customer ID: " << id << endl;
        cout << "Coordinates: " << coordinates[0] << ", " << coordinates[1] << endl;
        cout << "Demand: " << demand << endl;
        cout << "Service Time: " << serviceTime << endl;
    }

};