#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int num_customer = 10 ;
const int num_vehicle = 3 ;

struct Customer {
    int id;
    int x;
    int y;
    int demand;
    int ready_time;
    int due_time;
    int service_time;

    Customer(int id_, int x_, int y_, int demand_, int ready_time_, int due_time_, int service_time_)
        : id(id_), x(x_), y(y_), demand(demand_), ready_time(ready_time_), due_time(due_time_), service_time(service_time_) {}
};

struct Vehicle {
    int id;
    int capacity;
    int current_load;
    int current_time;
    int current_location;
    vector<int> route;

    // Constructor with initializer list for 'route'
    // Vehicle(int id_, int capacity_, int current_load_, int current_time_, int current_location_, const vector<int>& route_)
    //     : id(id_), capacity(capacity_), current_load(current_load_), current_time(current_time_), current_location(current_location_), route(route_) {}
};



double distance(const Customer& a, const Customer& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// TSP algorithm to solve the vehicle routing problem
double tsp(const vector<Customer>& customers, const vector<Vehicle>& subset, int start, vector<vector<double> >& memo) {
    if (subset.empty())
        return distance(customers[start], customers[0]); // Return distance to the starting point

    int n = subset.size();
    if (memo[start][n] != -1)
        return memo[start][n];

    double minDist = numeric_limits<double>::max();
    for (int i = 0; i < n; ++i) {
        int next = subset[i].id;
        vector<Vehicle> remaining;
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

// // Nearest neighbor heuristic to construct initial routes
// vector<int> nearestNeighbor(const vector<Customer>& customers, vector<bool>& visited, int start) {
//     int n = customers.size();
//     vector<int> route;
//     route.push_back(start);
//     visited[start] = true;
//     for (int i = 0; i < n - 1; ++i) {
//         double minDist = numeric_limits<double>::max();
//         int nearest = -1;
//         for (int j = 0; j < n; ++j) {
//             if (!visited[j] && j != route.back()) {
//                 double dist = distance(customers[route.back()], customers[j]);
//                 if (dist < minDist) {
//                     minDist = dist;
//                     nearest = j;
//                 }
//             }
//         }
//         route.push_back(nearest);
//         visited[nearest] = true;
//     }
//     return route;
// }

// genetic algorithm to optimize the routes
vector<int> geneticAlgorithm(const vector<Customer>& customers, const vector<int>& route) {

    return route;
}

void divideConquer(const vector<Customer>& customers, vector<Vehicle>& vehicles) {
    vector<vector<int> > routes;
    for (const Vehicle& vehicle : vehicles) {
        vector<int> route;
        route.push_back(0); // Start from depot
        for (int i = 1; i < customers.size(); ++i) {
            route.push_back(i);
        }
        route.push_back(0); // Return to depot
        routes.push_back(route);
    }

    // Use TSP to optimize routes
    for (int i = 0; i < routes.size(); ++i) {
        vector<vector<double> > memo(customers.size(), vector<double>(vehicles.size() + 1, -1));
        double minDist = tsp(customers, vehicles, 0, memo);
        cout << "Vehicle " << vehicles[i].id << " distance: " << minDist << endl;
    }
}




