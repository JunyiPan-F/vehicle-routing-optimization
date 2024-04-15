# include <iostream>
# include <vector>
# include <math.h>
# include <stdlib.h>
using namespace std;

class Vehicle
{
private:
    int vehicle_id;
    int start_index;
    int capacity = 10;

public:

    Vehicle()
    {
        vehicle_id = 0;
        start_index = 0;
        capacity = 10;
    }
    
    Vehicle(int vehicle_id, int start_index, int capacity)
    {
        this->vehicle_id = vehicle_id;
        this->start_index = start_index;
        this->capacity = capacity;
    }

    void print()
    {
        cout << "Vehicle ID: " << vehicle_id << endl;
        cout << "Start Index: " << start_index << endl;
        cout << "Capacity: " << capacity << endl;
    }
};
