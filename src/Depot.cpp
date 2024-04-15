#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;

class Depot{
private:
    int id;
    vector<int> coordinates;
    int maxVehicles;
    int maxCapacity;
    int maxDuration;
    vector<int> closest_customers;
public:

    Depot(){
        id = 0;
        coordinates = {0, 0};
        maxVehicles = 0;
        maxCapacity = 0;
        maxDuration = 0;
    }

    Depot(int id, vector<int> coordinates, int maxVehicles, int maxCapacity, int maxDuration){
        this->id = id;
        this->coordinates = coordinates;
        this->maxVehicles = maxVehicles;
        this->maxCapacity = maxCapacity;
        this->maxDuration = maxDuration;
    }

    void print(){
        cout << "Depot ID: " << id << endl;
        cout << "Coordinates: " << coordinates[0] << ", " << coordinates[1] << endl;
        cout << "Max Vehicles: " << maxVehicles << endl;
        cout << "Max Capacity: " << maxCapacity << endl;
        cout << "Max Duration: " << maxDuration << endl;
    }

    void setClosestCustomers(vector<int> closest_customers){
        this->closest_customers = closest_customers;
    }

    vector<int> getClosestCustomers(){
        return closest_customers;
    }
};

