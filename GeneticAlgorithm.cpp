#include "GeneticAlgo.h"
#include <Customer.cpp>
#include <Depot.cpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Matrix.cpp>
#include <VRP.cpp>

// class ProblemSolver
// {
// protected:    
//     vector<Customer> customers;

// public:
//     // Constructor
//     ProblemSolver(Problem problem) : problem(problem) {}

//     // Solve method
//     virtual vector<int> solve(bool log = true, bool intermediate_prints = true) = 0;
// };
using namespace std;

class GeneticSolver : public VRP
{
private:
    double random_portion;
    int generations;
    int population_size;
    double crossover_rate;
    double heuristic_mutate_rate;
    double inversion_mutate_rate;
    double depot_move_mutate_rate;
    double best_insertion_mutate_rate;
    double route_merge_rate;
    vector<vector<int>> population;
    vector<vector<int>> groups;

public:
    // Constructor
    GeneticSolver(VRP problem, double random_portion = 0, int generations = 2500, int population_size = 50,
                  double crossover_rate = 0.60, double heuristic_mutate_rate = 0.20, double inversion_mutate_rate = 0.25,
                  double depot_move_mutate_rate = 0.25, double best_insertion_mutate_rate = 0.1,
                  double route_merge_rate = 0.05) : VRP(problem),
                                                    random_portion(random_portion),
                                                    generations(generations),
                                                    population_size(population_size),
                                                    crossover_rate(crossover_rate),
                                                    heuristic_mutate_rate(heuristic_mutate_rate),
                                                    inversion_mutate_rate(inversion_mutate_rate),
                                                    depot_move_mutate_rate(depot_move_mutate_rate),
                                                    best_insertion_mutate_rate(best_insertion_mutate_rate),
                                                    route_merge_rate(route_merge_rate)
    {
        groupCustomers();
        initializePopulation();
    }

    // Solve method
    vector<int> solve(bool log = true, bool intermediate_prints = true)
    {
        for (int g = 0; g < this.generations; ++g)
        {
            // Log in every 10 generation
            if (log && g % 10 == 0)
            {
                auto best = max_element(population.begin(), population.end(),
                                             [](const vector<int> &x, const vector<int> &y)
                                             {
                                                 return x[1] < y[1];
                                             });
                cout << "[Generation " << g << "] Best score: " << (*best)[1] << " Consistent: "
                          << isConsistent((*best)[0]) << endl;
            }
            // Print intermediate route plans in every 100 generation
            if (intermediate_prints && g % 100 == 0)
            {
                sort(population.begin(), population.end(),
                          [](const vector<int> &x, const vector<int> &y)
                          {
                              return x[1] > y[1];
                          });
                show(population[0][0]);
            }

            // Do selection
            auto selection = select(heuristic_mutate_rate + inversion_mutate_rate + crossover_rate +
                                    depot_move_mutate_rate + best_insertion_mutate_rate + route_merge_rate);

            // Apply Genetic Operators
            int offset = 0;
            int crossoverCount = static_cast<int>(population_size * crossover_rate / 2);
            for (int i = 0; i < crossoverCount; ++i)
            {
                auto p1 = selection[2 * i + offset];
                auto p2 = selection[2 * i + 1 + offset];
                crossover(p1, p2);
                crossover(p2, p1);
            }
            offset += crossoverCount;

            applyMutation(selection, offset, heuristic_mutate_rate, &GeneticSolver::heuristicMutate);
            applyMutation(selection, offset, inversion_mutate_rate, &GeneticSolver::inversionMutate);
            applyMutation(selection, offset, depot_move_mutate_rate, &GeneticSolver::depotMoveMutate);
            applyMutation(selection, offset, best_insertion_mutate_rate, &GeneticSolver::bestInsertionMutate);
            applyMutation(selection, offset, route_merge_rate, &GeneticSolver::routeMerge);

            // Select population
            population = select(1.0, 4);
        }

        // Sort Population
        sort(population.begin(), population.end(),
                  [](const vector<int> &x, const vector<int> &y)
                  {
                      return x[1] > y[1];
                  });
        cout << "\n\nFinished training" << endl;

        vector<int> best_solution;
        // Check consistency of the first population instance
        if (isConsistent(population[0][0]))
        {
            cout << "Best score: " << population[0][1] << ", best distance: "
                      << evaluate(population[0][0], true) << endl;
            best_solution = population[0][0];
        }
        else
        {
            // Check all population instance consistencies while found a consistent one.
            for (const auto &c : population)
            {
                if (isConsistent(c[0]))
                {
                    cout << "Best score: " << c[1] << ", best distance: "
                              << evaluate(c[0], true) << endl;
                    best_solution = c[0];
                    break;
                }
            }
            if (best_solution.empty())
            {
                cout << "Found no consistent solutions." << endl;
            }
        }

        return best_solution;
    }

private:
    // Group customers by proximity to depots
    void groupCustomers()
    {
        // Implementation of groupCustomers method
    }

