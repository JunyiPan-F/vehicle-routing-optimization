#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int num_customer;
const int num_vehicle;

struct Customer {
    int id;
    int x;
    int y;
    int demand;
    int ready_time;
    int due_time;
    int service_time;
};

struct Vehicle {
    int capacity;
    int current_load;
    int current_time;
    int current_location;
    vector<int> route;
};  

double distance(const Customer& a, const Customer& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// using the TSP  and nearest neighbor algorithm to solve the VRP、

double tsp(const vector<Customer>& customers, const vector<int>& subset, int start, vector<vector<double>>& memo) {
    if (subset.empty())
        return distance(customers[start], customers[0]); // Return distance to the starting point

    int n = subset.size();
    if (memo[start][n] != -1)
        return memo[start][n];

    double minDist = numeric_limits<double>::max();
    for (int i = 0; i < n; ++i) {
        int next = subset[i];
        vector<int> remaining;
        for (int j = 0; j < n; ++j) {
            if (j != i)
                remaining.push_back(subset[j]);
        }
        double dist = distance(customers[start], customers[next]) + tsp(customers, remaining, next, memo);
        minDist = min(minDist, dist);
    }

    memo[start][n] = minDist;
    return minDist;
}

// int nearestNeighbor(const vector<Customer>& customers, vector<int>& subset, int start) {
//     int n = subset.size();
//     int nearest = -1;
//     double minDist = numeric_limits<double>::max();
//     for (int i = 0; i < n; ++i) {
//         int next = subset[i];
//         double dist = distance(customers[start], customers[next]);
//         if (dist < minDist) {
//             minDist = dist;
//             nearest = next;
//         }
//     }
//     return nearest;
// }

void divideConquer(const vector<Customer>& customers, vector<Vehicle>& vehicles) {
    vector<vector<int>> clusters(num_vehicle);

    for (int i = 1; i < num_customer; ++i) {
        clusters[i % num_vehicle].push_back(i);
    }

    // Solve TSP for each cluster
    for (int i = 0; i < num_vehicle; ++i) {
        vector<int>& cluster = clusters[i];
        vector<vector<double>> memo(num_customer, vector<double>(cluster.size() + 1, -1));
        double minDist = tsp(customers, cluster, 0, memo);
        cout << "Cluster " << i+1 << " distance: " << minDist << endl;
    }
}



