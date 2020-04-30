#pragma once

#include <vector>
#include "Ant.h"
#include "Graph.h"

using std::vector;

class AntColony
{
    friend class Ant;

private:
    Graph& G;
    vector<Ant> Colony;
    vector<vector<double>> Pheromone;
    vector<vector<double>> DeltaPheromone;

    /* Constants as used in the theoretical definitions  */
    double Alpha;       // 
    double Beta;        // 
    double Q;           // pheromone quantity left by a single ant
    double Ro;          // evaporation rate of pheromone
    double TauMax;

    //int InitialNode;
    int RouteSize;
    int ColonySize;
    int Time = 0;

    void InitializePheromone();
    void InitializeColony();
    void Initialize();

    void UpdatePheromones();

    double BestLength;
    vector<int> BestRoute;

    static const bool Verbose = false;

public:

    AntColony(Graph& G, double Alpha, double Beta, double Q, double Ro, double TauMax);
    
    void Optimize(int Iterations);
    double GetBestLength() const;
    const vector<int>& GetBestRoute() const;

    ~AntColony() = default;
};