    // Find closest depot to a given customer
    Depot findClosestDepot(Customer customer)
    {
        // Implementation of findClosestDepot method
    }

    // Calculate distance between two locations
    double distance(vector<int> source, vector<int> destination)
    {
        // Implementation of distance method
    }

    // Print out the route plan for a given chromosome
    void show(vector<int> chromosome)
    {
        // Implementation of show method
    }

    // Encode routes array into a chromosome
    vector<int> encode(vector<vector<int>> routes)
    {
        // Implementation of encode method
    }

    // Decode chromosome into routes array
    vector<vector<int>> decode(vector<int> chromosome)
    {
        // Implementation of decode method
    }

    // Schedule route for a given route
    vector<int> scheduleRoute(vector<int> route)
    {
        // Implementation of scheduleRoute method
    }

    // Check consistency of a given chromosome
    bool isConsistent(vector<int> chromosome){
        const vector<Customer> &customers = problem.customers;
        const vector<Depot> &depots = problem.depots;
        vector<vector<vector<int>>> routes = decode(chromosome);

        for (const Customer &c : customers)
        {
            if (find(chromosome.begin(), chromosome.end(), c.id) == chromosome.end())
            {
                return false;
            }
        }

        for (size_t d = 0; d < routes.size(); ++d)
        {
            const Depot &depot = depots[d];
            if (routes[d].size() > depot.max_vehicles)
            {
                return false;
            }
            for (const auto &route : routes[d])
            {
                if (!is_consistent_route(route, depot))
                {
                    return false;
                }
            }
        }

        return true;
    }

// Check consistency of a given route-depot pair
bool
isConsistentRoute(vector<int> route, Depot depot, bool includeReason)
    {
        // Implementation of isConsistentRoute method
    }

    // Initialize the population
    void initializePopulation()
    {
        // Initialize population using heuristic chromosome generation
        for (int x = 0; x < static_cast<int>(population_size * (1 - random_portion)); ++x)
        {
            auto chromosome = create_heuristic_chromosome(groups);
            population.push_back({chromosome, evaluate(chromosome)});
        }

        // Initialize population using random chromosome generation
        for (int x = 0; x < static_cast<int>(population_size * random_portion); ++x)
        {
            auto chromosome = create_random_chromosome(groups);
            population.push_back({chromosome, evaluate(chromosome)});
        }
    }

