#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <Customer.cpp>
#include <Matrix.cpp>

using namespace std;
class VRP
{
private:
    int numNodes;
    Matrix cost;
    vector<vector<int>> duration; // duration for servicing node from plus the time for traversing the arc from from to to.

    int LIMIT;
    vector<vector<int>> vehicle_startPositions;
    vector<vector<int>> time_windows;


public:
    VRP(int numNodes, Matrix cost)
    {
        this->numNodes = numNodes;
        this->cost = cost;
    }
};
