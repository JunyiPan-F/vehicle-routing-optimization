# include <iostream>
# include <vector>
# include <math.h>
# include <stdlib.h>
# include <Customer.cpp>
# include <Matrix.cpp>

using namespace std;
class TSP
{
private:
    int numNodes;
    Matrix cost;
    int LIMIT;
    vector<vector<int,int>> vehicle_startPositions;
    

public:
    TSP(int numNodes, Matrix cost)
    {
        this->numNodes = numNodes;
        this->cost = cost;
    }
    

};

