#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

// Forward declarations for classes used in GeneticAlgorithm
class Customer;
class Depot;
class Location;

using namespace std;
// Define the GeneticAlgorithm class
class GeneticAlgorithm
{
public:
    GeneticAlgorithm(/* Add parameters */);                      // Constructor
    void solve(bool log = true, bool intermediatePrints = true); // Solve method
    // Declare other public methods

private:
    // Declare private member variables and methods
    // Add necessary includes
    void groupCustomers();
    Depot findClosestDepot(Customer customer);
    double distance(vector<int> source, vector<int> destination);
    void show(std::vector<int> chromosome);
    std::vector<int> encode(std::vector<std::vector<int>> routes);
    std::vector<std::vector<int>> decode(std::vector<int> chromosome);
    std::vector<int> scheduleRoute(std::vector<int> route);
    bool isConsistent(std::vector<int> chromosome);
    bool isConsistentRoute(std::vector<int> route, Depot depot, bool includeReason = true);
    void initializePopulation();
    std::vector<int> createHeuristicChromosome(std::vector<std::vector<int>> groups);
    std::vector<int> createRandomChromosome(std::vector<std::vector<int>> groups);
    void crossover(std::vector<int> &p1, std::vector<int> &p2);
    double evaluate(std::vector<int> chromosome, bool returnDistance = false);
    double evaluateRoute(std::vector<int> route, Depot depot, bool returnLoad = false);
    std::vector<std::vector<int>> select(double portion, int elitism = 0);
    void heuristicMutate(std::vector<int> &p);
    void inversionMutate(std::vector<int> &p);
    void bestInsertionMutate(std::vector<int> &p);
    void depotMoveMutate(std::vector<int> &p);
    void routeMerge(std::vector<int> &p);
};

#endif