    vector<int> create_heuristic_chromosome(const vector<vector<int>> &groups)
    {
        const vector<Depot> &depots = problem.depots;
        const vector<Customer> &customers = problem.customers;
        vector<vector<int>> routes(depots.size());
        vector<int> missing_customers(customers.size());

        // Initialize missing customers
        for (size_t i = 0; i < customers.size(); ++i)
        {
            missing_customers[i] = customers[i].id;
        }

        for (size_t d = 0; d < groups.size(); ++d)
        {
            const Depot &depot = depots[d];
            const auto &group = groups[d];
            vector<vector<double>> savings(group.size(), vector<double>(group.size(), 0.0));

            // Calculate savings
            for (size_t i = 0; i < group.size(); ++i)
            {
                for (size_t j = i + 1; j < group.size(); ++j)
                {
                    const Customer &ci = customers[group[i]];
                    const Customer &cj = customers[group[j]];
                    savings[i][j] = distance(depot, ci) + distance(depot, cj) - distance(ci, cj);
                }
            }

            // Sort savings
            vector<pair<double, pair<int, int>>> savings_order;
            for (size_t i = 0; i < group.size(); ++i)
            {
                for (size_t j = i + 1; j < group.size(); ++j)
                {
                    savings_order.push_back({savings[i][j], {i, j}});
                }
            }
            sort(savings_order.rbegin(), savings_order.rend());

            for (const auto &saving : savings_order)
            {
                int i = saving.second.first;
                int j = saving.second.second;
                const Customer &ci = customers[group[i]];
                const Customer &cj = customers[group[j]];
                int ri = -1;
                int rj = -1;

                // Find routes containing ci and cj
                for (size_t r = 0; r < routes[d].size(); ++r)
                {
                    if (find(routes[d][r].begin(), routes[d][r].end(), ci.id) != routes[d][r].end())
                    {
                        ri = r;
                    }
                    if (find(routes[d][r].begin(), routes[d][r].end(), cj.id) != routes[d][r].end())
                    {
                        rj = r;
                    }
                }

                vector<int> new_route;

                if (ri == -1 && rj == -1)
                {
                    if (routes[d].size() < depot.max_vehicles)
                    {
                        if (ci.id == cj.id)
                        {
                            new_route = {ci.id};
                        }
                        else
                        {
                            new_route = {ci.id, cj.id};
                        }
                    }
                }
                else if (ri != -1 && rj == -1)
                {
                    if (routes[d][ri].front() == ci.id || routes[d][ri].back() == ci.id)
                    {
                        new_route = routes[d][ri];
                        new_route.push_back(cj.id);
                    }
                }
                else if (ri == -1 && rj != -1)
                {
                    if (routes[d][rj].front() == cj.id || routes[d][rj].back() == cj.id)
                    {
                        new_route = routes[d][rj];
                        new_route.push_back(ci.id);
                    }
                }
                else if (ri != -1 && rj != -1)
                {
                    new_route = routes[d][ri];
                    new_route.insert(new_route.end(), routes[d][rj].begin(), routes[d][rj].end());
                }

                if (!new_route.empty() && is_consistent_route(new_route, depot, true) == 2)
                {
                    new_route = schedule_route(new_route);
                    if (is_consistent_route(new_route, depot))
                    {
                        if (ri == -1 && rj == -1)
                        {
                            routes[d].push_back(new_route);
                            missing_customers.erase(remove(missing_customers.begin(), missing_customers.end(), ci.id), missing_customers.end());
                            if (ci.id != cj.id)
                            {
                                missing_customers.erase(remove(missing_customers.begin(), missing_customers.end(), cj.id), missing_customers.end());
                            }
                        }
                        else if (ri != -1 && rj == -1)
                        {
                            routes[d][ri] = new_route;
                            missing_customers.erase(remove(missing_customers.begin(), missing_customers.end(), cj.id), missing_customers.end());
                        }
                        else if (ri == -1 && rj != -1)
                        {
                            routes[d][rj] = new_route;
                            missing_customers.erase(remove(missing_customers.begin(), missing_customers.end(), ci.id), missing_customers.end());
                        }
                        else if (ri != -1 && rj != -1)
                        {
                            if (ri > rj)
                            {
                                routes[d].erase(routes[d].begin() + ri);
                                routes[d].erase(routes[d].begin() + rj);
                            }
                            else
                            {
                                routes[d].erase(routes[d].begin() + rj);
                                routes[d].erase(routes[d].begin() + ri);
                            }
                            routes[d].push_back(new_route);
                        }
                    }
                }
            }
        }

        // Order customers within routes
        for (size_t i = 0; i < routes.size(); ++i)
        {
            for (size_t j = 0; j < routes[i].size(); ++j)
            {
                routes[i][j] = schedule_route(routes[i][j]);
            }
        }

        vector<int> chromosome = encode(routes);
        chromosome.insert(chromosome.end(), missing_customers.begin(), missing_customers.end());
        return chromosome;
    }

    // Create chromosomes using a random approach
    vector<int> createRandomChromosome(vector<vector<int>> groups)
    {
        // Implementation of createRandomChromosome method
    }

    // Apply crossover operation
    void crossover(vector<int> &p1, vector<int> &p2)
    {
        // Implementation of crossover method
    }

    // Evaluate the fitness of a chromosome
    double evaluate(vector<int> chromosome, bool returnDistance)
    {
        // Implementation of evaluate method
    }

    // Evaluate the fitness of a route
    double evaluateRoute(vector<int> route, Depot depot, bool returnLoad)
    {
        // Implementation of evaluateRoute method
    }

    // Select individuals from the population
    vector<vector<int>> select(double portion, int elitism)
    {
        // Implementation of select method
    }

    // Apply heuristic mutation operation
    void heuristicMutate(vector<int> &p)
    {
        // Implementation of heuristicMutate method
    }

    // Apply inversion mutation operation
    void inversionMutate(vector<int> &p)
    {
        // Implementation of inversionMutate method
    }

    // Apply best insertion mutation operation
    void bestInsertionMutate(vector<int> &p)
    {
        // Implementation of bestInsertionMutate method
    }

    // Apply depot move mutation operation
    void depotMoveMutate(vector<int> &p)
    {
        // Implementation of depotMoveMutate method
    }

    // Apply route merge operation
    void routeMerge(vector<int> &p)
    {
        // Implementation of routeMerge method
    }
};